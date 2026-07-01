// FUNC_NAME: Entity::constructor
// Function address: 0x008421f0
// Identified as a base class constructor for game objects (likely Entity).
// Sets vtable pointers and magic sentinel values for debugging.

Entity* __thiscall Entity::constructor(Entity* this) {
    // Call base class constructor (likely for a parent class)
    FUN_00848d00(); // Base constructor

    // Call some initializer six times (possibly for components or slots)
    FUN_005953b0(); // Initializer call 1
    FUN_005953b0(); // Initializer call 2
    FUN_005953b0(); // Initializer call 3
    FUN_005953b0(); // Initializer call 4
    FUN_005953b0(); // Initializer call 5
    FUN_005953b0(); // Initializer call 6

    // Set vtable pointer at offset 0x00
    this->vtable = (void*)&PTR_FUN_00d748c4; // +0x00: vtable

    // Set pointer at offset 0x0C (possibly class descriptor or base vtable)
    this->field_0C = (void*)&PTR_LAB_00d747cc; // +0x0C: first assignment (overwritten below)
    this->field_0C = (void*)&PTR_LAB_00d74898; // +0x0C: final assignment (derived class data)

    // Initialize magic sentinel fields for debugging
    this->magicZero = 0;                // +0x8C: zero sentinel
    this->magicBad = 0xbadbadba;        // +0x90: "bad" sentinel
    this->magicBeef = 0xbeefbeef;       // +0x94: "beef" sentinel
    this->magicEa = 0xeac15a55;         // +0x98: "EA" sentinel
    this->magic911 = 0x91100911;        // +0x9C: "911" sentinel

    return this;
}