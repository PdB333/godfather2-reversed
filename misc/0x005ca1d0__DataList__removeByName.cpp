// FUNC_NAME: DataList::removeByName
void DataList::removeByName(void)
{
    // this structure layout (offsets relative to this):
    // +0x00: unknown (vtable or other)
    // +0x10: pointer to array of elements (each element = 0x114 bytes)
    // +0x14: number of elements (int)
    // +0x1c: pointer to search string (const char*)

    int elementArrayPtr = *(int *)(this + 0x10);
    int count = *(int *)(this + 0x14);
    const char* searchName = *(const char **)(this + 0x1c); // name to match

    int foundIndex = -1;
    int offset = 0;

    if (count > 1) {
        for (int idx = 0; idx < count; idx++) {
            int elementBase = elementArrayPtr + offset;
            const char* elementName = (const char *)(elementBase + 4);

            // compute length of elementName via pointer arithmetic
            const char* p = elementName;
            while (*p != '\0') {
                p++;
            }
            int nameLen = p - (elementBase + 5); // actual length without null terminator

            if (_strncmp(searchName, elementName, nameLen) == 0) {
                foundIndex = idx;
                // sanity check (should never be negative)
                if (foundIndex < 0) {
                    return;
                }
                break;
            }
            offset += 0x114; // each element is 0x114 bytes
        }
    }

    // if a matching element was found, remove it by index
    if (foundIndex < count) {
        FUN_005ca250(); // internal removal helper (likely shifts remaining elements or adjusts count)
    }
}