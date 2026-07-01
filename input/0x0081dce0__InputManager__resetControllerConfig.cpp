// FUNC_NAME: InputManager::resetControllerConfig
void __fastcall InputManager::resetControllerConfig(InputManager* this)
{
    // Clear specific flags at +0x10 (likely bitfield for controller state)
    *(uint*)((char*)this + 0x10) &= 0xfffffffb; // Clear bit 2 (controller type flag?)
    *(uint*)((char*)this + 0x10) &= 0xfffffffe; // Clear bit 0 (connected?)
    *(uint*)((char*)this + 0x10) &= 0xfffffffd; // Clear bit 1 (active?)
    *(uint*)((char*)this + 0x14) &= 0xfffffffe; // Clear bit 0 of second flags word

    // Call some initialization function 4 times (likely per controller slot or analog stick)
    FUN_004df600(); // Probably InputAction::reset()
    FUN_004df600();
    FUN_004df600();
    FUN_004df600();

    // Reset deadzone/shape settings at +0x11c
    *(int*)((char*)this + 0x11c) = 0;          // +0x11c: inner deadzone
    *(char*)((char*)this + 0x120) = 0;          // +0x120: outer deadzone shape (0 = circular)
    *(int*)((char*)this + 0x124) = 8;           // +0x124: outer deadzone value (8 = default radius)
}