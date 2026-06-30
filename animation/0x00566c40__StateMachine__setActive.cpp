// FUNC_NAME: StateMachine::setActive
void StateMachine::setActive(char active) {
    if (active == '\0') {
        // Transition to inactive state: subState=2, mainState=0, clear flag bit 2
        *(unsigned char*)(this + 0x14) = 2;          // subState
        *(int*)(this + 0x10) = 0;                    // mainState
        *(unsigned int*)(this + 0x2C) &= 0xFFFFFFFB; // clear bit 2 (flag)
    } else if (*(int*)(this + 0x10) != 8) {
        // If not already in a special state (8), set mainState to 1
        *(int*)(this + 0x10) = 1;
    }

    // Notify delegate via virtual call (vtable offset 0x44)
    __int32* delegate = *(int**)(this + 0x0C);
    if (delegate != nullptr) {
        (**(code**)(*delegate + 0x44))();  // call function at vtable slot 0x44/4
    }
}