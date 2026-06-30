// FUNC_NAME: AssetManager::getAsset
// Address: 0x005e49d0
// Role: Load an asset by ID and create a runtime object from its data.
// param_1 (ECX) is unused – likely a static or thunked method.
// param_2 (EDX) = asset ID (hash or index)
// param_3 (stack) = output pointer where the new object handle is stored
// Returns: non‑zero handle on success, 0 on failure.

int __fastcall AssetManager::getAsset(
    void* /*this*/,          // ECX – not used
    int assetId,             // EDX
    int* outHandle           // stack param
)
{
    void* dataPtr;       // buffer to receive pointer to raw asset data
    int dataSize;        // size of that data
    int result;

    result = FUN_005f0560(assetId, &dataPtr, &dataSize);
    if (result != 0 && dataSize != 0)
    {
        // Create the runtime object from the raw data and return its handle
        *outHandle = FUN_005e4a20(*outHandle, (int)dataPtr);
        return *outHandle;
    }
    return 0;
}