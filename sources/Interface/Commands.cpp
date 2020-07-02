/**************************************************************************
 *   Created: 2013/04/23 21:52:18
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#include "Prec.hpp"
#include "Commands.hpp"

using namespace TakionBridge;
using namespace TakionBridge::Interface;
using namespace TakionBridge::Interface::Commands;

MessageId MarketOrder::GetId() {
	return MESSAGE_ID_ORDER_MARKET;
}

MessageId MarketOrderWithStopPrice::GetId() {
	return MESSAGE_ID_ORDER_MARKET_WITH_STOP_PRICE;
}

MessageId LimitOrder::GetId() {
	return MESSAGE_ID_ORDER_LIMIT;
}
