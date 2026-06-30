// FUNC_NAME: getInternalFlag
int __thiscall getInternalFlag(void *this) {
    undefined4 *internalPtr;
    
    internalPtr = (undefined4 *)getInternalPointer(this);
    if (internalPtr != NULL) {
        return *internalPtr; // offset 0x00
    }
    return 0;
}