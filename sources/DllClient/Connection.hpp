/**************************************************************************
 *   Created: 2013/04/25 00:51:09
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#pragma once

#include "Interface/Util.hpp"

namespace TakionBridge { namespace DllClient {

	class Connection
		: private boost::noncopyable,
		boost::enable_shared_from_this<Connection> {

	public:

		explicit Connection(const char *host, unsigned short port);
		~Connection();

	public:

		template<typename Command, typename Response>
		void SendMessage(const Command &command, Response &response) {
			
			namespace io = boost::asio;
			namespace ip = boost::asio::ip;
			using namespace TakionBridge::Interface;
			
			m_buffer.resize(GetPacketSize<Command>());
			size_t offset = 0;

			const auto messageId = command.GetId();
			io::write(m_socket, io::buffer(&messageId, sizeof(messageId)));
			
			memcpy(
				&m_buffer[offset],
				&beginPacketMagic,
				sizeof(beginPacketMagic));
			offset += sizeof(beginPacketMagic);
			
			memcpy(
				&m_buffer[offset],
				&command,
				sizeof(command));
			offset += sizeof(command);

			memcpy(
				&m_buffer[offset],
				&endPacketMagic,
				sizeof(endPacketMagic));

			io::write(
				m_socket,
				io::buffer(&m_buffer[0], m_buffer.size()));

			io::read(m_socket, io::buffer(&response, sizeof(response)));

		}

	public:

		boost::asio::io_service m_ioService;
		boost::asio::ip::tcp::socket m_socket;

		std::vector<char> m_buffer;

	};

} }
