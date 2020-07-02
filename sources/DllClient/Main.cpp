/**************************************************************************
 *   Created: 2013/04/18 23:54:56
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

////////////////////////////////////////////////////////////////////////////////

namespace TakionBridge { namespace DllClient {

	App theApp;

} }

////////////////////////////////////////////////////////////////////////////////

BOOL WINAPI DllMain(
			_In_  HINSTANCE /*hinstDLL*/,
			_In_  DWORD fdwReason,
			_In_  LPVOID /*reserved*/) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			theApp.GetClient();
			break;
		case DLL_PROCESS_DETACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		default:
			break;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
