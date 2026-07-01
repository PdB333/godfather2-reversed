//FUNC_NAME: SomeClass::sumRecentWindowedValues
float __thiscall SomeClass::sumRecentWindowedValues(int thisPtr, int currentTime)
{
    int index = *(int *)(thisPtr + 0x890);          // current write index into ring buffer
    float sum = 0.0f;
    int *entryPtr = (int *)(thisPtr + 0x868 + index * 8); // base of ring buffer + index * 8 bytes per entry
    int entryTime = *entryPtr;                      // first int: timestamp
    int i = index;
    
    // Walk backwards through the ring buffer, summing values whose timestamp is within 0x30d4 (12500) of currentTime
    while ((uint)(currentTime - entryTime) < 0x30d4) {
        i = i - 1;
        sum = (float)entryPtr[1] + sum;             // second int: value (cast to float)
        entryPtr = entryPtr - 2;                    // move to previous entry (each entry is 2 ints)
        if (i == index) break;                      // wrapped around full circle
        entryTime = *entryPtr;
    }
    return (float10)sum;
}