// FUNC_NAME: SomeClass::releaseAndDelete
int* __thiscall SomeClass::releaseAndDelete(int* thisPtr, byte shouldDelete)
{
    if (*thisPtr != 0) {
        this->release(thisPtr);  // +0x00: pointer to internal data; calls destructor/cleanup
    }
    if (shouldDelete & 1) {
        operatorDelete(thisPtr); // free allocated memory
    }
    return thisPtr;
}