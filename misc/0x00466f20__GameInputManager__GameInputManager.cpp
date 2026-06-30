// FUNC_NAME: GameInputManager::GameInputManager
// Function address: 0x00466f20
// Constructor for GameInputManager class.
// Sets up vtable pointers for multiple inheritance, initializes global state.
// param_2: flags - if bit 0 set, performs additional initialization.

GameInputManager* __thiscall GameInputManager::GameInputManager(GameInputManager* this, byte flags) {
    // Set vtable pointers for base classes
    // +0x00: vtable pointer to base class A (likely InputDevice or Singleton)
    *(uint32_t*)this = &PTR_FUN_00e31ef8;
    // +0x04: vtable pointer for second base class (e.g., HandlerList)
    *(uint32_t*)((uint8_t*)this + 4) = &PTR_LAB_00e31f04;
    // +0x10: vtable pointer for third base class (e.g., EventReceiver)
    *(uint32_t*)((uint8_t*)this + 16) = &PTR_LAB_00e31f14;

    // Call base class constructor (likely for a common base)
    FUN_0043e380(this);

    // Override the third vtable pointer
    *(uint32_t*)((uint8_t*)this + 16) = &PTR_LAB_00e31f18;

    // Reset global initialization flag
    DAT_0122346c = 0;
    // Perform global initializations (e.g., input system start)
    FUN_004083d0();

    // Set the final derived class vtable
    *(uint32_t*)this = &PTR_LAB_00e30ea0;

    // If flags indicate additional work, call the extra init function
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}