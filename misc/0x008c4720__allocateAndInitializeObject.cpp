// FUNC_NAME: allocateAndInitializeObject
bool allocateAndInitializeObject(void* pManager, void* pObject)
{
    int randomValue = getRandomSeed(); // FUN_008c0060 - returns some random or sequential value
    uint count = (randomValue + 1) >> 1; // half of (randomValue+1), used as allocation size or count
    if (count != 0)
    {
        heapAllocate(count); // FUN_006b1e10 - memory allocation
        char initResult = objectInit(pManager, count, pObject); // FUN_008c0bb0 - initialize object
        if (initResult == '\0')
        {
            // Clear the success flag at offset +0x04
            if (*(int*)((char*)pObject + 4) != 0)
            {
                *(int*)((char*)pObject + 4) = 0;
            }
            objectCleanup(pManager, count, pObject); // FUN_008c2b50 - cleanup on failure
        }
    }
    // Return whether the success flag (offset +0x04) is non-zero
    return *(int*)((char*)pObject + 4) != 0;
}