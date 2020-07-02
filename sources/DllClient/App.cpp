/**************************************************************************
 *   Created: 2013/04/18 23:59:11
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#include "Prec.hpp"
#include "App.hpp"
#include "Client.hpp"
#include "Interface/Util.hpp"

using namespace TakionBridge;
using namespace TakionBridge::DllClient;

////////////////////////////////////////////////////////////////////////////////

namespace {

#	ifdef DEV_VER
		const char *const ipAddress = "192.168.132.32";
#	else
		const char *const ipAddress = "127.0.0.1";
#	endif

}

////////////////////////////////////////////////////////////////////////////////

App::App() {
	//...//
}

App::~App() {
	//...//
}

Client & App::GetClient() {
	if (!m_client) {
		m_client.reset(
			new Client(ipAddress, Interface::GetDefaultGatewayPort()));
	}
	return *m_client;
}

const Client & App::GetClient() const {
	return const_cast<App *>(this)->GetClient();
}

////////////////////////////////////////////////////////////////////////////////
