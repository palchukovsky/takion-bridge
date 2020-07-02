/**************************************************************************
 *   Created: 2013/04/18 23:55:24
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include "Fwd.hpp"

////////////////////////////////////////////////////////////////////////////////

#pragma warning(push, 3)
#pragma warning(disable: 4180)
#pragma warning(disable: 4702)
#pragma warning(disable: 4267)
#pragma warning(disable: 4244)

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

#pragma warning(pop)

#include <stdint.h>
#include <exception>

#include <Windows.h>

////////////////////////////////////////////////////////////////////////////////
