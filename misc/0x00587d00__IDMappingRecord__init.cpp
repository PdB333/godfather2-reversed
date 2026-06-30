// FUNC_NAME: IDMappingRecord::init
int* __thiscall IDMappingRecord::init(int* thisPtr, int managerPtr, int contextObj, uint idKey) {
    char* contextData = *(char**)(contextObj + 0x60);
    int firstId = -1;
    if (contextData != nullptr && *contextData == 0x02) {
        int** idPtr = (int**)(contextData + 4);
        if (idPtr != nullptr) {
            firstId = **idPtr;
        }
    }

    // Hash table: managerPtr->hashTableHeader (at offset 0x70+0x30)
    int* hashHeader = *(int**)(*(int*)(managerPtr + 0x70) + 0x30);
    uint* bucketPtr = (uint*)hashHeader[0];
    uint bucketCount = (uint)hashHeader[1];
    uint* node = *(uint**)(bucketPtr + (idKey % bucketCount) * 4);

    char* lookupData = nullptr;
    int secondId = -1;

    while (node != nullptr) {
        if (node[0] == idKey) {
            if (node != (uint*)0x0 && node != (uint*)0xfffffffc) {
                lookupData = (char*)node[2];
            } else {
                lookupData = nullptr;
            }
            break;
        }
        node = (uint*)node[3];
    }

    if (lookupData != nullptr && *lookupData == 0x02) {
        int** idPtr = (int**)(lookupData + 4);
        if (idPtr != nullptr) {
            secondId = **idPtr;
        }
    }

    thisPtr[0] = managerPtr;
    thisPtr[1] = contextObj;
    thisPtr[2] = firstId;
    thisPtr[3] = idKey;
    thisPtr[4] = secondId;
    thisPtr[5] = 0;
    return thisPtr;
}