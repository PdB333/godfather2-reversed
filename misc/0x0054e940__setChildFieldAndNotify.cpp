// FUNC_NAME: setChildFieldAndNotify
// Address: 0x0054e940
// Role: Sets a 4-byte field at offset +0x2c in an object pointed to by this->someChild (+0x18),
//       then calls a notification/activation function on that child with argument 1.

void __thiscall setChildFieldAndNotify(void* thisPtr, int param2)
{
    // this +0x18: pointer to a child/component object (e.g., m_pSubsystem)
    void* child = *(void**)((char*)thisPtr + 0x18);
    
    // child +0x2c: some property (e.g., m_state, m_value)
    *(int*)((char*)child + 0x2c) = param2;
    
    // Call a function on child with argument 1 (likely enable/activate)
    FUN_009e9c50(child, 1);
}