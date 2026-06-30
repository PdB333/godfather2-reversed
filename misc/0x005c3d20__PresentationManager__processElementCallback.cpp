// FUNC_NAME: PresentationManager::processElementCallback
// Function address: 0x005c3d20
// Role: Calls a virtual function on a singleton manager, passing a pointer to a sub-object at offset 5 from the first argument.
// Observed pattern: Retrieves a manager via FUN_005c3df0 (likely a static getter), then calls a virtual method at vtable+0x1c.
// The virtual method receives (param_1 + 5, param_2) as arguments.

void __thiscall PresentationManager::processElementCallback(void* this, int subObjectOffset5, int arg2)
{
    // Retrieve a pointer to the manager instance (e.g., UIRenderingManager, DebugOverlay, etc.)
    // FUN_005c3df0 likely returns a global singleton or factory instance.
    // The function uses a hidden register parameter (in_EAX) which may be a class ID or version tag.
    int* vtablePtr = (int*)FUN_005c3df0(in_EAX);

    // Call virtual function at vtable offset 0x1c (index 7).
    // This function expects:
    //   - ECX = this (the manager)
    //   - first stack argument = pointer to object at (subObjectOffset5 + 5 bytes)
    //   - second stack argument = arg2
    // The +5 offset suggests subObjectOffset5 points to a structure where the relevant sub-object begins at byte offset 5.
    // Possibly a base class offset or a packed field.
    (**(code**)(*vtablePtr + 0x1c))((char*)subObjectOffset5 + 5, arg2);
}