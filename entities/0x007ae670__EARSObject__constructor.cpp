// FUNC_NAME: EARSObject::constructor
int __thiscall EARSObject::constructor(int thisPtr, byte flag) {
    // Call base initialization routine (global or static)
    BaseInit();
    // If the least significant bit of flag is set, perform cleanup/deallocation
    if (flag & 1) {
        operatorDelete(thisPtr);
    }
    return thisPtr;
}