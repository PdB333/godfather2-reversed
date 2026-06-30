// FUNC_NAME: BaseStateMachine::dispatchStateUpdate
// Address: 0x00724cb0
// This function is a thin dispatch wrapper that calls a virtual function at vtable offset 0x24.
// It is used as the public interface for triggering state machine updates.
// The offset 0x24 corresponds to a virtual method such as "updateState" or "processInput" in derived state classes.

void __fastcall BaseStateMachine::dispatchStateUpdate(int *this) // this in ECX
{
    // Call the virtual method at vtable entry +0x24 (index 9)
    (*(void (__fastcall **)(int *))(*(int *)this + 0x24))(this);
    return;
}