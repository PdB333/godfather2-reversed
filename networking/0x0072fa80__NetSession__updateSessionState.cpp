// FUNC_NAME: NetSession::updateSessionState
int __fastcall NetSession::updateSessionState(NetSession* thisPtr) {
    int status;

    // Global check: likely platform or game mode state
    status = getGamePlatformState(); // FUN_0077dd80
    if (status != 3) {
        // Return error code if not in correct state (e.g., not in game)
        return -0x57f3644a; // 0xA80C9BB6
    }

    // Read flags at offset +0x1f5c (bitfield)
    uint flags = *(uint*)((char*)thisPtr + 0x1f5c);

    // Check bit 23 (synchronization flag?)
    if ((flags >> 0x17) & 1) {
        // If bit 23 is set, compute result based on bit 22
        // Uses a conditional mask and addition to produce a specific value
        uint bit22 = (flags >> 0x16) & 1;
        int result = (-(uint)(bit22 != 0) & 0xe9952a6d) + 0x8bbdce97;
        return result;
    }

    // Otherwise run the next update step
    status = executeUpdateStep(); // FUN_0072f880
    return status;
}