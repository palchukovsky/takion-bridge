/**************************************************************************
 *   Created: 2013/04/28 20:13:19
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#include "Prec.hpp"
#include "Requests.hpp"

using namespace TakionBridge;
using namespace TakionBridge::Interface;
using namespace TakionBridge::Interface::Requests;

////////////////////////////////////////////////////////////////////////////////

SymbolInfoRequest::SymbolInfoRequest() {
	memset(symbol, 0, sizeof(symbol));
}

////////////////////////////////////////////////////////////////////////////////

MessageId SecurityInfoRequest::GetId() {
	return MESSAGE_ID_REQUEST_SECURITY_INFO;
}

SecurityInfo::SecurityInfo()
		: status(STATUS_UNDEFINED),
		positionPrice(.0),
		positionQty(0) {
	//...//
}

////////////////////////////////////////////////////////////////////////////////

MessageId PositionInfoRequest::GetId() {
	return MESSAGE_ID_REQUEST_POSITION_INFO;
}

PositionInfo::PositionInfo()
		: status(STATUS_UNDEFINED),
		openPnL(.0),
		closedPnL(.0) {
	//...//
}

////////////////////////////////////////////////////////////////////////////////
