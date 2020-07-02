/**************************************************************************
 *   Created: 2013/04/28 20:14:39
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#pragma once

#include "Interface/Requests.hpp"

namespace TakionBridge { namespace Gateway {

	////////////////////////////////////////////////////////////////////////////////

	class SecurityInfo : private boost::noncopyable {

	public:

		explicit SecurityInfo(
				const TakionBridge::Interface::Requests::SecurityInfoRequest &);
		~SecurityInfo();

	public:

		boost::shared_ptr<const TakionBridge::Interface::Requests::SecurityInfo>
		Execute();

	protected:

		bool IsOk() const {
			return m_stock ? true : false;
		}

		int GetPositionSize() const;
		::Price GetPositionPrice() const;

		const Security & GetStock() const {
			assert(m_stock);
			return *m_stock;
		}
		
	private:

		const TakionBridge::Interface::Requests::SecurityInfoRequest &m_request;

		Security *m_stock;
		const Account *m_account;
		const Position *m_position;

	};

	////////////////////////////////////////////////////////////////////////////////

	class PositionInfo : private boost::noncopyable {

	public:

		explicit PositionInfo(
				const TakionBridge::Interface::Requests::PositionInfoRequest &);
		virtual ~PositionInfo();

	public:

		boost::shared_ptr<const TakionBridge::Interface::Requests::PositionInfo>
		Execute();

	protected:

		bool IsOk() const {
			return m_stock ? true : false;
		}

		const Security & GetStock() const {
			assert(m_stock);
			return *m_stock;
		}
		
	private:

		const TakionBridge::Interface::Requests::PositionInfoRequest &m_request;

		Security *m_stock;
		const Account *m_account;
		const Position *m_position;

	};

	////////////////////////////////////////////////////////////////////////////////

} }
