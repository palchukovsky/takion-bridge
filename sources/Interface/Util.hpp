/**************************************************************************
 *   Created: 2013/04/17 08:49:56
 *    Author: Eugene V. Palchukovsky
 *    E-mail: eugene@palchukovsky.com
 * -------------------------------------------------------------------
 *   Project: Takion Bridge
 **************************************************************************/

#pragma once

#include "Types.hpp"

namespace TakionBridge { namespace Interface {

	extern const PacketMagic beginPacketMagic;
	extern const PacketMagic endPacketMagic;

	unsigned short GetDefaultGatewayPort();

	bool CheckPacketMagics(const char *packetBuffer, size_t packetBufferLen);

	template<typename Packet>
	const Packet & ResolvePacket(const char *packetBuffer, size_t packetBufferLen) {
		if (!CheckPacketMagics(packetBuffer, packetBufferLen)) {
			throw std::exception("Protocol error: wrong packet magic");
		}
		return *reinterpret_cast<const Packet *>(
			packetBuffer + sizeof(PacketMagic));
	}

	template<typename Packet>
	size_t GetPacketSize() {
		return
			sizeof(TakionBridge::Interface::PacketMagic)
			+ sizeof(Packet)
			+ sizeof(TakionBridge::Interface::PacketMagic);
	}

} }
