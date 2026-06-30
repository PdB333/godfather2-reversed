// FUNC_NAME: InputManager::disconnectController

// InputManager member fields (offsets relative to this):
// +0x6a: controllerSlots[16][0x44]  // each slot: 0x44 bytes
//   Within each slot:
//   +0x2c: uint32 field_0x2c
//   +0x30: uint32 field_0x30
//   +0x34: uint32 field_0x34
//   +0x38: uint32 field_0x38
//   +0x6a: uint8 connectedFlag   // (offset relative to slot base)
// +0x566: uint8 activeSlot1
// +0x567: uint8 activeSlot2
// +0x568: uint8 currentSlot
// +0x56c: uint32 currentSlotData
// +0x4dc: void (*callback)(uint32, int, uint32, int)  // event callback

void InputManager::disconnectController(uint8 slotIndex, uint32 unkArg) {
    if (slotIndex < 16) {
        // Save the connected flag of the slot before clearing
        uint8 savedFlag = *(uint8 *)((uintptr_t)this + 0x6a + slotIndex * 0x44);

        // Calculate slot base address (without the +0x6a offset)
        uint8* slotBase = (uint8*)((uintptr_t)this + slotIndex * 0x44);

        // Clear the slot's state block (0x44 bytes starting at slotBase+0x2c)
        memset(slotBase + 0x2c, 0, 0x44);

        // Explicitly zero four dwords (redundant after memset, but preserves intent)
        *(uint32*)(slotBase + 0x2c) = 0;
        *(uint32*)(slotBase + 0x30) = 0;
        *(uint32*)(slotBase + 0x34) = 0;
        *(uint32*)(slotBase + 0x38) = 0;

        // Restore the saved flag (then immediately clear it)
        *(uint8*)((uintptr_t)this + 0x6a + slotIndex * 0x44) = savedFlag;
        *(uint8*)((uintptr_t)this + 0x6a + slotIndex * 0x44) = 0;  // disconnect

        // If this slot was the current active slot, reset it
        if (*(uint8*)((uintptr_t)this + 0x568) == slotIndex) {
            *(uint8*)((uintptr_t)this + 0x568) = 0x12;  // invalid slot index (18)
            *(uint32*)((uintptr_t)this + 0x56c) = 0;
        }

        // Deactivate any vibration/state for this slot
        resetController(slotIndex);  // FUN_00410770

        // Update secondary active slot tracking
        if (*(uint8*)((uintptr_t)this + 0x566) == slotIndex) {
            *(uint8*)((uintptr_t)this + 0x566) = 0x12;  // invalid
        }
        if (*(uint8*)((uintptr_t)this + 0x567) == slotIndex) {
            *(uint8*)((uintptr_t)this + 0x567) = 0x12;  // invalid
        }

        // Dispatch a disconnect event (probably notifies the game)
        struct DisconnectEvent {
            uint32 field_0;  // DAT_01206a10
            uint8  field_4;
            uint8  slotIndex;  // aligned?
        } event = { DAT_01206a10, 0, slotIndex };

        dispatchEvent(&event, 0);  // FUN_00408a00
    }

    // If a callback is registered, invoke it
    if (*(void***)((uintptr_t)this + 0x4dc) != nullptr) {
        (*(void(__thiscall*)(uint32, int, uint32, int))(*(uintptr_t*)((uintptr_t)this + 0x4dc)))(unkArg, 0, unkArg, 0);
    }
}