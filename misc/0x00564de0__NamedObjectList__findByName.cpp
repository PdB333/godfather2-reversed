// FUNC_NAME: NamedObjectList::findByName
// Address: 0x00564de0
// This function performs a linear search through an array of named objects,
// comparing each object's name (obtained via virtual function at vtable+0x14)
// with the provided name string. Returns pointer to the object if found, else 0.
// Class layout:
//   +0x08: array of pointers to named objects (each 4 bytes)
//   +0x1c: number of entries (int32)

uint32_t NamedObjectList::findByName(const char* name)
{
    int32_t count = *(int32_t*)(this + 0x1c);
    if (count == 0) {
        return 0;
    }

    uint32_t index = 0;
    do {
        // Get pointer to current named object from the array
        void* objectPtr = *(void**)(this + 0x08 + index * 4);
        // Retrieve its name via virtual function at vtable offset 0x14
        // Assuming object has a vtable, and the method at index 5 returns const char*
        const char* objectName = (*(const char*(__thiscall**)(void*))(*(uint32_t*)objectPtr + 0x14))(objectPtr);

        // Compare strings byte-by-byte (case-sensitive)
        const char* pName = name;
        const char* pObjName = objectName;
        int32_t cmpResult;
        do {
            uint8_t c1 = *pObjName;
            uint8_t c2 = *pName;
            if (c1 != c2) {
                bool less = (c1 < c2);
                cmpResult = (1 - (uint32_t)less) - (uint32_t)(less != 0);
                break;
            }
            if (c1 == 0) {
                cmpResult = 0;
                break;
            }
            pObjName++;
            pName++;
        } while (true);

        if (cmpResult == 0) {
            // Found matching name, return the object pointer
            return *(uint32_t*)(this + 0x08 + index * 4);
        }

        index++;
    } while (index < (uint32_t)count);

    return 0;
}