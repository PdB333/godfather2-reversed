// FUNC_NAME: EARSObject::release
void EARSObject::release()
{
    int *smartPtr;
    int *refCounter;

    // Release object at offset +0x64 (pointer to shared data)
    smartPtr = *(int **)(this + 0x64);
    if (smartPtr != nullptr) {
        refCounter = smartPtr + 2; // ref count at offset +8 from the pointed-to object's start
        *refCounter = *refCounter - 1;
        if (*refCounter == 0) {
            // Call virtual destructor through vtable (method at vtable+8)
            (**(code **)(*smartPtr + 8))();
        }
    }

    // Subtract allocated memory size from global counter (offset +0x54 holds size)
    if (*(int *)(this + 0x54) != 0) {
        gTotalAllocatedMemory -= *(int *)(this + 0x54);
    }

    // Free the buffer pointer stored at offset +0x5c
    _free(*(undefined4 *)(this + 0x5c));

    // Release object at offset +0x2c
    smartPtr = *(int **)(this + 0x2c);
    if (smartPtr != nullptr) {
        refCounter = smartPtr + 2;
        *refCounter = *refCounter - 1;
        if (*refCounter == 0) {
            (**(code **)(*smartPtr + 8))();
        }
    }

    // Release object at offset +0x28
    smartPtr = *(int **)(this + 0x28);
    if (smartPtr != nullptr) {
        refCounter = smartPtr + 2;
        *refCounter = *refCounter - 1;
        if (*refCounter == 0) {
            (**(code **)(*smartPtr + 8))();
        }
    }

    // Release object at offset +0x24
    smartPtr = *(int **)(this + 0x24);
    if (smartPtr != nullptr) {
        refCounter = smartPtr + 2;
        *refCounter = *refCounter - 1;
        if (*refCounter == 0) {
            (**(code **)(*smartPtr + 8))();
        }
    }

    // Release object at offset +0x20
    smartPtr = *(int **)(this + 0x20);
    if (smartPtr != nullptr) {
        refCounter = smartPtr + 2;
        *refCounter = *refCounter - 1;
        if (*refCounter == 0) {
            // Warning: indirect jump, vtable call assumed
            (**(code **)(*smartPtr + 8))();
        }
    }
}