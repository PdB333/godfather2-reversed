// FUNC_NAME: ScriptParser::readValue
int ScriptParser::readValue() {
    int* pBase = reinterpret_cast<int*>(*(int*)(this + 0xC));  // +0xC: base of token buffer
    int* pCurrent = reinterpret_cast<int*>(*(int*)(this + 0x8)); // +0x8: current position
    int* pNext = pBase + 2; // +8 bytes (one token ahead)

    // Check if we have room or if the next token is a sentinel (-1)
    if ((pCurrent <= pNext) || (pNext == nullptr) || (*pNext == -1)) {
        error(this, 2, "value expected"); // FUN_00627a20
        // Note: ECX/EDX may be restored on error, but we ignore for reconstruction
    }

    // Clear buffer from current position to base+0x10 (16 bytes) if needed
    if (pCurrent < pBase + 4) { // 4 ints = 16 bytes
        do {
            *reinterpret_cast<int**>(this + 0x8)[0] = 0;
            *reinterpret_cast<int*>(this + 0x8) += 8; // advance by 8 bytes
        } while (*reinterpret_cast<int*>(this + 0x8) < reinterpret_cast<int>(pBase + 4));
    }

    // Set current to base+16 (two tokens ahead) and shift buffer
    int* pTarget = pBase; // base
    int* pSrc = pTarget + 4; // base + 16 bytes
    *reinterpret_cast<int**>(this + 0x8) = pSrc;

    // Shift the buffer: copy tokens from start to end (reverse order)
    for (; pTarget < pSrc; pSrc -= 2) {
        pSrc[0] = pSrc[-2];
        pSrc[1] = pSrc[-1];
    }

    // Insert the token that was at the new current position into the first slot
    pSrc = *reinterpret_cast<int**>(this + 0x8);
    pTarget[0] = pSrc[0];
    pTarget[1] = pSrc[1];

    // Set up compare parameters: use current-8 as left value
    int localStack[3]; // actually used as pair for comparison
    localStack[0] = *reinterpret_cast<int*>(this + 0x8) - 8;
    localStack[1] = -1;

    // Perform comparison (likely "less than" or "equality") against the stack base
    int compareResult = compareValues(&LAB_006261e0, localStack, localStack[0] - *(int*)(this + 0x1C)); // FUN_00636570

    // Write result token: type=1, value=compareResult==0
    pSrc = *reinterpret_cast<int**>(this + 0x8);
    pSrc[0] = 1;
    pSrc[1] = (compareResult == 0) ? 1 : 0;

    // Advance current
    *reinterpret_cast<int*>(this + 0x8) += 8;

    // Copy the just-written token back to the base position
    int* newCurrent = reinterpret_cast<int*>(*reinterpret_cast<int*>(this + 0x8));
    pTarget = reinterpret_cast<int*>(*reinterpret_cast<int*>(this + 0xC));
    pTarget[0] = newCurrent[-2];
    pTarget[1] = newCurrent[-1];
    *reinterpret_cast<int*>(this + 0x8) -= 8;

    // Return number of tokens in buffer
    return (*reinterpret_cast<int*>(this + 0x8) - *reinterpret_cast<int*>(this + 0xC)) >> 3;
}