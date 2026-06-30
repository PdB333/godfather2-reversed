// FUNC_NAME: InputDeviceManager::InputDeviceManager

#include <cstdint>

// Vtable for controller slot objects (from PTR_LAB_00e40d18)
extern void* g_controllerSlotVtable;

// Vtable for InputDeviceManager (from PTR_FUN_00e38908)
extern void* g_inputDeviceManagerVtable;

// Size of each controller slot: 0x5C bytes (23 dwords)
struct ControllerSlot {
    void* vtable;          // +0x00
    uint32_t field_0x04;   // +0x04
    uint32_t field_0x08;   // +0x08
    uint32_t field_0x0C;   // +0x0C
    uint32_t field_0x10;   // +0x10
    uint32_t field_0x14;   // +0x14
    uint32_t field_0x18;   // +0x18
    uint32_t field_0x1C;   // +0x1C
    uint32_t field_0x20;   // +0x20
    uint32_t field_0x24;   // +0x24
    uint32_t field_0x28;   // +0x28
    uint32_t field_0x2C;   // +0x2C
    uint32_t field_0x30;   // +0x30
    uint32_t field_0x34;   // +0x34
    uint32_t field_0x38;   // +0x38
    uint32_t field_0x3C;   // +0x3C
    uint32_t field_0x40;   // +0x40
    uint32_t field_0x44;   // +0x44
    uint32_t field_0x48;   // +0x48
    uint32_t field_0x4C;   // +0x4C
    uint32_t field_0x50;   // +0x50
    uint32_t field_0x54;   // +0x54
    uint32_t field_0x58;   // +0x58
};

// Global singleton instance
InputDeviceManager* g_inputDeviceManager = reinterpret_cast<InputDeviceManager*>(0x0121a380);

// Base initialization (likely memory or subsystem setup)
extern void __cdecl baseInit(); // FUN_006126d0

// Constructor for InputDeviceManager
// Initializes the singleton and its 16 controller slots
InputDeviceManager* __thiscall InputDeviceManager::InputDeviceManager() {
    baseInit();

    // Set own vtable
    this->vtable = &g_inputDeviceManagerVtable;

    // Pointer to first controller slot (at offset 0xB8 from this)
    // In the original code: puVar1 = &DAT_0121a438 (first slot)
    ControllerSlot* slot = reinterpret_cast<ControllerSlot*>(reinterpret_cast<uint8_t*>(this) + 0xB8);

    // Initialize 16 controller slots (0xF + 1 = 16)
    for (int i = 0; i < 16; ++i) {
        // Set vtable for each slot
        slot->vtable = &g_controllerSlotVtable;

        // Zero-initialize all fields
        slot->field_0x04 = 0;
        slot->field_0x08 = 0;
        slot->field_0x0C = 0;
        slot->field_0x10 = 0;
        slot->field_0x14 = 0;
        slot->field_0x18 = 0;
        slot->field_0x1C = 0;
        slot->field_0x20 = 0;
        slot->field_0x24 = 0;
        slot->field_0x28 = 0;
        slot->field_0x2C = 0;
        slot->field_0x30 = 0;
        slot->field_0x34 = 0;
        slot->field_0x38 = 0;
        slot->field_0x3C = 0;
        slot->field_0x40 = 0;
        slot->field_0x44 = 0;
        slot->field_0x48 = 0;
        slot->field_0x4C = 0;
        slot->field_0x50 = 0;
        slot->field_0x54 = 0;
        slot->field_0x58 = 0;

        // Advance to next slot (0x17 dwords = 0x5C bytes)
        slot = reinterpret_cast<ControllerSlot*>(reinterpret_cast<uint8_t*>(slot) + 0x5C);
    }

    // Additional global variables zeroed (likely part of manager state)
    // These are at fixed offsets from the manager base
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0xD24) = 0; // DAT_0121b0a4
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0xD28) = 0; // DAT_0121b0a8
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0xD2C) = 0; // DAT_0121b0ac
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x12B8) = 0; // DAT_0121b638
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x12BC) = 0; // DAT_0121b63c

    return this;
}