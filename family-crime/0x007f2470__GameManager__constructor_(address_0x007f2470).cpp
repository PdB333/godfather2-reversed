// FUNC_NAME: GameManager::constructor (address 0x007f2470)
// NOTE: This is a constructor for a class inheriting from two base classes (multiple inheritance).
// It manually sets vtable pointers, calls a base initialization function (FUN_0043b400), then updates its own vtable.
// DAT_0112bb50 is a global flag (likely g_bGameStarted) that is reset to 0.

void __thiscall GameManager::GameManager() {
    // Set vtable pointers for multiple inheritance:
    // Offset +0x00: first base class vtable (PTR_FUN_00d70288)
    // Offset +0x04: second base class vtable (PTR_LAB_00d70278)
    *(void**)this = &PTR_FUN_00d70288;    // vtable for first base
    *(void**)((uint)this + 4) = &PTR_LAB_00d70278; // vtable for second base

    // Call base class initializer (likely sets up base class members)
    BaseInitFunc();

    // Override first vtable with own vtable after base initialization
    *(void**)this = &PTR_LAB_00d70274;

    // Reset global start flag
    g_bGameStarted = 0;
}