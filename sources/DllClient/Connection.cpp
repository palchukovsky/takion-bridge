/**************************************************************************
 *   Created: 2013/04/25 00:54:27
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#include "Prec.hpp"
#include "Connection.hpp"

using namespace TakionBridge::DllClient;

namespace io = boost::asio;
namespace ip = boost::asio::ip;

Connection::Connection(const char *host, unsigned short port)
		: m_socket(m_ioService) {

	std::ostringstream service;
	service << port;
	
	ip::tcp::resolver::query query(host, service.str());
	ip::tcp::resolver resolver(m_ioService);
	ip::tcp::resolver::iterator endpointIt = resolver.resolve(query);

	io::connect(m_socket, endpointIt);

}

Connection::~Connection() {
	//...//
}

