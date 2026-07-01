// FUNC_NAME: SomeClass::removeNodeAndCleanup
void __thiscall SomeClass::removeNodeAndCleanup(int param_2)
{
    // Stack cookie or vtable pointer? Not used.
    undefined **local_18 = &PTR_FUN_00e31e2c;
    int local_14;
    undefined4 local_10;
    undefined4 local_c;
    undefined1 *local_8 = (undefined1 *)&local_18;
    undefined1 local_4;

    // Determine node pointer: if param_2 is null, use 0; else add 0x48 (node offset within object)
    if (param_2 == 0) {
        local_14 = 0;
    } else {
        local_14 = param_2 + 0x48; // +0x48: linked list node offset
    }

    local_10 = 0;
    if (local_14 != 0) {
        // Read next pointer from node (offset +4)
        local_10 = *(undefined4 *)(local_14 + 4);
        // Set node's next pointer to point to local variable (stack sentinel)
        *(int **)(local_14 + 4) = &local_14;
    }

    // Get member at this+0xA0 (likely a pointer to a reference-counted object)
    local_c = *(undefined4 *)(this + 0xA0);
    local_4 = 0;
    // Call release/cleanup on that member
    FUN_00408a00(&local_c, 0);

    // If node was valid, call deallocation/cleanup on the node
    if (local_14 != 0) {
        FUN_004daf90(&local_14);
    }
    return;
}