/**************************************************************************
 *   Created: 2013/04/17 07:54:21
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#pragma once

#include "Types.hpp"

namespace TakionBridge { namespace Interface { namespace Commands {

	//////////////////////////////////////////////////////////////////////////

	struct Order {
		TakionBridge::Interface::Symbol symbol;
		TakionBridge::Interface::OrderSide side;
		TakionBridge::Interface::Qty qty;
	};

	struct MarketOrder : public TakionBridge::Interface::Commands::Order {
		static MessageId GetId();
	};

	struct MarketOrderWithStopPrice
			: public TakionBridge::Interface::Commands::MarketOrder {
		
		TakionBridge::Interface::Price stopPrice;

		static MessageId GetId();

	};
	
	struct LimitOrder : public TakionBridge::Interface::Commands::Order {
	
		TakionBridge::Interface::Price price;

		static MessageId GetId();
	
	};

	//////////////////////////////////////////////////////////////////////////

	struct Response {

		enum Status : uint8_t {
			STATUS_OK,
			STATUS_UNDEFINED,
			STATUS_GENERAL_ERROR,
			STATUS_FORMAT_ERROR,
			STATUS_UNKNOWN_STOCK,
			STATUS_NOTLOADED_STOCK,
			STATUS_NO_ACCOUNT,
		};

		Status status;
		char text[64];

		Response() 
				: status(STATUS_UNDEFINED) {
			text[0] = 0;
		}

	};


	////////////////////////////////////////////////////////////////////////////////

} } }
