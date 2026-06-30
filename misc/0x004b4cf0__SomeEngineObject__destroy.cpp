// FUNC_NAME: SomeEngineObject::destroy
int __thiscall SomeEngineObject::destroy(int thisPtr, byte deallocFlag) {
    // Call base destruction (common destruction logic)
    baseDestructor();

    // If the object was dynamically allocated (deallocFlag & 1), free the memory
    if (deallocFlag & 1) {
        operatorDelete(thisPtr);
    }

    return thisPtr;
}