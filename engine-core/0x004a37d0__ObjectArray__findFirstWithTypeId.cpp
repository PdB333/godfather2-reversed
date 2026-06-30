// FUNC_NAME: ObjectArray::findFirstWithTypeId
// Address: 0x004a37d0
// Searches the array of object pointers at +0x1C (array of pointers to objects), count at +0x20,
// for the first object whose type field at +0x14 (offset 20 bytes into object) equals 0x10.
// Returns the first DWORD of that object (e.g., an ID or handle), or 0 if not found.
unsigned int __fastcall ObjectArray::findFirstWithTypeId(ObjectArray* thisPtr)
{
    unsigned int result = 0;
    unsigned short count = *(unsigned short*)((char*)thisPtr + 0x20);
    if (count != 0)
    {
        unsigned short index = 0;
        while (true)
        {
            // Fetch pointer to current object from array at +0x1C
            unsigned int* objPtr = *(unsigned int**)(*(int*)((char*)thisPtr + 0x1C) + index * 4);
            // Compare type field at object[5] (offset 0x14) with 0x10
            if (objPtr[5] == 0x10)
            {
                result = objPtr[0]; // Return first field of matching object
                break;
            }
            index++;
            if (count <= index)
            {
                break;
            }
        }
    }
    return result;
}