//FUNC_NAME: PlayerCrewLeaderComponent::constructor
// Address: 0x008de740
// Role: Constructor for PlayerCrewLeaderComponent. Initializes vtable pointers and a field.
// Calls base constructor (FUN_008df7a0) with the provided parameter.

PlayerCrewLeaderComponent* __thiscall PlayerCrewLeaderComponent::constructor(PlayerCrewLeaderComponent* this, uint32_t param_2)
{
    // Call base class constructor (likely Component or CrewLeaderComponent)
    FUN_008df7a0(param_2);

    // Set primary vtable pointer
    this->vtable = &PTR_FUN_00d7ec70;

    // Set secondary vtable pointers for multiple inheritance / interfaces
    this->interfaceVtable1 = &PTR_LAB_00d7ec60;   // +0x3C (offset 0xf * 4)
    this->interfaceVtable2 = &PTR_LAB_00d7ec5c;   // +0x48 (offset 0x12 * 4)
    this->interfaceVtable3 = &PTR_LAB_00d7ec58;   // +0x50 (offset 0x14 * 4)
    this->interfaceVtable4 = &PTR_LAB_00d7ebf8;   // +0x54 (offset 0x15 * 4)
    this->interfaceVtable5 = &PTR_LAB_00d7eb90;   // +0x58 (offset 0x16 * 4)

    // Initialize field at offset 0x9c (156 * 4 = 624 bytes) to 0
    this->someField = 0;                           // +0x9C

    return this;
}