/**************************************************************************
 *   Created: 2013/04/23 21:09:49
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#include "Prec.hpp"
#include "OrderCommand.hpp"
#include "Util.hpp"

using namespace TakionBridge;
using namespace TakionBridge::Gateway;
using namespace TakionBridge::Interface;

////////////////////////////////////////////////////////////////////////////////

OrderCommand::Exception::Exception(
					Commands::Response::Status status,
					const char *what)
			: std::exception(what),
			m_status(status) {
	//...//
}

Commands::Response::Status OrderCommand::Exception::GetStatus() const {
	return m_status;
}

////////////////////////////////////////////////////////////////////////////////

OrderCommand::OrderCommand(const TakionBridge::Interface::Symbol &symbol)
		: m_response(new Commands::Response),
		m_stock(nullptr),
		m_account(nullptr),
		m_position(nullptr) {

	const auto releaseStock = [](Security *stock) {
		if (!stock) {
			return;
		}
		TD_ReleaseStock(stock);
	};

	std::unique_ptr<Security, decltype(releaseStock)> stock(
		TD_ObtainStock(symbol, false),
		releaseStock);
	if (!stock.get()) {
		SetResponse(
			Commands::Response::STATUS_UNKNOWN_STOCK, 
			"Can't obtain stock.");
		return;
	} else if (!stock->isLoaded()) {
		SetResponse(
			Commands::Response::STATUS_NOTLOADED_STOCK,
			"Stock not loaded.");
		return;
	}

	m_account = TD_GetCurrentAccount();
	if (!m_account) {
		SetResponse(Commands::Response::STATUS_NO_ACCOUNT, "No account.");
		return;
	}

	m_account->LockInquiryWait();
	try {
		m_position = m_account->FindStockPosition(stock->GetNumericSymbol());
	} catch (...) {
		m_account->UnlockInquiry();
		throw;
	}
	m_account->UnlockInquiry();

	m_stock = stock.release();

}

OrderCommand::~OrderCommand() {
	if (m_stock) {
		TD_ReleaseStock(m_stock);
	}
}

void OrderCommand::SetResponse(
			Commands::Response::Status status,
			const char *text) {
	m_response->status = status;
	assert(strlen(text) <= _countof(m_response->text) - 1);
	strncpy(m_response->text, text, _countof(m_response->text) - 1);
}

void OrderCommand::SetResponse(const Exception &ex) {
	m_response->status = ex.GetStatus();
	assert(strlen(ex.what()) <= _countof(m_response->text) - 2);
	strncpy(m_response->text, ex.what(), _countof(m_response->text) - 2);
	const size_t len = strlen(m_response->text);
	m_response->text[len] = '.';
	m_response->text[len + 1] = 0;
}

int OrderCommand::GetPositionSize() const {
	return m_position
		?	m_position->GetSize()
		:	0;
}

::Price OrderCommand::GetPositionPrice() const {
	::Price result;
	if (m_position) {
		result = m_position->GetAveragePrice();
	}
	return result;
}

::Price OrderCommand::GetLevel1Bid() const {
	return ::Price(GetStock().GetL1Bid());
}
	
::Price OrderCommand::GetLevel1Ask() const {
	return ::Price(GetStock().GetL1Ask());
}

boost::shared_ptr<const Commands::Response> OrderCommand::Execute() {
	if (!IsOk()) {
		return m_response;
	}
	try {
		const auto orderSendingResult = SendOrder();
		if (orderSendingResult != OE_OK) {
			SetResponse(Commands::Response::STATUS_GENERAL_ERROR, "General error.");
		} else {
			SetResponse(Commands::Response::STATUS_OK, "Order sent.");
		}
	} catch (const Exception &ex) {
		SetResponse(ex);
	}
	return m_response;
}

char OrderCommand::GetSide(Interface::OrderSide side) {
	switch (side) {
		case OS_BUY:
			return 'B';
		case OS_SELL:
			return 'S';
		default:
			throw Exception(
				Commands::Response::STATUS_FORMAT_ERROR,
				"Unknown order side");
	}
}

////////////////////////////////////////////////////////////////////////////////

MarketOrderCommand::MarketOrderCommand(const Commands::MarketOrder &order)
		: Base(order.symbol),
		m_order(order) {
	//...//
}

MarketOrderCommand::~MarketOrderCommand() {
	//...//
}

unsigned char MarketOrderCommand::SendOrder() {

	::Price signedStopPrice(PriceToPrice(GetStopPrice()));
	::Price level1Bid = GetLevel1Bid();
	::Price level1Ask = GetLevel1Ask();
	SignedPrice pegOffset;

	return GetAccount().SendOrder(
		NULL,
		NULL,
		true,
		0,
		&GetStock(),
		0,
		AMEX_ROUTE,
		GetSide(m_order.side),
		GetOrderType(),
		0,
		NULL,
		TU_GetPriceZero(),
		TU_GetPriceZero(),
		signedStopPrice,
		GetStopType(),
		OST_NONE,
		level1Bid,
		level1Ask,
		m_order.qty,
		m_order.qty,
		0,
		0,
		0,
		0,
		0,
		false,
		0,
		pegOffset,
		'0',
		0,
		true,
		'1',
		true,
		false,
		TU_GetPriceZero(),
		false,
		false,
		false,
		false,
		false,
		RLP_ROUND_DOWN,
		NULL,
		0);

}

MarketOrderWithStopPriceCommand::MarketOrderWithStopPriceCommand(
				const Commands::MarketOrderWithStopPrice &order)
		: Base(order),
		m_stopPrice(order.stopPrice) {
	//...//
}
		
MarketOrderWithStopPriceCommand::~MarketOrderWithStopPriceCommand() {
	//...//
}

////////////////////////////////////////////////////////////////////////////////

LimitOrderCommand::LimitOrderCommand(const Commands::LimitOrder &order)
		: Base(order.symbol),
		m_order(order) {
	//...//
}

LimitOrderCommand::~LimitOrderCommand() {
	//...//
}

unsigned char LimitOrderCommand::SendOrder() {
	
	::Price limitPrice(PriceToPrice(m_order.price));
	::Price level1Bid = GetLevel1Bid();
	::Price level1Ask = GetLevel1Ask();
	SignedPrice pegOffset;

	return GetAccount().SendOrder(
		NULL,
		NULL,
		true,
		0,
		&GetStock(),
		0,
		AMEX_ROUTE,
		GetSide(m_order.side),
		ORDER_TYPE_LIMIT,
		0,
		NULL,
		limitPrice,
		TU_GetPriceZero(),
		TU_GetPriceZero(),
		OST_NONE,
		OST_NONE,
		level1Bid,
		level1Ask,
		m_order.qty,
		m_order.qty,
		0,
		0,
		0,
		0,
		0,
		false,
		0,
		pegOffset,
		'0',
		0,
		true,
		'1',
		true,
		false,
		TU_GetPriceZero(),
		false,
		false,
		false,
		false,
		false,
		RLP_ROUND_DOWN,
		NULL,
		0);

}

////////////////////////////////////////////////////////////////////////////////
