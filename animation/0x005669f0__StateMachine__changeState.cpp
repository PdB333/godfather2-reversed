// FUNC_NAME: StateMachine::changeState
void __thiscall StateMachine::changeState(StateMachine *this, int arg0, int arg1)
{
    // VTable pointer stored at offset +0x0c from 'this'
    uintptr_t vtablePtr = *(uintptr_t *)((uintptr_t)this + 0x0c);
    // Virtual function at vtable offset 0x50 (index 0x50/4 = 20)
    void (*virtualFunc)(int, int, int) = *(void (**)(int, int, int))(vtablePtr + 0x50);
    // Call with param2, param3, and flag 1 (likely bool)
    virtualFunc(arg0, arg1, 1);
    // Set state field at +0x10 to 3 (enum value for new state)
    *(int *)((uintptr_t)this + 0x10) = 3;
}