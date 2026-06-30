// FUNC_NAME: SomeManager::initSlots
// Function at 0x0059b5e0: Initializes a structure with 6 entries, each containing a pointer and flags.
// Likely part of a manager class (e.g., AnimationSlotManager, AudioSlotManager) that holds multiple slots.
// Each slot is 0x10 bytes: pointer, zero, then four shorts (0,0,4,0).
// The structure starts with a flags field (low nibble set to 0xE, bit0 cleared).

struct SlotEntry {
    uint32_t pointer;    // +0x00: pointer to associated object (set to param_1)
    uint32_t zero;       // +0x04: always 0
    int16_t short0;      // +0x08: 0
    int16_t short1;      // +0x0A: 0
    int16_t short2;      // +0x0C: 4 (default value)
    int16_t short3;      // +0x0E: 0
};

struct SlotManager {
    uint32_t flags;               // +0x00: flags (initialized to (flags & ~1) | 0xE)
    SlotEntry entries[6];         // +0x04: 6 slots, each 0x10 bytes
    uint32_t extraZero;           // +0x64: always 0
};

// __fastcall: this in ECX, param_1 in EDX? But decompiled shows param_1 as only arg.
// We assume this is a member function with this in ECX and a parameter in EDX.
void __fastcall SlotManager::initSlots(uint32_t param_1) {
    // Initialize each slot entry
    for (int i = 0; i < 6; i++) {
        entries[i].pointer = param_1;
        entries[i].zero = 0;
        entries[i].short0 = 0;
        entries[i].short1 = 0;
        entries[i].short2 = 4;   // default value
        entries[i].short3 = 0;
    }
    // Set the extra zero at the end
    extraZero = 0;
    // Set flags: clear bit0, set low nibble to 0xE
    flags = (flags & 0xFFFFFFFE) | 0xE;
}