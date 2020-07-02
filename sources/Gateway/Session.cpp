/**************************************************************************
 *   Created: 2013/04/17 08:20:14
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#include "Prec.hpp"
#include "Session.hpp"
#include "OrderCommand.hpp"
#include "RequestAnswer.hpp"
#include "Interface/Util.hpp"

using namespace TakionBridge;
using namespace TakionBridge::Gateway;
using namespace TakionBridge::Interface;

namespace io = boost::asio;
namespace ip = boost::asio::ip;


Session::Session(io::io_service &ioService)
		: m_socket(ioService) {
	RegisterMessage<Commands::MarketOrder>();
	RegisterMessage<Commands::MarketOrderWithStopPrice>();
	RegisterMessage<Commands::LimitOrder>();
	RegisterMessage<Requests::SecurityInfoRequest>();
	RegisterMessage<Requests::PositionInfoRequest>();
}

Session::~Session() {
	//...//
}


namespace {

	////////////////////////////////////////////////////////////////////////////////

	template<typename Command>
	struct MessageToImplementation {
		//...//
	};

	template<>
	struct MessageToImplementation<
				TakionBridge::Interface::Commands::MarketOrder> {
		typedef TakionBridge::Gateway::MarketOrderCommand Implementation;
	};

	template<>
	struct MessageToImplementation<
				TakionBridge::Interface::Commands::MarketOrderWithStopPrice> {
		typedef TakionBridge::Gateway::MarketOrderWithStopPriceCommand
			Implementation;
	};

	template<>
	struct MessageToImplementation<
				TakionBridge::Interface::Commands::LimitOrder> {
		typedef TakionBridge::Gateway::LimitOrderCommand Implementation;
	};

	template<>
	struct MessageToImplementation<
				TakionBridge::Interface::Requests::SecurityInfoRequest> {
		typedef TakionBridge::Gateway::SecurityInfo Implementation;
	};

	template<>
	struct MessageToImplementation<
				TakionBridge::Interface::Requests::PositionInfoRequest> {
		typedef TakionBridge::Gateway::PositionInfo Implementation;
	};

}

template<typename Message>
void Session::RegisterMessage() {

	typedef typename MessageToImplementation<Message>::Implementation
		Implementation;

	assert(m_handlers.find(Message::GetId()) == m_handlers.end());
	const auto handler = [this](const std::vector<char> &buffer) {
		Implementation impl(ResolvePacket<Message>(&buffer[0], buffer.size()));
		const auto response = impl.Execute();
		SendAnswer(response);
	};

	m_handlers[Message::GetId()].first = GetPacketSize<Message>();
	m_handlers[Message::GetId()].second = handler;

}

void Session::Start() {
	StartReadCommandId();
}

void Session::StartReadCommandId() {
	m_in.messageId = MESSAGE_ID_UNKNOWN;
	m_in.commandBuffer.clear();
	io::async_read(
		m_socket,
		io::buffer(&m_in.messageId, sizeof(m_in.messageId)),
		boost::bind(
			&Session::HandleReadCommandId,
			shared_from_this(),
			io::placeholders::error));
}

void Session::HandleReadCommandId(const boost::system::error_code &error) {
	assert(m_in.commandBuffer.empty());
	if (error) {
		return;
	}
	const Handlers::const_iterator i = m_handlers.find(m_in.messageId);
	assert(i != m_handlers.end());
	if (i == m_handlers.end()) {
		return;
	}
	m_in.commandBuffer.resize(i->second.first);
	StartReadCommand();
}

void Session::HandleReadCommand(const boost::system::error_code &error) {
	if (error) {
		return;
	}
	try {
		const Handlers::const_iterator i = m_handlers.find(m_in.messageId);
		assert(i != m_handlers.end());
		if (i == m_handlers.end()) {
			return;
		}
		i->second.second(m_in.commandBuffer);
	} catch (const std::exception &) {
		return;
	}
}

void Session::StartReadCommand() {
	assert(!m_in.commandBuffer.empty());
	memset(&m_in.commandBuffer[0], 0, m_in.commandBuffer.size());
	io::async_read(
		m_socket,
		io::buffer(&m_in.commandBuffer[0], m_in.commandBuffer.size()),
		boost::bind(
			&Session::HandleReadCommand,
			shared_from_this(),
			io::placeholders::error));
}

template<typename Answer>
void Session::SendAnswer(boost::shared_ptr<const Answer> answer) {
	io::async_write(
		m_socket,
        io::buffer(&*answer, sizeof(*answer)),
		boost::bind(
			&Session::HandleAnswerWrite<Answer>,
			shared_from_this(),
			answer,
			io::placeholders::error));
}

template<typename Answer>
void Session::HandleAnswerWrite(
			boost::shared_ptr<const Answer>,
			const boost::system::error_code &error) {
	if (error) {
		return;
	}
	StartReadCommandId();
}

////////////////////////////////////////////////////////////////////////////////
