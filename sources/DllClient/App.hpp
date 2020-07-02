/**************************************************************************
 *   Created: 2013/04/18 23:57:43
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace TakionBridge { namespace DllClient {

	class App : private boost::noncopyable {

	public:

		App();
		~App();

	public:

		Client & GetClient();
		const Client & GetClient() const;

	private:

		std::unique_ptr<Client> m_client;

	};

} }

////////////////////////////////////////////////////////////////////////////////

namespace TakionBridge { namespace DllClient {
	extern App theApp;
} }

////////////////////////////////////////////////////////////////////////////////
