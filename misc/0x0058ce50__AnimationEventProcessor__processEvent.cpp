// FUNC_NAME: AnimationEventProcessor::processEvent
int __thiscall AnimationEventProcessor::processEvent(float timeDelta, int thisObj, void* animState, int param4, int param5, int param6, int param7, int param8) {
    int* intPtr;
    byte* bytePtr;
    code* funcPtr;
    int opcode;
    int result;
    float clampedTime;
    float localTime;

    // Get pointers from the animation state structure
    intPtr = *(int**)((int)animState + 4); // +0x4: pointer to an int array? [0]=index? [1]=float, [2]=float
    // Check if the state's active flag is valid (byte at +0x1)
    if (*(char*)((int)animState + 1) < 1) {
        return 0;
    }

    bytePtr = *(byte**)((int)animState + 0xc); // +0xc: pointer to opcode byte
    opcode = *intPtr;
    localTime = timeDelta;

    // Validate the opcode index and call a function from a global dispatch table
    if ((-1 < opcode) && (opcode < DAT_01205574)) {
        funcPtr = *(code**)(DAT_01205570 + 4 + opcode * 0xc);
        if (funcPtr != (code*)0x0) {
            (*funcPtr)(thisObj, opcode, &localTime);
        }
    }

    // Normalize the time: compute progress relative to start and duration
    clampedTime = (localTime - (float)intPtr[1]) / (float)intPtr[2]; // intPtr[1] = start offset, intPtr[2] = duration
    if (clampedTime <= 0.0f) {
        clampedTime = 0.0f;
    } else {
        float maxTime = DAT_00e2b1a4;
        if (maxTime < clampedTime) {
            clampedTime = maxTime;
        }
    }

    // Read the opcode byte and dispatch to handler
    byte opcodeByte = *bytePtr;
    if ((opcodeByte & 0x3f) < 0x23) { // 0x23 = 35, so opcodes 0-34 are valid
        // Call handler via function pointer table
        funcPtr = (code*)(&DAT_0103afc0)[opcodeByte & 0x3f];
        result = funcPtr(thisObj, bytePtr, param4, param5, param6, param7, param8);
        if (result == 0) {
            FUN_0056fb60(); // Cleanup function (likely unlocks memory)
            return 0;
        }
        int handlerResult = result;
        int finalResult = FUN_005850c0(handlerResult, clampedTime, param7);
        FUN_0056fb60();
        return finalResult;
    }

    FUN_0056fb60();
    return 0;
}