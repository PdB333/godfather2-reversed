// FUNC_NAME: SomeStateMachine::update
void __thiscall SomeStateMachine::update(int this) // this is param_1, in_EAX is a pointer to a sub-struct
{
    // Likely the first member of 'this' is an integer state machine struct pointer
    int* stateMachine = (int*)this; // Actually in_EAX = stateMachine pointer, but we need to map correctly
    // The decompiled code uses *in_EAX as the state and accesses in_EAX[3], in_EAX[4]
    // Also uses param_1+0x24 (offset 36), param_1+0x34 (offset 52), param_1+0xc (offset 12)

    baseFunction(); // FUN_00642b00()

    int state = stateMachine[0]; // *in_EAX
    int temp; // for swap

    switch (state)
    {
    case 1:
    case 3:
        temp = stateMachine[4];
        stateMachine[0] = 2;
        stateMachine[4] = stateMachine[3];
        stateMachine[3] = temp;
        return;
    case 2:
    case 4:
        temp = stateMachine[4];
        stateMachine[0] = 3;
        stateMachine[4] = stateMachine[3];
        stateMachine[3] = temp;
        return;
    case 9:
        someIntermediateFunction(); // FUN_00643250()
        temp = stateMachine[4];
        stateMachine[4] = stateMachine[3];
        stateMachine[3] = temp;
        return;
    case 10:
    case 11:
        anotherBaseFunction(); // FUN_00642d40()
        if (state == 11 && *(int*)(this + 0x34) <= stateMachine[1] && stateMachine[1] < 250)
        {
            *(int*)(this + 0x24) = *(int*)(this + 0x24) - 1;
        }
        int computed = computeSomething(stateMachine[1] << 15 | 0x12, *(int*)(*(int*)(this + 0xc) + 8)); // FUN_006438e0
        stateMachine[1] = computed;
        stateMachine[0] = 10;
        break;
    }

    // Perform the same swap after switch (for cases that fall through)
    temp = stateMachine[4];
    stateMachine[4] = stateMachine[3];
    stateMachine[3] = temp;
}