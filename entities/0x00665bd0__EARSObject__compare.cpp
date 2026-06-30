// FUNC_NAME: EARSObject::compare
int EARSObject::compare(EARSObject* other) {
    int thisType = *(int*)((char*)this + 0x8);
    int otherType = *(int*)((char*)other + 0x8);

    if (thisType != otherType) {
        // Primary ordering: if thisType is not 1, return 1; else return -1
        return (thisType != 1) ? 1 : -1;
    }

    // Types equal, delegate to secondary comparison
    if (thisType == 1) {
        return FUN_00665c30();
    }
    return FUN_00665c30();
}