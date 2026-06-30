// FUNC_NAME: Entity::checkAndSetActiveFlag
void __fastcall Entity::checkAndSetActiveFlag(void* thisPtr) {
    // thisPtr points to an Entity or derived object
    int* flags = (int*)((char*)thisPtr + 0x34);   // +0x34: bitfield flags
    int* state = (int*)((char*)thisPtr + 0xC4);   // +0xC4: state variable (0=inactive? 1=active? etc.)
    int* typeId = (int*)((char*)thisPtr + 0x40);  // +0x40: type identifier (hash or enum)

    // Condition: state is 0 or 1, and typeId is not a specific value (0x637b907 likely represents "dead" or "removed"),
    // and bit4 of flags is clear, and bit23 is clear.
    if ((*state == 1 || *state == 0) &&
        (*typeId != 0x637b907) &&
        ((~((unsigned char)(*flags >> 4) & 1) != 0) &&  // bit4 == 0
         (((*flags >> 0x17) & 1) == 0))) {              // bit23 == 0

        // Call a subfunction that likely checks additional object validity (e.g., isInWorld, isAlive)
        bool isConditionMet = FUN_008c7f80(thisPtr);  // returns non-zero if true
        if (isConditionMet) {
            // Set bit23 (0x800000) in flags - possibly "active" or "in use"
            *flags |= 0x800000;
        }
    }
}