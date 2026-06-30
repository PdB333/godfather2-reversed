// FUNC_NAME: BaseManager::reset
int __fastcall BaseManager::reset(void* thisObj)
{
    // +0x20: flag (byte) - m_bState, +0x24: pointer to manager
    if ((*(char*)((int)thisObj + 0x20) == '\0') && (*(int*)((int)thisObj + 0x24) != 0))
    {
        // +0x0c: pointer to first resource (has vtable)
        if (*(void**)((int)thisObj + 0x0c) != nullptr)
        {
            // Call virtual method at vtable+0x5c (likely release/destroy)
            (*(void (__thiscall**)(void*))(*(int*)(*(int*)((int)thisObj + 0x0c)) + 0x5c))(*(void**)((int)thisObj + 0x0c));
            // Call virtual method at manager vtable+0x3c (notification)
            (*(void (__thiscall**)(void*))(*(int*)(*(int*)((int)thisObj + 0x24)) + 0x3c))(*(void**)((int)thisObj + 0x24));
            *(int*)((int)thisObj + 0x0c) = 0;
        }
        // +0x08: pointer to second resource (has vtable)
        if (*(void**)((int)thisObj + 0x08) != nullptr)
        {
            // Call virtual method at vtable+0x2c (likely release/destroy)
            (*(void (__thiscall**)(void*))(*(int*)(*(int*)((int)thisObj + 0x08)) + 0x2c))(*(void**)((int)thisObj + 0x08));
            // Call virtual method at manager vtable+0x10 (notification)
            (*(void (__thiscall**)(void*))(*(int*)(*(int*)((int)thisObj + 0x24)) + 0x10))(*(void**)((int)thisObj + 0x24));
            *(int*)((int)thisObj + 0x08) = 0;
        }
        // Set flag to 1 (reset complete)
        *(char*)((int)thisObj + 0x20) = 1;
        // Call manager vtable+0x1c with 12 zero arguments (clear/reset)
        (*(void (__thiscall**)(void*, int, int, int, int, int, int, int, int, int, int, int, int))(*(int*)(*(int*)((int)thisObj + 0x24)) + 0x1c))(
            *(void**)((int)thisObj + 0x24), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
    return 1;
}