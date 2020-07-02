/**************************************************************************
 *   Created: 2013/04/17 08:07:53
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#include "Prec.hpp"
#include "Server.hpp"
#include "Session.hpp"

using namespace TakionBridge;
using namespace TakionBridge::Gateway;

namespace io = boost::asio;
namespace ip = boost::asio::ip;

Server::Server(unsigned short port)
		//! @todo in production listen only loopback
		: m_acceptor(m_ioService, ip::tcp::endpoint(ip::tcp::v4(), port)) {
	StartAccept();
	m_threads.create_thread([this]() {Main();});
}

Server::~Server() {
	m_ioService.stop();
	m_threads.join_all();
}

void Server::Main() {
	m_ioService.run();
}

void Server::StartAccept() {
	boost::shared_ptr<Session> session(new Session(m_ioService));
	m_acceptor.async_accept(
		session->GetSocket(),
		boost::bind(
			&Server::HandleAccept,
			this,
			session,
			io::placeholders::error));
}

void Server::HandleAccept(
			boost::shared_ptr<Session> &session,
			const boost::system::error_code &error) {
    if (error) {
		return;
	}
	session->Start();
    StartAccept();
}
