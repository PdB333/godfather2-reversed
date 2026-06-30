// FUNC_NAME: Object::setStateActive
void __thiscall Object::setStateActive(void)
{
    int currentState = *(int *)(this + 0xc); // +0xc: state field (enum: 1=active, 2=loading, 3=error, 4=transitioning)
    if (currentState == 2 || currentState == 3 || currentState == 4) {
        // Cleanup resource handle stored at +0x4 (e.g., a pointer or index)
        FUN_00c7a770(*(undefined4 *)(this + 0x4));
    }
    *(int *)(this + 0xc) = 1; // Transition to active/idle state
}