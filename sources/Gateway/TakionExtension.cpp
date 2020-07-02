/**************************************************************************
 *   Created: 2013/04/18 08:56:28
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#include "Prec.hpp"
#include "App.hpp"
#include "MainDialog.hpp"

using namespace TakionBridge::Gateway;

////////////////////////////////////////////////////////////////////////////////

namespace {

	const char *const takionGatewayStatusCaption = "Takion Gateway status";

	std::unique_ptr<TakionMessageBox> messageBox;

}

////////////////////////////////////////////////////////////////////////////////

namespace {

	//Format: "<1 ifEnabled, or 0 ifDisabled><1 ifChecked, or 0 ifUnchecked><MenuItemText>|..."
	//For a separator: just one char |
	void AddMenuItemToString(
				std::string &menuStr,
				const char *text = nullptr,
				bool enabled = true,
				bool checked = false) {
		if (text) {
			if (!menuStr.empty()) {
				menuStr += '|';
			}
			menuStr += enabled ? '1' : '0';
			menuStr += checked ? '1' : '0';
			menuStr += text;
		} else {
			menuStr += '|';
		}
	}

	void StartServer() {
		try {
			theApp.StartServer();
			messageBox->ClearMessageList(false);
			messageBox->AddMessage("Takion Gateway successfully opened.", true);
			messageBox->DisplayModeless(
				TGUI_GetTakionMainWnd(),
				takionGatewayStatusCaption,
				MB_OK | MB_ICONINFORMATION);
		} catch (const std::exception &ex) {
			messageBox->ClearMessageList(false);
			std::ostringstream oss;
			oss << "Failed to open Takion Gateway: \"" << ex.what() << "\".";
			messageBox->AddMessage(oss.str().c_str(), true);
			messageBox->DisplayModeless(
				TGUI_GetTakionMainWnd(),
				takionGatewayStatusCaption,
				MB_OK | MB_ICONERROR);
		}
	}

	void StopServer() {
		theApp.StopServer();
		messageBox->ClearMessageList(false);
		messageBox->AddMessage("Takion Gateway closed.", true);
		messageBox->DisplayModeless(
			TGUI_GetTakionMainWnd(),
			takionGatewayStatusCaption,
			MB_OK | MB_ICONINFORMATION);
	}

}

////////////////////////////////////////////////////////////////////////////////

extern "C" {

	unsigned int WINAPI GetExtensionCode() {
		return 1;
	}

	unsigned __int64 WINAPI GetExtensionVersion() {
		return theApp.GetVersionNum();
	}

	unsigned __int64 WINAPI GetUtilsVersion() {
		return U_GetModuleVersionNum();
	}

	unsigned __int64 WINAPI GetUtilsHeaderVersion() {
		return U_VersionStrToNum(UtilsHeaderVersion);
	}

	unsigned __int64 WINAPI GetTakionUtilsVersion() {
		return TU_GetModuleVersionNum();
	}

	unsigned __int64 WINAPI GetTakionUtilsHeaderVersion() {
		return U_VersionStrToNum(TakionUtilsHeaderVersion);
	}

	unsigned __int64 WINAPI GetTakionGuiVersion() {
		return TGUI_GetModuleVersionNum();
	}

	unsigned __int64 WINAPI GetTakionGuiHeaderVersion() {
		return U_VersionStrToNum(TakionGuiHeaderVersion);
	}

	unsigned __int64 WINAPI GetTakionDataVersion() {
		return TD_GetModuleVersionNum();
	}

	unsigned __int64 WINAPI GetTakionDataHeaderVersion() {
		return U_VersionStrToNum(TakionDataHeaderVersion);
	}

	unsigned __int64 WINAPI GetTakionLogVersion() {
		return TL_GetModuleVersionNum();
	}

	unsigned __int64 WINAPI GetTakionLogHeaderVersion() {
		return U_VersionStrToNum(TakionLogHeaderVersion);
	}

	unsigned __int64 WINAPI GetObserverVersion() {
		return O_GetModuleVersionNum();
	}

	unsigned __int64 WINAPI GetObserverHeaderVersion() {
		return U_VersionStrToNum(ObserverHeaderVersion);
	}

	const char* WINAPI GetTakionExtensionDescription() {
		return theApp.GetFileDescription().c_str();
	}

	void WINAPI GetTakionExtensionMenu(std::string &menuStr) {
		if (!theApp.IsServerStarted()) {
			AddMenuItemToString(menuStr, "Open the Gate");
		} else {
			AddMenuItemToString(menuStr, "Close the Gate");
		}
	}

	void WINAPI ExecuteTakionCommand(
				unsigned short messageId,
				CWnd *takionExtensionWindow) {
		switch (messageId) {
			case  0:
				!theApp.IsServerStarted()
					?	StartServer()
					:	StopServer();
				break;
			default:
				TakionMessageBox mb(TGUI_GetTakionMainWnd());
				std::string info("Unknown Command ");
				char num[33] = {};
				info += U_UShortToStr(messageId, num, _countof(num));
				mb.AddMessage(info);
				mb.DisplayModal(
					takionExtensionWindow,
					"Extension Command",
					MB_OK | MB_ICONERROR);
				break;
		}
	}

	void WINAPI ExtensionInitialize() {
		theApp.GetMainDialog().CreateModeless(
			theApp.GetMainDialog().GetMainWnd());
		theApp.GetMainDialog().ShowWindow(SW_HIDE);
		messageBox.reset(new TakionMessageBox(TGUI_GetTakionMainWnd(), true));
		StartServer();
	}

	void WINAPI ExtensionTerminate() {
		if (theApp.IsServerStarted()) {
			StopServer();
		}
		messageBox->DestroyWindow();
		messageBox.reset();
	}

	void WINAPI ActiveMmBoxChanged(
			const char *  /*symbol*/,
			const Security * /*security*/,
			bool /*wasLoaded*/,
			unsigned int /*ordinal*/) {
		//...//
	}

	void WINAPI KeyStrokeAndCommand(
				unsigned char /*ascii*/,
				unsigned char /*modifier*/,
				bool /*repeat*/,
				const char * /*commandName*/,
				unsigned int /*extensionCode*/,
				unsigned int /*userExtensionCode*/) {
		//...//
	}

	void WINAPI SymbolEnteredInMmBox(
				const char * /*symbol*/,
				bool /*valid*/,
				bool /*fromKeyboard*/,
				unsigned int /*ordinal*/) {
		//...//
	}

	void WINAPI SecurityRefreshed(
				const char * /*symbol*/,
				const Security * /*security*/,
				bool /*wasLoaded*/,
				unsigned int /*ordinal*/) {
		//...//
	}

	void WINAPI TakionMoveWindows(int dx, int dy) {
		theApp.GetMainDialog().DragWindow(dx, dy);
	}

}

////////////////////////////////////////////////////////////////////////////////

