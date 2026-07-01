//FUNC_NAME: Entity::isConscious
// Function address: 0x0093a070
// Role: Checks if entity is alive, not dead, and not stunned (or similar state)
// Offsets:
//   +0x48: byte - alive flag (non-zero = alive)
//   +0x5c: uint - bitfield of flags (bit 19 = dead flag, 0 = alive)
//   +0x60: int - stun timer or health (must be < 1 to be conscious)

int __thiscall Entity::isConscious(void* thisPtr) {
    // Check if alive byte is non-zero
    if (*(char*)((int)thisPtr + 0x48) != 0) {
        // Check that dead flag (bit 19) is not set
        if ((*(unsigned int*)((int)thisPtr + 0x5c) >> 0x13 & 1) == 0) {
            // Check that stun timer/health is less than 1 (i.e., not stunned or alive)
            if (*(int*)((int)thisPtr + 0x60) < 1) {
                return 1;
            }
        }
    }
    return 0;
}