// FUNC_NAME: Entity::initFromMemberPointer
void Entity::initFromMemberPointer() {
    // Read 4-byte value at offset +0x70 (likely a handle or pointer to a sub-object)
    int resourceHandle = *(int*)((char*)this + 0x70);
    // Build a temporary 9-byte structure on the stack
    struct TempInitData {
        int handle;      // +0x00
        int zeroField;   // +0x04
        char flag;       // +0x08
    } initData;
    initData.handle = resourceHandle;
    initData.zeroField = 0;
    initData.flag = 0;
    // Call internal initialization routine with pointer to the temp data and a zero flag
    FUN_00408a00(&initData, 0);
}