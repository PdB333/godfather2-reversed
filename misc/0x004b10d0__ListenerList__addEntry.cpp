// FUNC_NAME: ListenerList::addEntry
void __thiscall ListenerList::addEntry(void** ppObject)
// Function at 0x004b10d0: adds a listener entry for the object pointed to by *ppObject.
// Container fields: +0x00: mEntries (int*) - pointer to array of 8-byte entries
//                   +0x04: mCount (int) - number of entries currently used
//                   +0x08: mCapacity (int) - allocated capacity (number of entries)
// Each entry (8 bytes): +0x00: object pointer (void*), +0x04: next pointer (void*)
// The object being listened to is assumed to have a "next" field at offset +0x04
// that points to the current head of the listener list for that object.
// New entry is inserted at the head of the object's listener list.
{
    int* thisPtr = reinterpret_cast<int*>(this);
    int* entries = reinterpret_cast<int*>(thisPtr[0]);  // +0x00
    int count = thisPtr[1];                             // +0x04
    int capacity = thisPtr[2];                          // +0x08

    // Grow the array if full
    if (count == capacity)
    {
        int newCapacity = (capacity == 0) ? 1 : (capacity * 2);
        grow(newCapacity);  // FUN_004b1440
        // Re-read fields after reallocation (grow may change pointers)
        entries = reinterpret_cast<int*>(thisPtr[0]);
        count = thisPtr[1];
        capacity = thisPtr[2];
    }

    // Pointer to the new entry slot
    int* newEntry = entries + count * 8;
    thisPtr[1] = count + 1;

    if (newEntry != nullptr)
    {
        int* object = *ppObject;  // The object to listen to, as stored by caller
        newEntry[0] = reinterpret_cast<int>(object);
        newEntry[1] = 0;  // Initialize next pointer to null

        if (object != 0)
        {
            // Insert at head of object's listener list
            // Object's next pointer at offset +0x04
            newEntry[1] = *(reinterpret_cast<int*>(object) + 1);
            *reinterpret_cast<int**>(reinterpret_cast<char*>(object) + 4) = newEntry;
        }
    }
    return;
}