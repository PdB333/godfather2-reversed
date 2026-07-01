// FUNC_NAME: PlayerCrewLeaderComponent::initializeCrewSlots
// Function at 0x007dc210: Initializes three crew member slots and trailing flags to default values (0 or invalid handle).
// Offsets below indicate positions within the PlayerCrewLeaderComponent object.

void __fastcall PlayerCrewLeaderComponent::initializeCrewSlots(PlayerCrewLeaderComponent* this)
{
    // Global constant (likely -1 or 0xFFFFFFFF representing an invalid crew handle)
    uint32_t invalidHandle = _DAT_00d5780c;

    // --- Slot 0 (base offset +0x14) ---
    *(uint32_t*)(this + 0x14) = 0; // +0x14: unknown (likely state/timer)
    *(uint32_t*)(this + 0x2C) = 0; // +0x2C
    *(uint32_t*)(this + 0x3C) = 0; // +0x3C
    *(uint32_t*)(this + 0x4C) = 0; // +0x4C
    *(uint32_t*)(this + 0x5C) = invalidHandle; // +0x5C: crew member pointer/ID
    *(uint32_t*)(this + 0x60) = 0; // +0x60: unknown
    *(uint16_t*)(this + 0x64) = 0; // +0x64: short field
    *(uint16_t*)(this + 0x66) = 0; // +0x66: short field

    // --- Slot 1 (base offset +0x84) ---
    *(uint32_t*)(this + 0x84) = 0; // +0x84
    *(uint32_t*)(this + 0x9C) = 0; // +0x9C
    *(uint32_t*)(this + 0xAC) = 0; // +0xAC
    *(uint32_t*)(this + 0xBC) = 0; // +0xBC
    *(uint32_t*)(this + 0xCC) = invalidHandle; // +0xCC
    *(uint32_t*)(this + 0xD0) = 0; // +0xD0
    *(uint16_t*)(this + 0xD4) = 0; // +0xD4
    *(uint16_t*)(this + 0xD6) = 0; // +0xD6

    // --- Slot 2 (base offset +0xF4) ---
    *(uint32_t*)(this + 0xF4) = 0; // +0xF4
    *(uint32_t*)(this + 0x10C) = 0; // +0x10C
    *(uint32_t*)(this + 0x11C) = 0; // +0x11C
    *(uint32_t*)(this + 0x12C) = 0; // +0x12C (300 decimal)
    *(uint32_t*)(this + 0x13C) = invalidHandle; // +0x13C
    *(uint32_t*)(this + 0x140) = 0; // +0x140
    *(uint16_t*)(this + 0x144) = 0; // +0x144
    *(uint16_t*)(this + 0x146) = 0; // +0x146

    // --- Tail bytes (offset +0x150 to +0x154) ---
    *(uint8_t*)(this + 0x150) = 0; // +0x150
    *(uint8_t*)(this + 0x151) = 0; // +0x151
    *(uint8_t*)(this + 0x152) = 0; // +0x152
    *(uint8_t*)(this + 0x153) = 0; // +0x153
    *(uint8_t*)(this + 0x154) = 0; // +0x154
}