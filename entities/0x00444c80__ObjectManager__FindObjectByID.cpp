// FUNC_NAME: ObjectManager::FindObjectByID
// Function address: 0x00444c80
// Searches an array of object pointers for one whose first field (ID) matches the given id.
// The array is stored via a container structure at this+0x10.
// Container header layout: [0] = pointer to array of object pointers, [4] = count.

int* __thiscall ObjectManager::FindObjectByID(int id)
{
    int* result = nullptr;
    if (id != 0)
    {
        // Container header pointer at this+0x10
        int** containerHeader = *(int***)(this + 0x10);
        // Array of object pointers (each element is a pointer to an object whose first field is the ID)
        int** objPtrArray = (int**)*containerHeader;   // containerHeader[0]
        int count = (int)containerHeader[1];            // containerHeader[1]
        int** end = objPtrArray + count;
        // Linear search
        for (int** iter = objPtrArray; iter != end; ++iter)
        {
            int* obj = *iter;   // obj points to the ID field of the object
            if (obj != nullptr && *obj == id)
            {
                result = obj;
            }
        }
    }
    return result;
}