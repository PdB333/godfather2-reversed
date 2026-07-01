// FUNC_NAME: ResourceManager::resolveAsset
void __thiscall ResourceManager::resolveAsset(int* thisPtr, bool forceCreate, uint32_t nameHash) {
    int resourceCount = (**(code**)(*thisPtr + 0x19c))();  // vtable[0x67] – get number of known resource types
    if (resourceCount < 1) {
        return;
    }
    int firstResourceKey = (**(code**)(*thisPtr + 0x19c))(0); // vtable[0x67] – get first type key
    int* hashComponents = (int*)FUN_004352c0(nameHash, firstResourceKey, 0); // unpacks 128-bit hash into 4 ints
    int hash0 = hashComponents[0];
    int hash1 = hashComponents[1];
    int hash2 = hashComponents[2];
    int hash3 = hashComponents[3];
    if (hash0 == 0 && hash1 == 0 && hash2 == 0 && hash3 == 0) {
        return;
    }
    // Global initialization flag for hash database
    if (DAT_0112da14 == 0) {
        FUN_007f6f90();  // initialise hash lookup table
        DAT_0112da14 = 1;
    }
    void* searchKey = (void*)FUN_004e0460(&hash0); // convert hash to search key
    void* foundEntry = _bsearch(searchKey, &DAT_0112ca78, 0x6f, 0x20, (_PtFuncCompare*)&LAB_007f6f20);
    if (foundEntry != NULL) {
        // Found existing asset – activate it
        (**(code**)(*thisPtr + 0xa8))(*(uint32_t*)((int)foundEntry + 0x10), 0); // vtable[0x2a] – useExistingAsset
        return;
    }
    // Not in database – create new asset from prototype
    int protoDataPtr = FUN_00471610(); // returns address of a prototype structure
    uint64_t nameString = *(uint64_t*)(protoDataPtr + 0x30);
    uint32_t extraData = *(uint32_t*)(protoDataPtr + 0x38);
    if (forceCreate || ((thisPtr[0x6e5] >> 0x14) & 1) != 0) {
        // Use slot for forced or already created
        int* targetSlot = (forceCreate) ? (thisPtr + 0x1b6) : (thisPtr + 0x1b5);
        (**(code**)(*thisPtr + 0xa4))(&nameString, targetSlot); // vtable[0x29] – setPrototypeName
    }
    // Copy prototype data (64 bytes) to local buffer
    uint32_t localBuffer[12];
    uint32_t* srcBuffer = (uint32_t*)FUN_00471610(); // re-call to get same pointer? Might be a static
    for (int i = 0; i < 16; i++) {
        localBuffer[i] = srcBuffer[i];
    }
    uint64_t localName = nameString;
    uint32_t localExtra = extraData;
    char assetBuffer[76]; // buffer for asset creation
    FUN_0044b4e0(assetBuffer, localBuffer); // convert/copy prototype to asset buffer
    uint32_t factoryHandle = (**(code**)(*thisPtr + 0x58))(0, thisPtr, 0, 0); // vtable[0x16] – getObjectFactory
    int assetIdx = FUN_004df330(&assetIdx, &hash0, assetBuffer, factoryHandle); // register new asset
    if (assetIdx != 0) {
        *(uint32_t*)(assetIdx + 8) = 0; // clear unknown field
    }
    return;
}