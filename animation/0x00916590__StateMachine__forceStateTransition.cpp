// FUNC_NAME: StateMachine::forceStateTransition
void __thiscall StateMachine::forceStateTransition(int this, int param2)
{
    // Input data structure (16 bytes, 4 floats)
    struct InputData {
        float a; // +0x00 (first element, from FUN_00950b20 result)
        float b; // +0x04 (second element, used as timer/accumulator)
        float c; // +0x08 (third element)
        float d; // +0x0C (fourth element, from global _DAT_00d5780c)
    } localData;

    InputData* pInput = (InputData*)FUN_00950b20(); // getSomeData
    if (pInput == nullptr) {
        localData.a = 0.0f;
        localData.b = 0.0f;
        localData.c = 0.0f;
        localData.d = 0.0f;
    } else {
        localData.a = pInput->a;
        localData.b = pInput->b;
        localData.c = pInput->c;
        localData.d = _DAT_00d5780c; // global constant
    }

    localData.b += DAT_00d8bbc8; // add global time delta (e.g., frame time)
    FUN_0097a8d0(&localData);    // processInputData (modifies or uses the data)

    // Reset current state if it's one of the transitional states
    switch (*(int*)(this + 8)) { // +0x08: current state
    case 1:
    case 2:
    case 3:
    case 4:
        *(int*)(this + 8) = 0; // clear to idle/default
    }

    // Store new parameter and force state to 3
    *(int*)(this + 4) = param2; // +0x04: parameter for the target state
    *(int*)(this + 8) = 3;      // +0x08: state = 3 (e.g., active/playing)
    FUN_00978910(param2);       // startTransition or applyParameter
}