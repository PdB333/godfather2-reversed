// FUNC_NAME: HashTable::tryInsert
// Address: 0x0088b0c0
// This function appears to be a hash table insertion or lookup check.
// The object at this has two fields: +0x04 = pointer to data array, +0x08 = index (count).
// param_2 is a pointer to input data. The function computes a hash of the input,
// checks if it matches a stored value in the array, then optionally encodes the data.

int __thiscall HashTable::tryInsert(int this, undefined4 *inputData)
{
    int hashResult[3]; // local_34
    int tempData;      // local_1c
    undefined4 uStack_28;
    undefined2 uStack_22;
    undefined2 local_24;
    undefined4 uStack_20;
    undefined8 local_18;
    undefined8 local_10;
    undefined8 local_8;

    // Compute hash from inputData; store in hashResult[0]
    FUN_008896d0(hashResult, inputData);

    // Compare hash with stored value: *(int*)(*(int*)(this+4) + *(int*)(this+8)*4)
    // this+4 is base pointer to array, this+8 is index (multiplied by 4)
    if (hashResult[0] == *(int *)(*(int *)(this + 4) + *(int *)(this + 8) * 4))
    {
        // Save first 4 bytes of input data
        tempData = *inputData;

        // Mask input pointer to clear low byte (maybe tag/type removal)
        inputData = (undefined4 *)((uint)inputData & 0xffffff00);

        // Clear hash result and temporary storage
        hashResult[0] = 0;
        hashResult[1] = 0;
        uStack_28 = 0;
        local_18 = 0;
        local_24 = 0;
        uStack_22 = 0;
        uStack_20 = 0;
        local_10 = (ulonglong)(uint)hashResult[2];
        local_8 = 0;

        // Encode or pack data
        FUN_008898a0(hashResult, &tempData, inputData);
    }

    // Return size (hashResult[0] + 4) possibly the final encoded size
    return hashResult[0] + 4;
}