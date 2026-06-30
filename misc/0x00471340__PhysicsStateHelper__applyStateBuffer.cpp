// FUNC_NAME: PhysicsStateHelper::applyStateBuffer
void __fastcall PhysicsStateHelper::applyStateBuffer(int *thisPtr) {
    int *stateBuffer; // +0x74
    int *parentNode; // from +0x68
    int *targetState; // local
    float localTransform[4]; // 4 floats
    float localVelocity[4];
    float localAccel[4];
    float sentinel = *(float*)DAT_00e2b1a4; // likely 0x7F7FFFFF (NaN) or 0

    stateBuffer = (int *)(thisPtr + 0x1d);          // +0x74
    localTransform[0] = 0; localTransform[1] = 0; localTransform[2] = 0; localTransform[3] = sentinel;
    localVelocity[0] = 0; localVelocity[1] = 0; localVelocity[2] = 0; localVelocity[3] = sentinel;
    localAccel[0] = 0; localAccel[1] = 0; localAccel[2] = 0; localAccel[3] = sentinel;

    // copy from this->stateBuffer into localTransform (12 bytes)
    (*(void (**)(void*, void*, int))(*(int*)thisPtr + 0x8c))(localTransform, stateBuffer, 1);

    if (thisPtr[0x1a] == 0) {
        parentNode = 0;
    } else {
        parentNode = (int *)(thisPtr[0x1a] - 0x48); // parent struct offset
    }

    // copy target state from parent using this->someField (offset +0x70) as parameter
    (*(void (**)(void*, void*, int))(*(int*)parentNode + 0x90))(localAccel, (void *)(thisPtr + 0x1c), 1);

    FUN_00424470(); // unknown helper: probably end-of-frame sync

    if (thisPtr[0x1e] != 0) { // buffer is active
        FUN_00417560(); // begin update block? (stack frame setup)
        // reinitialize localAccel for pending send
        localAccel[0] = 0;
        localAccel[1] = 0;
        localAccel[2] = localTransform[3]; // carry over sentinel?
        localAccel[3] = 0;
        // ... more assignments mimic the original but omitted for clarity
    }

    FUN_00417560(); // end update block?

    // Select vfunc based on bitfield at +0x15e
    void (*dispatchFunc)(void*);
    void *dispatchArg;
    if (((unsigned char)thisPtr[0x15e / 4] & 1) == 0) {
        dispatchFunc = (void (*)(void*))(*(int*)thisPtr + 0x2c);
        dispatchArg = (void *)&stateBuffer; // actually pointer to stack structure
    } else {
        dispatchFunc = (void (*)(void*))(*(int*)thisPtr + 0x1c);
        dispatchArg = (void *)&thisPtr[0x2e / 4]; // some other stack variable
    }

    // Prepare argument structure
    int stackArg[2];
    stackArg[0] = (int)stateBuffer;
    stackArg[1] = 1; // count or flag
    dispatchFunc(dispatchArg);

    // Retrieve parent again and propagate results
    if (thisPtr[0x1a] == 0) {
        parentNode = 0;
    } else {
        parentNode = (int *)(thisPtr[0x1a] - 0x48);
    }
    int state1 = (*(int (**)(void))(*(int*)parentNode + 0x50))();
    (*(void (**)(int))(*(int*)thisPtr + 0x54))(state1);

    if (thisPtr[0x1a] == 0) {
        parentNode = 0;
    } else {
        parentNode = (int *)(thisPtr[0x1a] - 0x48);
    }
    int state2 = (*(int (**)(int))(*(int*)parentNode + 0x58))(0xffffffff);
    (*(void (**)(int))(*(int*)thisPtr + 0x5c))(state2);
}