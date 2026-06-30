// FUNC_NAME: SomeClass::reset
void __thiscall SomeClass::reset(uint32_t initData) {
    // Clear flags at offsets +0x8 and +0x9 (likely boolean state flags)
    *(uint8_t*)((uintptr_t)this + 8) = 0;
    *(uint8_t*)((uintptr_t)this + 9) = 0;

    // Call common engine initialization routine (FUN_0040d330)
    baseInit();

    // Call internal member initialization with the argument (FUN_0067d090)
    initializeMembers(initData);
}