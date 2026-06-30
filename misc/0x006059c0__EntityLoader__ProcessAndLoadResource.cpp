// FUNC_NAME: EntityLoader::ProcessAndLoadResource
void EntityLoader::ProcessAndLoadResource(void* context) {
    int resourceIndex = 0;
    char hasMore = getNextResourceIndex(this, &resourceIndex);
    if (hasMore) {
        const char* namePtr;
        int nameLen;
        if (DAT_012056c8 == '\0') {
            namePtr = nullptr;
            nameLen = 0;
        } else {
            namePtr = &DAT_012056c8;
            nameLen = 4;
        }
        // Load resource from table at this+0x1c using index, matching against DAT_00e2e230
        int loadedObj = loadResourceByName(
            *(uint32_t*)(*(int*)((char*)this + 0x1c) + resourceIndex * 4),
            DAT_00e2e230,
            nameLen,
            0,
            namePtr
        );
        *(int*)((char*)this + 0x34) = loadedObj;  // Store loaded object at +0x34
        if (loadedObj != 0) {
            addToManager(context);  // FUN_004d3d90
            // Initialize a temporary string (likely empty)
            uint32_t tempString[3]; // 12 bytes: 4 bytes pointer, 4 bytes length, 4 bytes capacity?
            tempString[0] = DAT_01222258;
            tempString[1] = 0;
            ((char*)tempString)[8] = 0;
            stringAssign(tempString, 0);  // Clear string
            void* objPtr = getObjectFromPointer(*(undefined4*)((char*)this + 0x34));
            if (objPtr != 0) {
                // Set state to 6 at offset 0x56
                setState((char*)objPtr + 0x56, 6);  // FUN_00402920
            }
        }
    }
}