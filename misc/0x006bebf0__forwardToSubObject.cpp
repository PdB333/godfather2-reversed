// FUNC_NAME: forwardToSubObject
// Function address: 0x006bebf0
// Identified role: Simple forwarding/thunk to a sub-object method. The sub-object lives at offset +0x28 from 'this'.
// The actual work is done in FUN_006beb80 (likely a setter or handler on that sub-component).

void __thiscall forwardToSubObject(void* this_ptr, int param)
{
    // Sub-object is embedded at offset 0x28 (e.g., a state machine, input component, or property bag)
    void* subObject = reinterpret_cast<char*>(this_ptr) + 0x28;
    // Delegate to the sub-object's method (FUN_006beb80)
    FUN_006beb80(subObject, param);
    return;
}