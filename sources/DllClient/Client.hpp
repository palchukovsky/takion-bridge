/**************************************************************************
 *   Created: 2013/04/18 23:56:52
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#pragma once

#include "Interface/Commands.hpp"
#include "Interface/Requests.hpp"
#include "Interface/Types.hpp"

namespace TakionBridge { namespace DllClient {

	class Client : private boost::noncopyable {

	public:

		explicit Client(const char *host, unsigned short port);
		~Client();

	public:

		const std::string & GetConnectionInfo() const {
			return m_connectionInfo;
		}

	public:

		TakionBridge::Interface::Commands::Response::Status SendMarketOrder(
					const char *symbol,
					TakionBridge::Interface::OrderSide,
					TakionBridge::Interface::Qty);
		TakionBridge::Interface::Commands::Response::Status
		SendMarketOrderWithStopPrice(
					const char *symbol,
					TakionBridge::Interface::OrderSide,
					TakionBridge::Interface::Qty,
					TakionBridge::Interface::Price stopPrice);

		TakionBridge::Interface::Commands::Response::Status SendLimitOrder(
					const char *symbol,
					TakionBridge::Interface::OrderSide,
					TakionBridge::Interface::Qty,
					TakionBridge::Interface::Price);

		const char * GetLastSendErrorText() const throw();

		boost::shared_ptr<const TakionBridge::Interface::Requests::SecurityInfo>
		GetSecurityInfo(
					const char *symbol)
				const;

		boost::shared_ptr<const TakionBridge::Interface::Requests::PositionInfo>
		GetPositionInfo(
					const char *symbol)
				const;

	protected:

		template<typename Order>
		void SendOrder(const Order &);

	private:

		std::string m_connectionInfo;
		mutable TakionBridge::Interface::Commands::Response m_lastResponse;

		std::unique_ptr<Connection> m_connection;

	};

} }
