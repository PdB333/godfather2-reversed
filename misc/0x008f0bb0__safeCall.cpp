// FUNC_NAME: safeCall
uint32_t safeCall(uint32_t object, uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
    int32_t result;
    uint32_t instance;

    // Check if the object is valid or has a specific property (FUN_004461c0)
    result = FUN_004461c0(object, 0);
    if (result != 0) {
        // Obtain a global manager or context object (e.g., game manager)
        instance = FUN_0043aaf0();
        // Delegate to the actual processing function with the validated object and additional arguments
        return FUN_008f0520(instance, object, arg3, result, arg1, arg2);
    }
    return 0;
}