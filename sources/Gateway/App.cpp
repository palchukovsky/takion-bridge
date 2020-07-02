/**************************************************************************
 *   Created: 2013/04/17 21:23:56
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#include "Prec.hpp"
#include "App.hpp"
#include "MainDialog.hpp"
#include "Server.hpp"
#include "Interface/Util.hpp"

//////////////////////////////////////////////////////////////////////////

using namespace TakionBridge::Gateway;

App::App() {
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
}

App::~App() {
	//...//
}

bool App::IsServerStarted() const {
	return m_server;
}

void App::StartServer() {
	assert(!IsServerStarted());
	if (m_server) {
		return;
	}
	m_server.reset(new Server(Interface::GetDefaultGatewayPort()));
}

void App::StopServer() {
	assert(IsServerStarted());
	m_server.reset();
}

BOOL App::InitInstance() {
	if (!Base::InitInstance()) {
		return FALSE;
	}
	U_InitializeInstanceInfo(
		m_hInstance,
		m_filePathAndName,
		m_fileDescription,
		m_platform,
		m_versionNum,
		m_versionStr);
	return TRUE;
}

int App::ExitInstance() {
	return Base::ExitInstance();
}

MainDialog & App::GetMainDialog() {
	if (!m_mainDialog) {
		m_mainDialog.reset(new MainDialog);
	}
	return *m_mainDialog;
}

//////////////////////////////////////////////////////////////////////////

namespace TakionBridge { namespace Gateway {
	App theApp;
} }

