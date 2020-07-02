/**************************************************************************
 *   Created: 2013/04/17 08:07:39
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#pragma once

//////////////////////////////////////////////////////////////////////////

#include "Fwd.h"

//////////////////////////////////////////////////////////////////////////

#ifndef VC_EXTRALEAN
	// Exclude rarely-used stuff from Windows headers
#	define VC_EXTRALEAN
#endif

//////////////////////////////////////////////////////////////////////////

// some CString constructors will be explicit
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

// MFC core and standard components
#include <afxwin.h>
// MFC extensions
#include <afxext.h>

#ifndef _AFX_NO_AFXCMN_SUPPORT
	// MFC support for Windows Common Controls
#	include <afxcmn.h>
#endif

#include <afxtempl.h>
#include <afxdtctl.h>

//////////////////////////////////////////////////////////////////////////

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
#include <boost/function.hpp>
#include <boost/thread.hpp>

#pragma warning(pop)

//////////////////////////////////////////////////////////////////////////

#include <string>
#include <set>
#include <hash_map>
#include <hash_set>
#include <stdint.h>
#include <exception>

//////////////////////////////////////////////////////////////////////////

#pragma warning(push, 3)

#include <UtilsApi.h>
#include <TakionUtilsApi.h>
#include <TakionMemoryApi.h>
#include <TakionLogApi.h>
#include <TakionGui.h>
#include <TakionDataApi.h>
#include <ObserverApi.h>

#pragma warning(pop)

//////////////////////////////////////////////////////////////////////////
