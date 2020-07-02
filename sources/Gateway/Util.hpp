/**************************************************************************
 *   Created: 2013/04/28 21:53:09
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#pragma once

namespace TakionBridge { namespace Gateway {

	inline ::Price PriceToPrice(Interface::Price price) {
		const unsigned int dollarFraction
			= unsigned int((price - double(unsigned int(price))) * ::Price::divider);
		return ::Price(unsigned int(price), dollarFraction);
	}

	inline Interface::Price PriceToPrice(::Money money) {
		return
			double(money.GetDollarsRef())
				+ (double(money.GetDollarFractionRef())
					/ double(::Money::divider));
	}

} }
