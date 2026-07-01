// FUNC_NAME: SimObjectManager::findObjectByID
// 0x008ff210: Iterates over an array of objects to find one with matching ID at +0x54.
// Returns pointer to the object (int*) or nullptr if not found.

int* SimObjectManager::findObjectByID(int id) const
{
    int* result = nullptr;
    unsigned int index = 0;

    // count at this+0x14, array of pointers at this+0x10
    if (count != 0)
    {
        int** pArray = objectArray; // this+0x10: array of pointers to objects
        while ((*pArray)[0x54] != id) // object->id at +0x54
        {
            index++;
            pArray++;
            if (count <= index)
            {
                return result; // not found
            }
        }
        result = objectArray[index];
    }
    return result;
}