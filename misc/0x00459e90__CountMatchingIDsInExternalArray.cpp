// FUNC_NAME: CountMatchingIDsInExternalArray
int __fastcall CountMatchingIDsInExternalArray(int unusedParam1, int object, int* externalArray, int externalArrayCount) // param1 in ECX (unused), object in EDX, externalArray on stack, externalArrayCount passed in EDI (custom calling)
{
    uint internalCount = *(ushort*)(object + 0x2c); // number of internal IDs stored at +0x2c
    int matchCount = 0;

    if (internalCount != 0)
    {
        int* internalArray = *(int**)(object + 0x90); // pointer to array of internal IDs at +0x90
        do
        {
            uint j = 0;
            if (externalArrayCount != 0)
            {
                do
                {
                    // Compare the current internal ID with the first 4-byte field of each 8-byte entry in the external array
                    if (*internalArray == externalArray[j / 8]) // Actually param_3 + j*8, but we treat as array of 8-byte structs, compare first int
                    {
                        matchCount++;
                    }
                    j++;
                } while (j < externalArrayCount);
            }
            internalArray++;
            internalCount--;
        } while (internalCount != 0);
    }
    return matchCount;
}