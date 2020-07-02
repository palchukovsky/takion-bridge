/**************************************************************************
 *   Created: 2013/04/17 08:20:20
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#pragma once

#include "Interface/Commands.hpp"

namespace TakionBridge { namespace Gateway {

	class Session
		: private boost::noncopyable,
		public boost::enable_shared_from_this<Session> {

// 		template<typename Command, typename Registration>
// 		friend void RegisterCommand(Registration &, Session &);

	private:

		typedef std::pair<
				size_t, /* packet size */
				boost::function<void (const std::vector<char> &)>>
			Handler;
		typedef std::map<Interface::MessageId, Handler> Handlers;

	public:

		explicit Session(boost::asio::io_service &);
		~Session();

	public:

		boost::asio::ip::tcp::socket & GetSocket() {
			return m_socket;
		}

		void Start();

	private:

		void StartReadCommandId();
		void StartReadCommand();

		template<typename Answer>
		void SendAnswer(boost::shared_ptr<const Answer>);
		template<typename Answer>
		void HandleAnswerWrite(
					boost::shared_ptr<const Answer>,
					const boost::system::error_code &);
		
		void HandleReadCommandId(const boost::system::error_code &);
		void HandleReadCommand(const boost::system::error_code &);

	private:

		template<typename Command>
		void RegisterMessage();

	private:

		boost::asio::ip::tcp::socket m_socket;

		Handlers m_handlers;

		struct {
			Interface::MessageId messageId;
			std::vector<char> commandBuffer;
		} m_in;

	};

} }
