// FUNC_NAME: CEventManager::sendEvent
void __thiscall CEventManager::sendEvent(void* this, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5)
{
    // +0x164: active flag (non-zero if event processing is enabled)
    if (*(int*)((uintptr_t)this + 0x164) != 0)
    {
        int* ppGlobalVTable = (int*)(DAT_01206880 + 0x14);          // Global vtable pointer offset
        **(void***)ppGlobalVTable = (void*)&PTR_FUN_0110baf8;      // Set new vtable base
        *ppGlobalVTable = *ppGlobalVTable + 4;                     // Advance to next vtable slot

        // +0x54: sub-object (likely event queue or buffer)
        // Combines arg4 and arg5 into a 64-bit value (low, high) and passes size 4
        FUN_00473170((uintptr_t)this + 0x54, arg2, arg3, ((uint64_t)arg5 << 32) | arg4, 4);
    }
}