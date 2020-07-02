/**************************************************************************
 *   Created: 2013/04/28 20:29:34
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#include "Prec.hpp"
#include "RequestAnswer.hpp"
#include "Util.hpp"

using namespace TakionBridge;
using namespace TakionBridge::Gateway;
using namespace TakionBridge::Interface;

////////////////////////////////////////////////////////////////////////////////

SecurityInfo::SecurityInfo(const Requests::SecurityInfoRequest &request)
		: m_request(request),
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
		TD_ObtainStock(m_request.symbol, false),
		releaseStock);
	if (!stock.get() || !stock->isLoaded()) {
		return;
	}

	m_account = TD_GetCurrentAccount();
	if (!m_account) {
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

SecurityInfo::~SecurityInfo() {
	if (m_stock) {
		TD_ReleaseStock(m_stock);
	}
}

boost::shared_ptr<const Requests::SecurityInfo> SecurityInfo::Execute() {
	boost::shared_ptr<Requests::SecurityInfo> result(
		new Requests::SecurityInfo);
	if (!IsOk()) {
		return result;
	}
	result->status = Requests::SecurityInfo::STATUS_OK;
	result->positionPrice = PriceToPrice(GetPositionPrice());
	result->positionQty = GetPositionSize();
	return result;
}

int SecurityInfo::GetPositionSize() const {
	return m_position
		?	m_position->GetSize()
		:	0;
}

::Price SecurityInfo::GetPositionPrice() const {
	::Price result;
	if (m_position) {
		result = m_position->GetAveragePrice();
	}
	return result;
}

////////////////////////////////////////////////////////////////////////////////

PositionInfo::PositionInfo(const Requests::PositionInfoRequest &request)
		: m_request(request),
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
		TD_ObtainStock(m_request.symbol, false),
		releaseStock);
	if (!stock.get() || !stock->isLoaded()) {
		return;
	}

	m_account = TD_GetCurrentAccount();
	if (!m_account) {
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

PositionInfo::~PositionInfo() {
	if (m_stock) {
		TD_ReleaseStock(m_stock);
	}
}

boost::shared_ptr<const Requests::PositionInfo> PositionInfo::Execute() {
	boost::shared_ptr<Requests::PositionInfo> result(
		new Requests::PositionInfo);
	if (!IsOk()) {
		return result;
	}
	result->status = Requests::PositionInfo::STATUS_OK;
	if (m_position) {
		result->openPnL = PriceToPrice(m_position->GetOpenPnlNbboPrint());
		result->closedPnL = PriceToPrice(m_position->GetClosedPnl());
	}
	return result;
}

////////////////////////////////////////////////////////////////////////////////
