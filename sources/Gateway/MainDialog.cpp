/**************************************************************************
 *   Created: 2013/04/18 08:58:04
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#include "Prec.hpp"
#include "MainDialog.hpp"

using namespace TakionBridge::Gateway;

MainDialog::MainDialog()
		: TakionSettingTopDialog(TGUI_GetTakionMainWnd(), 100, 100) {
	//...//
}

void MainDialog::Top() {
	if (!m_hWnd) {
		return;
	}
	bool visible = !::IsWindowVisible(m_hWnd);
	::SetWindowPos(
		m_hWnd,
		HWND_TOP,
		0,
		0,
		0,
		0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	if (visible) {
		Entering();
	}
}

void MainDialog::FinishDialog(int result) {
	TakionSettingTopDialog::FinishDialog(result);
}

void MainDialog::Apply() {
	UpdateSettings();
}

BOOL MainDialog::OnInitDialog() {
	TakionMainWnd *const frame = TGUI_GetTakionMainWnd();
	TakionSettingTabDialog &tabDialog
		= *new TakionSettingTabDialog(frame, this, "Takion Bridge Gateway");
	AddSettingDialog(&tabDialog);
	return TakionSettingTopDialog::OnInitDialog();
}
