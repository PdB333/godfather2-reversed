// FUNC_NAME: ObjectList::removeObjectByID
// Address: 0x00722060
// Removes an object from a circular buffer by matching its ID (stored at object+0x48).
// The buffer holds pointers to objects (each entry 0x24 bytes). Uses a tail-to-head scan.
void __thiscall ObjectList::removeObjectByID(int* thisPtr, int id)
{
    int head = thisPtr[1]; // +0x04: head index
    int tail = thisPtr[2]; // +0x08: tail index
    int capacity = thisPtr[0]; // +0x00: max capacity
    int* buffer = (int*)thisPtr[3]; // +0x0C: pointer to allocated array of entries

    while (tail != head)
    {
        int* entry = (int*)((char*)buffer + tail * 0x24); // each entry is 0x24 bytes
        int objectPtr = entry[0]; // first field: pointer to object (or null)
        int objectId;
        if (objectPtr == 0)
        {
            objectId = 0;
        }
        else
        {
            objectId = objectPtr - 0x48; // ID is stored at object+0x48
        }

        if (objectId == id)
        {
            // Prepare a zero buffer to clear the entry
            int zeroBuffer[4] = {0, 0, 0, 0};
            int zeroBuffer2[2] = {0, 0};
            int zeroInt = 0;

            // Destroy the object if the entry contains a non-null pointer
            if (entry != zeroBuffer && objectPtr != 0)
            {
                FUN_004daf90(entry); // likely destructor or release
                entry[0] = 0;
            }

            // Clear the entry fields piecewise
            entry[2] = zeroBuffer[2]; // offset +0x08
            entry[3] = zeroBuffer[3]; // offset +0x0C
            *(long long*)(entry + 5) = *(long long*)(zeroBuffer + 5); // offset +0x14 (8 bytes)
            entry[4] = zeroBuffer[4]; // offset +0x10
            entry[7] = zeroInt;       // offset +0x1C
            entry[8] = zeroInt;       // offset +0x20

            if (zeroBuffer[0] != 0)
            {
                FUN_004daf90(zeroBuffer);
            }
            break; // removed, exit loop
        }

        tail++;
        if (tail >= capacity)
        {
            tail = 0;
        }
    }
    return;
}