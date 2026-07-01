// FUNC_NAME: SomeManager::setActiveState
void __thiscall SomeManager::setActiveState(int this)
{
    // Called with two member variables at offsets 0x80 and 0x88, and a boolean flag (1)
    // Likely sets an active state for a resource or object
    FUN_007d09f0(*(int*)(this + 0x80), *(int*)(this + 0x88), 1);
}