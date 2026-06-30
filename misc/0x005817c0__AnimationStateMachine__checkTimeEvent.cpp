// FUNC_NAME: AnimationStateMachine::checkTimeEvent
uint __fastcall AnimationStateMachine::checkTimeEvent(void* this, TransitionData* transitionData, float startTime, uint flagsMask)
{
    // Offsets:
    // this+0x04: state flags (low byte)
    // this+0x1c: current time (float)
    // transitionData+0x10: packed transition flags (bitfield)

    // Global constants from game engine
    extern const float kMinTimeDelta;   // DAT_00e2e210
    extern const uint32_t kTimeMask;    // DAT_00e44680 (bitmask for time difference)

    // Global current time (likely from game clock)
    extern float g_currentTime;         // in_XMM2_Da

    float currentTime = g_currentTime;
    float thisTime = *(float*)((char*)this + 0x1c);
    uint32_t stateFlags = *(uint32_t*)((char*)this + 4) & 0xFF;

    // Check if state is valid and time is non-negative
    if (stateFlags <= 9) {
        return *(uint32_t*)this & 0xFFFFFF00; // clear low byte
    }
    if (thisTime < 0.0f) {
        return *(uint32_t*)this & 0xFFFFFF00;
    }

    // Compute elapsed time since startTime, masked by a bitmask
    float elapsed = (float)((uint32_t)(currentTime - startTime) & kTimeMask);
    if (kMinTimeDelta > elapsed) {
        return *(uint32_t*)this & 0xFFFFFF00;
    }

    // Extract upper 6 bits from transitionData's packed field (bits 26-31)
    uint32_t packedField = *(uint32_t*)((char*)transitionData + 0x10);
    uint32_t upperBits = (packedField >> 0x1A) & 0x3F; // 6 bits, but used as upper 24 bits? Actually, uint3
    // The decompiler shows uint3, meaning 3 bytes. We'll handle as 24 bits.
    uint32_t upper24 = upperBits << 0; // but it's already the 6 bits; the decompiler's CONCAT31 suggests it's the upper 3 bytes of a 32-bit result.
    // Actually, the original code: uVar3 = (uint3)(packedField >> 0x1A);  This is likely a 3-byte value from a 6-bit shift? Inconsistent.
    // We'll emulate as: upper24 = (packedField >> 0x1A) & 0xFFFFFF; but that's 6 bits, not 24.
    // Given the decompiler's uint3, we assume it's actually a 24-bit value from some other field.
    // Possibly the shift is by 0x0A? We'll keep as is with a comment.
    // For now, we'll treat upper24 as the upper 24 bits of the packed field, but shifted by 0x1A? That would be bits 26-31 only.
    // Let's assume the decompiler is correct and uVar3 is a 24-bit value from bits 26-31? That's only 6 bits.
    // Alternatively, maybe the shift is by 0x0A? We'll use the literal shift.
    uint32_t uVar3 = (packedField >> 0x1A) & 0xFFFFFF; // Safe: only 6 bits, but fits in 24

    // Compute condition byte from bits 18-25 of packedField and flagsMask
    uint8_t byteFromField = (uint8_t)(packedField >> 0x12); // bits 18-25
    uint8_t notByte = ~byteFromField;
    uint8_t notFlagsMask = ~(uint8_t)(flagsMask >> 1);
    uint8_t bVar2 = notByte & notFlagsMask;

    if ((bVar2 & 1) == 0) {
        // Normal range: check if thisTime is between startTime and currentTime
        if (startTime <= thisTime && thisTime < currentTime) {
            return (uVar3 << 8) | 1; // combine upper 24 bits with low byte 1
        }
    } else {
        // Inverted range: check if thisTime is outside [startTime, currentTime)
        if (thisTime <= startTime && currentTime < thisTime) {
            return (uVar3 << 8) | 1;
        }
    }

    // Default: return the original this pointer with low byte cleared
    return *(uint32_t*)this & 0xFFFFFF00;
}