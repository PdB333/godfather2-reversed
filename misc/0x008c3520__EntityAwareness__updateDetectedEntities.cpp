// FUNC_NAME: EntityAwareness::updateDetectedEntities
void __fastcall EntityAwareness::updateDetectedEntities(int thisPtr)
{
    int *globalList;
    int listCount;
    int otherEntity;
    undefined4 otherValue;
    int currentCount;
    int capacity;
    int newCapacity;
    undefined4 *arrayPtr;

    // Global singleton managing entities (DAT_01129904)
    globalList = (int *)(DAT_01129904 + 0x30);  // pointer to array of entity pointers
    listCount = *(int *)(DAT_01129904 + 0x34);  // number of entities in list
    FUN_008bddc0(*(int *)(DAT_01129904 + 0x34) - 1); // unclear call, possibly pre-decrement count

    if (listCount != 0)
    {
        for (int i = 0; i < listCount; i++)
        {
            otherEntity = *(int *)(*globalList + i * 4);
            if (otherEntity != thisPtr)
            {
                otherValue = *(undefined4 *)(otherEntity + 0x54); // some ID/pointer from other entity
                currentCount = *(int *)(thisPtr + 0x194); // +404: current number of stored elements
                capacity = *(int *)(thisPtr + 400);       // +0x190: allocated capacity (in elements)

                if (capacity == currentCount)
                {
                    // Double capacity (or start at 1)
                    newCapacity = (currentCount == 0) ? 1 : (currentCount * 2);
                    FUN_008bddc0(newCapacity); // resize internal array to new capacity
                }

                arrayPtr = (undefined4 *)(*(int *)(thisPtr + 0x18c) + *(int *)(thisPtr + 400) * 8);
                *(int *)(thisPtr + 400) = *(int *)(thisPtr + 400) + 1; // increment count
                if (arrayPtr != (undefined4 *)0x0)
                {
                    *arrayPtr = otherValue;
                    arrayPtr[1] = 0; // second 4-byte field (e.g., flag or timestamp)
                }
            }
        }
    }
}