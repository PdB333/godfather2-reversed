// FUNC_NAME: ObjectManager::FindObjectByName
int __fastcall ObjectManager::FindObjectByName(void* thisPtr, const char* name)
{
    // +0x08: pointer to array descriptor (count + data)
    ArrayDescriptor* arrayDesc = *(ArrayDescriptor**)((char*)thisPtr + 0x08);
    if (arrayDesc == nullptr)
        return 0;

    // +0x04: number of entries
    uint32_t count = arrayDesc->count;
    if (count == 0)
        return 0;

    // +0x08: pointer to array of object pointers
    void** objects = arrayDesc->data;
    uint32_t idx = 0;
    do {
        // Each object has a name string at offset 0x40
        const char* objName = *(const char**)((char*)objects[idx] + 0x40);
        // Compare two bytes at a time (optimization)
        int cmpResult;
        const char* p1 = objName;
        const char* p2 = name;
        do {
            char c1 = *p1;
            char c2 = *p2;
            bool less = c1 < c2;
            if (c1 != c2) {
                cmpResult = (1 - (int)less) - (int)(less ? 1 : 0);
                break;
            }
            if (c1 == '\0') {
                cmpResult = 0;
                break;
            }
            // Compare next pair
            char n1 = p1[1];
            char n2 = p2[1];
            less = n1 < n2;
            if (n1 != n2) {
                cmpResult = (1 - (int)less) - (int)(less ? 1 : 0);
                break;
            }
            p1 += 2;
            p2 += 2;
        } while (c1 != '\0');

        if (cmpResult == 0) {
            return (int)objects[idx];
        }
        idx++;
    } while (idx < count);

    return 0;
}