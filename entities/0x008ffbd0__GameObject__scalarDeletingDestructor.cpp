// FUNC_NAME: GameObject::scalarDeletingDestructor
// Address: 0x008ffbd0
// Role: Scalar deleting destructor (calls destructor then optionally frees memory)
// Decompiled: calls destructor body (FUN_008ffb00) and if param_2 & 1, calls deallocation

undefined4 __thiscall GameObject::scalarDeletingDestructor(GameObject* this, byte flags)
{
    // Call the actual destructor body (virtual destructor implementation)
    FUN_008ffb00(); // GameObject::destructorBody() - likely clears internals, frees owned resources

    // If bit 0 of flags is set, deallocate the object's memory
    // This allows operator delete to be called when the scalar deleting destructor is used
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this); // operator delete(this) or memory deallocation
    }

    return this; // Return the original pointer (for chaining, e.g., in placement delete)
}