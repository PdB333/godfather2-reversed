// FUNC_NAME: PlayerCrewLeaderComponent::Constructor
// Function at 0x00830b20 - Constructor for PlayerCrewLeaderComponent (multiple inheritance, two vtable slots)
// Sets primary vtable at +0x00, then calls base1 init, then sets secondary vtable at +0x30, calls base2 init.

void __thiscall PlayerCrewLeaderComponent::Constructor(PlayerCrewLeaderComponent* this) {
    // Set primary vtable pointer for first base class
    this->vtable = (void**)&PTR_FUN_00d737d8; // +0x00
    // Initialize primary base (likely CrewLeaderComponent)
    this->initializeBase1(); // FUN_0082a9d0

    // Set secondary vtable pointer at offset 0x30 (for second base class)
    *(void**)((uint8_t*)this + 0x30) = &PTR_LAB_00e32854; // +0x30
    // Initialize second base (likely PlayerComponent)
    this->initializeBase2(); // FUN_00821f60
}