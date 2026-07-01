// FUNC_NAME: ObjectPoolManager::addObject
// Address: 0x0097d020
// Role: Adds an object to a limited-size pool if conditions are met (object valid, property check, priority negative, total count < 8)

void __thiscall ObjectPoolManager::addObject(int thisPtr, int objectPtr)
{
    char isValid;
    int propertyValue;
    int totalCount;
    int priority;

    // Check if object is valid/active
    isValid = isObjectValid(objectPtr);
    if (isValid != '\0')
    {
        // Check some property from object+0x38 (e.g., type flag)
        propertyValue = getSomeProperty(*(undefined4 *)(objectPtr + 0x38));
        if (propertyValue != 0)
        {
            // Read current index (also count of stored objects)
            int currentIndex = *(int *)(thisPtr + 0x9c); // +0x9c: m_currentIndex

            // Sum all category counts and current index
            totalCount = *(int *)(thisPtr + 0x78) + // +0x78: m_countCategoryC
                         *(int *)(thisPtr + 0x54) + // +0x54: m_countCategoryB
                         *(int *)(thisPtr + 0x30) + // +0x30: m_countCategoryA
                         currentIndex;

            // Check total capacity (max 8) and priority (negative = high priority)
            if ((totalCount < 8) && (priority = getPriority(objectPtr), priority < 0))
            {
                // Store object in array at +0x7c (m_objectArray[8])
                *(int *)(thisPtr + 0x7c + currentIndex * 4) = objectPtr;
                // Increment current index
                *(int *)(thisPtr + 0x9c) = currentIndex + 1;

                // If total was 0 before adding, start processing the list
                if (totalCount == 0)
                {
                    startProcessingList(); // FUN_0097c5a0
                }

                // If this is the first object added, enter critical section
                if (*(int *)(thisPtr + 0x9c) == 1)
                {
                    EnterCriticalSection(&DAT_0112a638); // FUN_00407e40
                }
            }
        }
    }
    return;
}