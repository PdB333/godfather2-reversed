// FUNC_NAME: EntityStateMachine::tryActivate
// Function address: 0x0076db20
// Checks state flags (offset +0x74) and target pointer (+0x5c),
// then queries a game manager singleton (via vtable offset 0x38) for permission.
// If approved, sets flag bit 0 and triggers an effect.

typedef bool (__thiscall* ManagerPermissionFunc)(void* manager);

void __thiscall EntityStateMachine::tryActivate(EntityStateMachine* thisPtr) {
    // Check if bits 0 and 2 are both clear at offset +0x74
    if ((*(uint8_t*)((uintptr_t)thisPtr + 0x74) & 5) != 0)
        return;

    // Target reference at offset +0x5c must be non-null
    if (*(void**)((uintptr_t)thisPtr + 0x5c) == nullptr)
        return;

    // Retrieve the global game manager via known getter function
    void* manager = (void*)FUN_0043b870(DAT_01131018);
    if (manager == nullptr)
        return;

    // Virtual call at vtable+0x38: likely "isActionAllowed" on the manager
    ManagerPermissionFunc permFunc = (ManagerPermissionFunc)(*(void***)manager)[0x38 / 4];
    if (!permFunc(manager))
        return;

    // Enable the activation flag (bit 0) at offset +0x74
    *(uint8_t*)((uintptr_t)thisPtr + 0x74) |= 1;

    // Execute the associated trigger (e.g., sound, animation, state push)
    FUN_009aef10();
}