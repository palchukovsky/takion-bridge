/**************************************************************************
 *   Created: 2013/04/18 23:47:12
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#pragma once

namespace TakionBridge { namespace Gateway {

	class SettingDialog
		: public TakionSettingPageBase,
		public Observer {
	
	public:
	
		explicit SettingDialog(
				TakionMainWnd *mainWnd,
				TakionSettingTabDialog *parentTab);
	public:

		virtual HWND GetFirstTabControl();
		virtual void UpdateSettings();
		virtual void UpdateControls();
		virtual void Leaving();

	protected:
		
		void UpdateConnections();
		void UpdateConnection(const Connection* connection, bool isConnected);
		virtual void DoDataExchange(CDataExchange* dx);
		virtual BOOL OnInitDialog();
		virtual void BeforeDestroy();

		virtual void Notify(
				const Message* message,
				Observable* from,
				const Message* info);

	protected:
	
		afx_msg HBRUSH OnCtlColor(CDC* dC, CWnd* wnd, UINT ctlColor);
		afx_msg void OnSelchangeConnection();
		DECLARE_MESSAGE_MAP()

	private:

	
	};

} }
