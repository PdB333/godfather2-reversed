// FUNC_NAME: Player::hasActiveCrewMember
bool __fastcall Player::hasActiveCrewMember() {
    // Bit 0 of byte at +0x8E6 distinguishes two modes (single vs multiplayer)
    if ((this->field_0x8E6 & 1) == 0) {
        // Check two possible crew member pointers at +0x1C78 and +0x24FC
        void* crewRef = nullptr;
        if (this->field_0x1C78 != nullptr) {
            crewRef = this->field_0x1C78 - 0x48; // +0x1C78 points into a larger object
        } else if (this->field_0x24FC != nullptr) {
            crewRef = this->field_0x24FC - 0x48;
        }

        if (crewRef != nullptr) {
            // Virtual call at vtable+0x10 (4th function) – checks hashed property
            auto vtable = *(void***)crewRef;
            auto isMatch = reinterpret_cast<bool (__fastcall*)(void*, uint)>(vtable[4]);
            return isMatch(crewRef, 0x369AC561);
        }
    } else {
        // Multiplayer branch: sentinel check for invalid this (-0x3AC)
        if ((int)this != -0x3AC) {
            // Global manager lookup by hash 0xB47BB605
            void* manager = FUN_00625050(0xB47BB605, 0);
            if (manager != nullptr) {
                int* slotPtr = *(int**)((char*)manager + 0x1B4); // +0x1B4 pointer to slot
                if (slotPtr != nullptr && slotPtr != (int*)0x48) { // 0x48 sentinel
                    void* slotBase = (char*)slotPtr - 0x48;
                    return FUN_006BC8D0(slotBase, 0x369AC561);
                }
            }
        }
    }
    return false;
}