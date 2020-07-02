/**************************************************************************
 *   Created: 2013/04/17 07:56:54
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#pragma once

namespace TakionBridge { namespace Interface { 

	typedef char PacketMagic[2];

	typedef char Symbol[13];

	typedef unsigned int Qty;

	typedef double Price;

 	enum OrderSide {
 		OS_BUY,
 		OS_SELL
 	};

	enum MessageId : uint8_t {
		MESSAGE_ID_UNKNOWN,
		MESSAGE_ID_ORDER_MARKET,
		MESSAGE_ID_ORDER_MARKET_WITH_STOP_PRICE,
		MESSAGE_ID_ORDER_LIMIT,
		MESSAGE_ID_REQUEST_SECURITY_INFO,
		MESSAGE_ID_REQUEST_POSITION_INFO,
		MESSAGE_ID_NOT_A_MESSAGE
	};

} }
