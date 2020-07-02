/**************************************************************************
 *   Created: 2013/04/19 00:29:09
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#include "Prec.hpp"
#include "App.hpp"
#include "Client.hpp"

using namespace TakionBridge;
using namespace TakionBridge::DllClient;
using namespace TakionBridge::Interface;

#define DLL_CLIENT_API _declspec(dllexport)

extern "C" {

	DLL_CLIENT_API const char * Takion_GetConnectionInfo() {
		return theApp.GetClient().GetConnectionInfo().c_str();
	}

	DLL_CLIENT_API const char * Takion_GetLastError() {
		return theApp.GetClient().GetLastSendErrorText();
	}

	DLL_CLIENT_API int _stdcall Takion_BuyMarket(
				const char *symbol,
				unsigned int qty) {
		try {
			return theApp.GetClient().SendMarketOrder(symbol, OS_BUY, qty);
		} catch (const std::exception &) {
			return -1;
		}
	}

	DLL_CLIENT_API int _stdcall Takion_SellMarket(
				const char *symbol,
				unsigned int qty) {
		try {
			return theApp.GetClient().SendMarketOrder(symbol, OS_SELL, qty);
		} catch (const std::exception &) {
			return -1;
		}
	}

	DLL_CLIENT_API int _stdcall Takion_BuyStop(
				const char *symbol,
				unsigned int qty,
				double stopPrice) {
		try {
			return theApp.GetClient()
				.SendMarketOrderWithStopPrice(symbol, OS_BUY, qty, stopPrice);
		} catch (const std::exception &) {
			return -1;
		}
	}

	DLL_CLIENT_API int _stdcall Takion_SellStop(
				const char *symbol,
				unsigned int qty,
				double stopPrice) {
		try {
			return theApp.GetClient()
				.SendMarketOrderWithStopPrice(symbol, OS_SELL, qty, stopPrice);
		} catch (const std::exception &) {
			return -1;
		}
	}

	DLL_CLIENT_API int _stdcall Takion_BuyLimit(
				const char *symbol,
				unsigned int qty,
				double price) {
		try {
			return theApp.GetClient()
				.SendLimitOrder(symbol, OS_BUY, qty, price);
		} catch (const std::exception &) {
			return -1;
		}
	}

	DLL_CLIENT_API int _stdcall Takion_SellLimit(
				const char *symbol,
				unsigned int qty,
				double price) {
		try {
			return theApp.GetClient()
				.SendLimitOrder(symbol, OS_SELL, qty, price);
		} catch (const std::exception &) {
			return -1;
		}
	}

	DLL_CLIENT_API unsigned int _stdcall Takion_GetPosSize(const char *symbol) {
		try {
			return theApp.GetClient().GetSecurityInfo(symbol)->positionQty;
		} catch (const std::exception &) {
			return 0;
		}
	}

	DLL_CLIENT_API double _stdcall Takion_GetPosPrice(const char *symbol) {
		try {
			return theApp.GetClient().GetSecurityInfo(symbol)->positionPrice;
		} catch (const std::exception &) {
			return .0;
		}
	}

	DLL_CLIENT_API double _stdcall Takion_GetOpenPnL(const char *symbol) {
		try {
			return theApp.GetClient().GetPositionInfo(symbol)->openPnL;
		} catch (const std::exception &) {
			return .0;
		}
	}

	DLL_CLIENT_API double _stdcall Takion_GetClosedPnL(const char *symbol) {
		try {
			return theApp.GetClient().GetPositionInfo(symbol)->closedPnL;
		} catch (const std::exception &) {
			return .0;
		}
	}

}
