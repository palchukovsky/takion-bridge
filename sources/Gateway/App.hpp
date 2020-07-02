/**************************************************************************
 *   Created: 2013/04/17 21:28:30
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace TakionBridge { namespace Gateway {

	class App : public CWinApp {

	public:

		typedef CWinApp Base;

	public:
		
		App();
		virtual ~App();

	public:
		
		virtual BOOL InitInstance();
		virtual int ExitInstance();

	public:

		bool IsServerStarted() const;
		void StartServer();
		void StopServer();

	public:

		MainDialog & GetMainDialog();

	public:
		
		const std::string & GetFilePathAndName() const {
			return m_filePathAndName;
		}
		
		const std::string & GetFileDescription() const {
			return m_fileDescription;
		}
		
		const std::string & GetPlatform() const {
			return m_platform;
		}
		
		const std::string & GetVersionStr() const {
			return m_versionStr;
		}
		
		const unsigned __int64 & GetVersionNum() const {
			return m_versionNum;
		}

	protected:

		std::string m_filePathAndName;
		std::string m_fileDescription;
		std::string m_platform;
		std::string m_versionStr;
		unsigned __int64 m_versionNum;

		std::unique_ptr<MainDialog> m_mainDialog;

		std::unique_ptr<Server> m_server;

	};

} }

////////////////////////////////////////////////////////////////////////////////

namespace TakionBridge { namespace Gateway {
	extern App theApp;
} }

////////////////////////////////////////////////////////////////////////////////
