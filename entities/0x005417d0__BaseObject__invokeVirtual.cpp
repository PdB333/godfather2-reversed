// FUNC_NAME: BaseObject::invokeVirtual
void __thiscall BaseObject::invokeVirtual(void* param_2, void* param_3, void* param_4)
{
    // Pre-call hook or debug check (likely logs or validates state)
    FUN_009f2000();

    // Call a virtual function from a member pointer stored at this+0xd0.
    // The vtable offset 0x54 corresponds to the 21st virtual function (0x54/4 = 0x15).
    // This is a typical delegation pattern: the object holds a pointer to a sub-object
    // (e.g., a behavior, state machine, or component) and forwards calls to it.
    (**(code **)(*(int *)(this + 0xd0) + 0x54))(param_2, param_3, param_4);
}