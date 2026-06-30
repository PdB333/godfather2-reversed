// FUNC_NAME: AssetLoader::processLoadRequest
int __thiscall AssetLoader::processLoadRequest(int this_ptr)
{
    int outputPtr = 0;
    // Retrieve first field at +0x10 (e.g., pointer to asset data block)
    int fieldA = getPointerFromOffset(this_ptr + 0x10, &outputPtr);
    // Retrieve second field at +0x1c (e.g., load type flag)
    char loadType = getPointerFromOffset(this_ptr + 0x1c, &outputPtr);
    int assetPtr = outputPtr;
    if (outputPtr == 0) {
        return 0;
    }
    if (loadType == '\0') {
        // Existing/replacement asset path
        onReplaceAsset(assetPtr); // FUN_006f9180
        int assetId = *(int *)(assetPtr + 0xc); // ID at offset +0x0c
        copyData(assetId, 0x1ff, assetPtr); // FUN_004035f0 – copy up to 511 bytes
        postLoad(); // FUN_006f97b0
        registerLoadedAsset(assetPtr); // FUN_006f9f90
        int objId = getObjectById(assetId); // FUN_004025a0
        if (objId != 0) {
            callReplaceMethod(objId, 0); // FUN_004048c0
        }
    } else {
        // New asset path
        onNewAsset(assetPtr); // FUN_006f91c0
        int assetId = *(int *)(assetPtr + 0xc);
        postLoad(); // FUN_006f97b0
        registerLoadedAsset(assetPtr); // FUN_006f9f90
        int objId = getObjectById(assetId); // FUN_004025a0
        if (objId != 0) {
            callNewMethod(objId); // FUN_00404c40
            return 1;
        }
    }
    return 1;
}