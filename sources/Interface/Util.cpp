/**************************************************************************
 *   Created: 2013/04/17 08:49:46
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#include "Prec.hpp"
#include "Util.hpp"

using namespace TakionBridge;
using namespace TakionBridge::Interface;

////////////////////////////////////////////////////////////////////////////////

namespace TakionBridge { namespace Interface {

	const PacketMagic beginPacketMagic = {0xF, 0xA};
	const PacketMagic endPacketMagic = {0xB, 0xD};

	unsigned short GetDefaultGatewayPort() {
		return 1419;
	}

	bool CheckPacketMagics(const char *buffer, size_t bufferLen) {
		assert(buffer);
		assert(bufferLen > sizeof(PacketMagic) * 2);
		if (bufferLen <= sizeof(PacketMagic) * 2) {
			return false;
		}
		return
			!memcmp(
					buffer + bufferLen - sizeof(PacketMagic),
					endPacketMagic,
					sizeof(beginPacketMagic))
			&& !memcmp(buffer, beginPacketMagic, sizeof(beginPacketMagic));
	}

} }

////////////////////////////////////////////////////////////////////////////////
