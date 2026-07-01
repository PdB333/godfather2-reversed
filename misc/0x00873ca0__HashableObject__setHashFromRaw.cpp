// FUNC_NAME: HashableObject::setHashFromRaw
int __thiscall HashableObject::setHashFromRaw(int thisPtr, int* rawData)
{
    int result = 0;

    // Check if the input 128-bit value (4 ints) is all zeros
    if (rawData[0] != 0 || rawData[1] != 0 || rawData[2] != 0 || rawData[3] != 0)
    {
        // Initialize hash processing context (FUN_005e3070)
        HashableObject::beginHashProcess();

        // Setup stack frame: local_10 points to a static jump table or vtable,
        // local_c stores this pointer for later use (FUN_005e6500 likely uses it)
        void* local_10 = &LAB_00873b90;  // some data/label
        int local_c = thisPtr;

        // Compute a 128-bit hash from rawData, output to local_20 (16 bytes on stack)
        // Returns handle/pointer to computed hash (or zero on failure)
        result = HashableObject::computeHash(rawData, local_20);  // FUN_005e6500
        if (result != 0)
        {
            // Store the computed hash into the object at offset +0x10
            HashableObject::storeHash(result, thisPtr + 0x10);  // FUN_005e6580
        }
    }
    return result;
}