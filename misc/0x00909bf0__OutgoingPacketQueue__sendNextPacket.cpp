// FUNC_NAME: OutgoingPacketQueue::sendNextPacket

#include <cstdint>

// Constants (guessed from decompiled logic)
const uint32_t kPacketFlagEmpty = 0x48; // 72 - possibly identifies an empty/invalid packet slot

// Function that attempts to send a packet via session; returns true if sent successfully
extern bool trySendPacket(uint32_t sessionHandle, uint32_t arg2, int32_t packetId);

// Function called after successful send; returns some result (maybe sequence number or status)
extern uint32_t completePacketSend(int32_t packetId);

// __thiscall: this = ecx
uint32_t __thiscall OutgoingPacketQueue::sendNextPacket(uint32_t sessionHandle, uint32_t arg2) {
    // Early exit if we have a current packet ID that is not empty, or if a flag is set
    uint32_t currentId = *(uint32_t*)(this + 0x64); // mCurrentPacketID
    if ((currentId != 0 && currentId != kPacketFlagEmpty) || (*(uint8_t*)(this + 0xB4) & 0x01) != 0) {
        return currentId & 0xFFFFFF00; // Return high 24 bits (maybe packet type or status)
    }

    int32_t packetsRemaining = *(int32_t*)(this + 0x60); // mPacketCount
    int32_t retries = 5; // Maximum attempts to find a valid packet to send

    do {
        if (packetsRemaining == 0) break; // No more packets to check

        uint32_t currentIndex = *(uint32_t*)(this + 0x6C); // mCurrentIndex
        if (*(uint32_t*)(this + 0x58) <= currentIndex) {
            *(uint32_t*)(this + 0x6C) = 0; // Wrap around index if past end
            currentIndex = 0;
        }

        // Each entry is 8 bytes; first 4 bytes are packet ID/type
        uint32_t* entryPtr = *(uint32_t**)(this + 0x54) + currentIndex * 2; // 8-byte stride
        uint32_t packetType = *entryPtr;

        if (packetType != 0) {
            int32_t packetId = packetType - kPacketFlagEmpty;
            if (packetId != 0) { // Packet is not the special empty type
                if (trySendPacket(sessionHandle, arg2, packetId)) {
                    return completePacketSend(packetId);
                }
                retries--; // Decrement retry count on failed send attempt
            }
        }

        packetsRemaining--;
        *(uint32_t*)(this + 0x6C) = currentIndex + 1; // Advance index
    } while (retries != 0);

    // Return the original current ID (masked) if no packet was sent
    return currentId & 0xFFFFFF00;
}