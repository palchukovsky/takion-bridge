/**************************************************************************
 *   Created: 2013/04/28 19:49:58
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#pragma once

#include "Types.hpp"

namespace TakionBridge { namespace Interface { namespace Requests {

	////////////////////////////////////////////////////////////////////////////////

	struct SymbolInfoRequest {
		
		Symbol symbol;

		SymbolInfoRequest();

	};

	////////////////////////////////////////////////////////////////////////////////

	struct SecurityInfoRequest : public SymbolInfoRequest {
		
		static MessageId GetId();

	};

	struct SecurityInfo {

		enum Status : uint8_t {
			STATUS_UNDEFINED,
			STATUS_UNKNOWN_STOCK,
			STATUS_NOTLOADED_STOCK,
			STATUS_NO_ACCOUNT,
			STATUS_OK
		};

		Status status;

		Price positionPrice;
		Qty positionQty;

		SecurityInfo();

	};

	////////////////////////////////////////////////////////////////////////////////

	struct PositionInfoRequest : public SymbolInfoRequest {
		
		static MessageId GetId();

	};

	struct PositionInfo {

		enum Status : uint8_t {
			STATUS_UNDEFINED,
			STATUS_UNKNOWN_STOCK,
			STATUS_NOTLOADED_STOCK,
			STATUS_NO_ACCOUNT,
			STATUS_OK
		};

		Status status;

		Price openPnL;
		Price closedPnL;

		PositionInfo();

	};

	////////////////////////////////////////////////////////////////////////////////

} } }
