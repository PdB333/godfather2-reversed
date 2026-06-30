// FUNC_NAME: SimManager::releaseSubsystem
// Address: 0x006b1990
// Role: Releases the subsystem pointed to by this+0xFC. Stops and removes the module with ID 2, then releases the subsystem object and nullifies the pointer.

void __fastcall SimManager::releaseSubsystem(SimManager* this)
{
    // Check if subsystem pointer (at offset 0xFC) is non-zero
    if (*(int*)((char*)this + 0xFC) != 0)
    {
        // Stop and remove module with ID 2 (likely a subsystem index)
        stopModule(this, 2);   // FUN_008c5420
        removeModule(this, 2); // FUN_008c53a0

        // If the subsystem object still exists, release it via its vtable
        int* pSubsystem = *(int**)((char*)this + 0xFC);
        if (pSubsystem != nullptr)
        {
            // vtable at pSubsystem[0]; call method at offset 0x18 (index 6) with argument 1
            (*(void(__thiscall**)(int*, int))(*pSubsystem + 0x18))(pSubsystem, 1);
        }

        // Nullify the subsystem pointer
        *(int*)((char*)this + 0xFC) = 0;
    }
}