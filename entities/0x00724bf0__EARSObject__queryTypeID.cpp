// FUNC_NAME: EARSObject::queryTypeID
int __thiscall EARSObject::queryTypeID(int typeId, int* outInterface) {
    // Match against a known type identifier (hash presumably)
    if (typeId == 0x8BD0E0EB) {  // -0x742f1f15 as unsigned
        *outInterface = (int)this;
        return 1;  // S_OK / true
    }
    *outInterface = 0;
    return 0;  // S_FALSE / false
}