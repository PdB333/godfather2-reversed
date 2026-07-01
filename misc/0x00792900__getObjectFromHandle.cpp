// FUNC_NAME: getObjectFromHandle
// Address: 0x00792900
// Role: Resolves a handle to an object pointer, optionally releasing a reference, and frees temporary list.

#include <cstdint>

// Forward declarations of called functions
bool handleToObject(uint32_t handle, int* objectListOut, int* indexOut, int* versionOut, uint32_t* resultOut);
void releaseObject(uint32_t object);
void operatorDelete(void* ptr);

uint32_t getObjectFromHandle(uint32_t handle)
{
    int objectList[3] = {0, 0, 0};  // +0x00: pointer to array of object pointers, +0x04 and +0x08 unused
    int index = 0;                  // Index into the object list
    int version = -1;               // Version/counter check
    uint32_t resultObject = 0;      // The resolved object pointer

    bool success = handleToObject(handle, objectList, &index, &version, &resultObject);

    int listPtr = objectList[0];    // Save for later cleanup
    uint32_t retVal = resultObject;

    // If handle resolved successfully, the object at listPtr[index] has a non-zero field at +0x04,
    // and version is valid, then release the object.
    if (success &&
        (*(int*)(*(int*)(listPtr + index * 4) + 4) != 0) &&
        (version >= 0))
    {
        releaseObject(resultObject);
    }

    // Free the temporary object list if it was allocated
    if (listPtr != 0)
    {
        operatorDelete((void*)listPtr);
    }

    return retVal;
}