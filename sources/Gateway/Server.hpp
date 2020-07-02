/**************************************************************************
 *   Created: 2013/04/17 08:08:03
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#pragma once

namespace TakionBridge { namespace Gateway {

	class Server : private boost::noncopyable {

	public:

		explicit Server(unsigned short port);
		~Server();

	private:

		void StartAccept();
		void HandleAccept(
				boost::shared_ptr<Session> &,
				const boost::system::error_code&);

		void Main();

	private:

		boost::asio::io_service m_ioService;
		boost::asio::ip::tcp::acceptor m_acceptor;

		boost::thread_group m_threads;

	};

} }
