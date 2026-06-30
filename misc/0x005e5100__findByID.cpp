// FUNC_NAME: findByID
// Function at 0x005e5100: Searches a container for an object with a specific ID.
// Container type has an array of object pointers at offset +0x6014 and count at +0x6018.
// Each object pointer points to a structure where the ID field is at offset +0x04.
// Returns pointer to the found object, or nullptr if not found.
void* __fastcall findByID(void* container, int objectID)
{
    uint count = *(uint*)((char*)container + 0x6018);
    if (count != 0)
    {
        int** arrayPtr = *(int***)((char*)container + 0x6014);
        for (uint i = 0; i < count; i++)
        {
            int* currentPtr = arrayPtr[i];
            if (currentPtr != nullptr && *(int*)((char*)currentPtr + 4) == objectID)
            {
                return currentPtr;
            }
        }
    }
    return nullptr;
}