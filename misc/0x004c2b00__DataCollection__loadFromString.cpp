// FUNC_NAME: DataCollection::loadFromString
void __thiscall DataCollection::loadFromString(int thisPtr, SomeRefCountedObject* obj, const char* str)
{
    // Delimiter for strtok (likely "\n" or similar global)
    char delimiter[3];
    *(uint16_t*)delimiter = DAT_00e3621c; // first two bytes from global
    delimiter[2] = DAT_00e3621e;          // third byte (null terminator)

    int firstToken;
    char* token = _strtok(str, delimiter);
    FID_conflict__sscanf(token, "%d\n", &firstToken);
    if (firstToken != 1) {
        return;
    }

    // Allocate new HexEntry (sizeof=0x10)
    HexEntry* entry = (HexEntry*)FUN_009c8e50(0x10);
    if (entry == nullptr) {
        entry = nullptr; // just to keep structure, original assigns 0
    } else {
        entry->object = obj;
        entry->hexData = nullptr;
        entry->hexCount = 0;
        entry->hexCapacity = 0;
        // Increment reference count of the object (refCount at offset 0)
        obj->refCount++;
    }

    // Add entry to outer dynamic array (this+0x208, size at +0x20c, capacity at +0x210)
    int* entryCount  = (int*)(thisPtr + 0x20c);
    int* entryCap    = (int*)(thisPtr + 0x210);
    if (*entryCount == *entryCap) {
        int newCap = (*entryCap == 0) ? 1 : (*entryCap * 2);
        FUN_004c2e30(newCap); // Resizes outer array, updates this+0x208 and +0x210
    }
    int** entryArray = (int**)(thisPtr + 0x208);
    entryArray[*entryCount] = (int)entry;
    (*entryCount)++;

    // Now parse hex values from the remainder of str
    int hexValue;
    while (true) {
        token = _strtok(nullptr, delimiter);
        if (token == nullptr) {
            return;
        }
        int matched = FID_conflict__sscanf(token, "0x%x", &hexValue);
        if (matched == 0) {
            return; // Stop if no match (control flow matches original: loop while iVar4 != 0)
        }
        // Add hexValue to entry's internal array (entry->hexData at +4, hexCount +8, hexCapacity +12)
        if (entry->hexCount == entry->hexCapacity) {
            int newCap = (entry->hexCapacity == 0) ? 1 : (entry->hexCapacity * 2);
            FUN_00486800(newCap); // Resizes hex array inside entry, updates hexData and hexCapacity
        }
        entry->hexData[entry->hexCount] = hexValue;
        (entry->hexCount)++;
    }
}