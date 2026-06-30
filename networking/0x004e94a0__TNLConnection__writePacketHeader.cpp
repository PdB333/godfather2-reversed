// FUNC_NAME: TNLConnection::writePacketHeader
#include <cstdint>

// Global pointer accessed through TLS (FS:[0x2c])
static inline int* getEngineGlobals() {
    int** pGlobalPtr = (int**)__readfsdword(0x2c);
    return *pGlobalPtr;
}

// Forward declaration of helper function called after copy
extern void finalizePacket();

void TNLConnection::writePacketHeader(const uint32_t* data, uint32_t param2) {
    int* engineGlobals = getEngineGlobals();
    int* base = (int*)engineGlobals[2];                                // engineGlobals+8

    // Copy 16 bytes from data into the slot buffer
    int* dest = (int*)((char*)base + 0x40 + *(int*)((char*)this + 0x18)); // slot offset
    dest[0] = data[0];
    dest[1] = data[1];
    dest[2] = data[2];
    dest[3] = data[3];

    finalizePacket();

    // Store extra value at offset 0x88 in the same slot
    *(uint32_t*)((char*)base + 0x88 + *(int*)((char*)this + 0x18)) = param2;
}