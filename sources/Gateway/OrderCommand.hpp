 /**************************************************************************
  *   Created: 2013/04/23 21:07:05
  *    Author: Eugene V. Palchukovsky
  *    E-mail: eugene@palchukovsky.com
  * -------------------------------------------------------------------
  *   Project: Takion Bridge
  **************************************************************************/
 
 #pragma once

#include "Interface/Types.hpp"
#include "Interface/Commands.hpp"

namespace TakionBridge { namespace Gateway {

	////////////////////////////////////////////////////////////////////////////////

	class OrderCommand : private boost::noncopyable {

	public:

		class Exception : public std::exception {
		public:
			Exception(
					TakionBridge::Interface::Commands::Response::Status,
					const char *what);
		public:
			TakionBridge::Interface::Commands::Response::Status GetStatus()
					const;
		private:
			TakionBridge::Interface::Commands::Response::Status m_status;
		};

	public:

		explicit OrderCommand(const TakionBridge::Interface::Symbol &symbol);
		virtual ~OrderCommand();

	public:

		boost::shared_ptr<const TakionBridge::Interface::Commands::Response>
		Execute();

	protected:

		virtual unsigned char SendOrder() = 0;

		bool IsOk() const {
			return m_stock ? true : false;
		}

		int GetPositionSize() const;
		::Price GetPositionPrice() const;

		Security & GetStock() {
			assert(m_stock);
			return *m_stock;
		}

		const Security & GetStock() const {
			return const_cast<OrderCommand *>(this)->GetStock();
		}
		
		Account & GetAccount() {
			assert(m_account);
			return *m_account;
		}

		
		::Price GetLevel1Bid() const;
		::Price GetLevel1Ask() const;
	  ::Price GetLastPrice() const;

		static char GetSide(TakionBridge::Interface::OrderSide);

	private:

		void SetResponse(
					TakionBridge::Interface::Commands::Response::Status,
					const char *text);
		void SetResponse(const Exception &);

	private:

		boost::shared_ptr<TakionBridge::Interface::Commands::Response>
			m_response;
		
		Security *m_stock;
		Account *m_account;
		const Position *m_position;


	};

	////////////////////////////////////////////////////////////////////////////////

	class MarketOrderCommand : public OrderCommand {

	public:

		typedef OrderCommand Base;

	public:
			
		explicit MarketOrderCommand(
				const TakionBridge::Interface::Commands::MarketOrder &orderRef);
		virtual ~MarketOrderCommand();

	protected:

		virtual unsigned char SendOrder();

		virtual TakionBridge::Interface::Price GetStopPrice() const {
			return .0;
		}

		virtual unsigned char GetOrderType() const {
			return ORDER_TYPE_MARKET;
		}

		virtual unsigned char GetStopType() const {
			return OST_NONE;
		}

	private:

		const TakionBridge::Interface::Commands::MarketOrder &m_order;

	};

	class MarketOrderWithStopPriceCommand : public MarketOrderCommand {

	public:

		typedef MarketOrderCommand Base;

	public:
			
		explicit MarketOrderWithStopPriceCommand(
				const TakionBridge::Interface::Commands::MarketOrderWithStopPrice &orderRef);
		virtual ~MarketOrderWithStopPriceCommand();

	protected:

		virtual TakionBridge::Interface::Price GetStopPrice() const {
			return m_stopPrice;
		}

		virtual unsigned char GetOrderType() const {
			return ORDER_TYPE_STOP;
		}

		virtual unsigned char GetStopType() const {
			return OST_NATIVE;
		}

	private:

		const TakionBridge::Interface::Price m_stopPrice;

	};

	////////////////////////////////////////////////////////////////////////////////

	class LimitOrderCommand : public OrderCommand {

	public:

		typedef OrderCommand Base;

	public:
			
		explicit LimitOrderCommand(
				const TakionBridge::Interface::Commands::LimitOrder &orderRef);
		virtual ~LimitOrderCommand();

	protected:

		virtual unsigned char SendOrder();

	private:

		const TakionBridge::Interface::Commands::LimitOrder &m_order;

	};

	////////////////////////////////////////////////////////////////////////////////

} }
