// FUNC_NAME: ObjectSet::findLastMatching
uint __thiscall ObjectSet::findLastMatching(int this, int* outIndex, uint* outValue, byte* outType, uint fallbackResult)
{
    uint result;
    int count;
    int* array;
    int* currentPtr;
    int element;
    int innerStruct;
    uint matchedValue;
    byte typeByte;

    // fallbackResult corresponds to the in_EAX register at function entry
    result = fallbackResult & 0xffffff00;

    // +0x30: pointer to array of pointers
    // +0x34: number of elements
    count = *(int*)(this + 0x34) - 1;
    if (count >= 0)
    {
        array = (int*)(*(int*)(this + 0x30) + count * 4);
        do
        {
            element = *array;
            innerStruct = *(int*)(element + 4);
            *outIndex = 0;
            // FUN_00605d00 is a condition checker that may modify *outIndex
            if ((char)FUN_00605d00(outIndex) != 0)
            {
                // innerStruct +0x1c is a pointer to an array of 4-byte values
                matchedValue = *(uint*)(*(int*)(innerStruct + 0x1c) + *outIndex * 4);
                *outValue = matchedValue;
                // element +0x8 holds a type byte
                typeByte = *(byte*)(element + 8);
                *outType = typeByte;
                // return (matchedValue & 0xffffff00) | 1
                return (matchedValue & 0xffffff00) | 1;
            }
            array = array - 1;
            count = count - 1;
        }
        while (count >= 0);
    }
    return result;
}