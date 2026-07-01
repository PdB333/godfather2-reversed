// FUNC_NAME: SomeManager::SomeManager
void __thiscall SomeManager::SomeManager(void *this) {
    // Set vtable pointer (offset 0x00)
    *(void **)this = &PTR_FUN_00d74178;
    // Set function pointer at offset 0x3C (0xF * 4)
    *(void **)((char *)this + 0x3C) = &PTR_LAB_00d74164;
    // Set function pointer at offset 0x48 (0x12 * 4)
    *(void **)((char *)this + 0x48) = &PTR_LAB_00d74160;
    // Set function pointer at offset 0x158 (0x56 * 4) - first assignment
    *(void **)((char *)this + 0x158) = &PTR_LAB_00d7415c;
    // Overwrite same offset with different pointer
    *(void **)((char *)this + 0x158) = &PTR_LAB_00d74158;
    // Reset global singleton flag/pointer
    DAT_0112a694 = 0;
    // Call secondary initialization
    FUN_0083f2f0();
    return;
}