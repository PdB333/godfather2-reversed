// FUNC_NAME: TNLConnection::initConnectionData
void __fastcall TNLConnection::initConnectionData(int *thisPtr)
{
    // Fetch session identifier from global game manager at DAT_01223480
    // Offset 0x54 gets a pointer, then +0x48 reads a uint32 (likely session token)
    uint32_t sessionToken = *(uint32_t *)(*(int *)(DAT_01223480 + 0x54) + 0x48);

    // Call virtual method at vtable index 0x8B (0x22c / 4) – returns a byte
    // Likely getFlags() or getNetworkRole()
    byte flags = (*(code **)(*thisPtr + 0x22c))();

    // Get a random/timestamp value from system function
    uint32_t randomValue = getTimestamp(); // FUN_0043b490

    // Build a 64-bit sequence number:
    // upper 32 bits = sessionToken
    // lower 32 bits = (randomValue & 0xfff) << 16 | 0x3e5 (0x3e5 = initial sequence base)
    uint64_t sendSequence = sessionToken;
    sendSequence = (sendSequence << 32) | ((randomValue & 0xfff) << 16 | 0x3e5);
    *(uint64_t *)(thisPtr + 0xcf) = sendSequence;  // +0x33C

    // Another 64-bit field: shift 1 by lower 5 bits of flags
    uint64_t receiveSequence = (uint64_t)(uint32_t)(1 << (flags & 0x1f));
    *(uint64_t *)(thisPtr + 0xd1) = receiveSequence; // +0x344

    // Zero out a related counter
    thisPtr[0xd3] = 0;  // +0x34C

    // Pass the value at offset +0x360 to an external cleanup function
    externDecRefCount(thisPtr[0xd8]);  // FUN_009eace0

    // Call three subsystem inits
    initNetLayers();  // FUN_0055d970
    initPacketBuffers();  // FUN_0055d870
    initAckTable();  // FUN_0055dbd0
}