// FUNC_NAME: SimManager::releaseAllEntities
void __thiscall SimManager::releaseAllEntities(int *this)
{
    uint i;

    // Call virtual pre-cleanup function (vtable index 36, offset 0x90)
    (*(void (__thiscall **)(int *))(*(int *)this + 0x90))(this);

    // Release each entity in the array
    i = 0;
    if (this[0x14] != 0) {
        do {
            FUN_009c8eb0(*(undefined4 *)(this[0x13] + i * 4)); // Entity::release
            i = i + 1;
        } while (i < (uint)this[0x14]);
    }

    // Reset count and free the array
    this[0x14] = 0;                      // +0x50 (count)
    FUN_009c8f10(this[0x13]);           // Memory::free
    this[0x13] = 0;                     // +0x4C (array pointer)
    this[0x15] = 0;                     // +0x54 (some flag or capacity)

    // Global post-cleanup
    FUN_0096abb0();                     // globalSimCleanup
}