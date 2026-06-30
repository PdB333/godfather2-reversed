// FUNC_NAME: SomeClass::findClosestIndex
int SomeClass::findClosestIndex() // __thiscall, address 0x00554200
{
    int count = *(int*)((char*)this + 0x68); // Number of elements in the array
    int bestIndex = -1;
    float bestValue = DAT_00e2b334; // Global initial large float (likely INF)

    for (int i = 0; i < count; i++)
    {
        float currentValue = computeDistanceForIndex(i); // Calls FUN_005540a0
        if (currentValue < bestValue)
        {
            bestValue = currentValue;
            bestIndex = i;
        }
    }

    return bestIndex;
}