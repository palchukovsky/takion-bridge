/**************************************************************************
 *   Created: 2013/04/18 23:56:27
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#include "Prec.hpp"
#include "Client.hpp"
#include "Connection.hpp"
#include "Interface/Commands.hpp"

using namespace TakionBridge;
using namespace TakionBridge::DllClient;
using namespace TakionBridge::Interface;

Client::Client(const char *host, unsigned short port) {
	try {
		m_connection.reset(new Connection(host, port));
		std::ostringstream oss;
		oss
			<< "Connected to the Takion at \"" << host << "\""
			<<", port " << port << ".";
		m_connectionInfo = oss.str();
	} catch (const boost::system::system_error &ex) {
		const char *const generalErrorText = "Failed to connect to the Takion";
		std::ostringstream oss;
		oss
			<< generalErrorText << " at \"" << host << "\""
			<<", port " << port << " (" << ex.what() << ").";
		m_connectionInfo = oss.str();
		strncpy_s(
			m_lastResponse.text,
			_countof(m_lastResponse.text),
			generalErrorText,
			_TRUNCATE);
		m_lastResponse.status = Commands::Response::STATUS_GENERAL_ERROR;
	}
}

Client::~Client() {
	//...//
}

template<typename Order>
void Client::SendOrder(const Order &order) {
	if (!m_connection) {
		return;
	}
	m_connection->SendMessage(order, m_lastResponse);
}

const char * Client::GetLastSendErrorText() const  throw() {
	return m_lastResponse.text;
}

Commands::Response::Status Client::SendMarketOrder(
			const char *symbol,
			OrderSide side,
			Qty qty) {
	assert(symbol);
	assert(strlen(symbol) > 0);
	Commands::MarketOrder order;
	strncpy(order.symbol, symbol, _countof(order.symbol) - 1);
	order.side = side;
	order.qty = qty;
	SendOrder(order);
	return m_lastResponse.status;
}

Commands::Response::Status Client::SendMarketOrderWithStopPrice(
			const char *symbol,
			OrderSide side,
			Qty qty,
			Price stopPrice) {
	assert(symbol);
	assert(strlen(symbol) > 0);
	Commands::MarketOrderWithStopPrice order;
	strncpy(order.symbol, symbol, _countof(order.symbol) - 1);
	order.side = side;
	order.qty = qty;
	order.stopPrice = stopPrice;
	SendOrder(order);
	return m_lastResponse.status;
}

Commands::Response::Status Client::SendLimitOrder(
			const char *symbol,
			OrderSide side,
			Qty qty,
			Price price) {
	assert(symbol);
	assert(strlen(symbol) > 0);
	Commands::LimitOrder order;
	strncpy_s(order.symbol, _countof(order.symbol), symbol, _TRUNCATE);
	order.side = side;
	order.qty = qty;
	order.price = price;
	SendOrder(order);
	return m_lastResponse.status;
}

boost::shared_ptr<const Requests::SecurityInfo> Client::GetSecurityInfo(
			const char *symbol)
		const {
	boost::shared_ptr<Requests::SecurityInfo> result(
		new Requests::SecurityInfo);
	if (!m_connection) {
		return result;
	}
	Requests::SecurityInfoRequest request;
	strncpy_s(request.symbol, _countof(request.symbol), symbol, _TRUNCATE);
	m_connection->SendMessage(request, *result);
	m_lastResponse.status = Commands::Response::STATUS_UNDEFINED;
	switch (result->status) {
		default:
		case Requests::SecurityInfo::STATUS_UNDEFINED:
			strncpy_s(
				m_lastResponse.text,
				_countof(m_lastResponse.text),
				"General error.",
				_TRUNCATE);
			break;
		case Requests::SecurityInfo::STATUS_UNKNOWN_STOCK:
			strncpy_s(
				m_lastResponse.text,
				_countof(m_lastResponse.text),
				"Can't obtain stock.",
				_TRUNCATE);
			break;
		case Requests::SecurityInfo::STATUS_NOTLOADED_STOCK:
			strncpy_s(
				m_lastResponse.text,
				_countof(m_lastResponse.text),
				"Can't obtain stock.",
				_TRUNCATE);
			break;
		case Requests::SecurityInfo::STATUS_NO_ACCOUNT:
			strncpy_s(
				m_lastResponse.text,
				_countof(m_lastResponse.text),
				"No account.",
				_TRUNCATE);
			break;
		case Requests::SecurityInfo::STATUS_OK:
			m_lastResponse.status = Commands::Response::STATUS_OK;
			strncpy_s(
				m_lastResponse.text,
				_countof(m_lastResponse.text),
				"Success.",
				_TRUNCATE);
			break;
	}
	return result;
}

boost::shared_ptr<const Requests::PositionInfo> Client::GetPositionInfo(
			const char *symbol)
		const {
	boost::shared_ptr<Requests::PositionInfo> result(
		new Requests::PositionInfo);
	if (!m_connection) {
		return result;
	}
	Requests::PositionInfoRequest request;
	strncpy_s(request.symbol, _countof(request.symbol), symbol, _TRUNCATE);
	m_connection->SendMessage(request, *result);
	m_lastResponse.status = Commands::Response::STATUS_UNDEFINED;
	switch (result->status) {
		default:
		case Requests::PositionInfo::STATUS_UNDEFINED:
			strncpy_s(
				m_lastResponse.text,
				_countof(m_lastResponse.text),
				"General error.",
				_TRUNCATE);
			break;
		case Requests::PositionInfo::STATUS_UNKNOWN_STOCK:
			strncpy_s(
				m_lastResponse.text,
				_countof(m_lastResponse.text),
				"Can't obtain stock.",
				_TRUNCATE);
			break;
		case Requests::PositionInfo::STATUS_NOTLOADED_STOCK:
			strncpy_s(
				m_lastResponse.text,
				_countof(m_lastResponse.text),
				"Can't obtain stock.",
				_TRUNCATE);
			break;
		case Requests::PositionInfo::STATUS_NO_ACCOUNT:
			strncpy_s(
				m_lastResponse.text,
				_countof(m_lastResponse.text),
				"No account.",
				_TRUNCATE);
			break;
		case Requests::PositionInfo::STATUS_OK:
			m_lastResponse.status = Commands::Response::STATUS_OK;
			strncpy_s(
				m_lastResponse.text,
				_countof(m_lastResponse.text),
				"Success.",
				_TRUNCATE);
			break;
	}
	return result;
}
