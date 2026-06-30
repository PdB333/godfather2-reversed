// FUNC_NAME: ObjectList::packObjectsForType
void __thiscall ObjectList::packObjectsForType(ObjectList* this, int typeID, int* outBuffer)
{
    TypeMaskPair* table = *(TypeMaskPair**)((char*)this + 0x20);
    uint32_t mask = 0;

    // Find the bitmask for the given typeID in the type-mask table
    while (true) {
        if (table->typeID == typeID || table->typeID == 0) {
            mask = table->bitmask;
        }
        table++;
        if (mask != 0) break;
    }

    ObjectEntry* entries = *(ObjectEntry**)((char*)this + 0x10);
    uint32_t entryCount = *(uint32_t*)((char*)this + 0x14);
    int count = 0;

    // Output buffer starts after the count integer
    char* outPtr = (char*)(outBuffer + 1);

    if (entryCount != 0) {
        for (uint32_t i = 0; i < entryCount; i++) {
            ObjectEntry* entry = &entries[i];

            // Read entry fields
            int id = entry->field0;
            int uid = entry->field1;
            int x = entry->field2;
            int y = entry->field3;
            int z = entry->field4;
            int w = entry->field5;
            ObjectData* data = entry->data;

            // Check if this object matches the type mask and visibility flags
            if ((data->bitmask & mask) != 0 &&
                ((data->flags & 1) != 0 || (*(uint32_t*)((char*)this + 0x1c) & 1) != 0)) {

                count++;
                // Copy the entry fields (6 ints)
                *(int*)outPtr = id; outPtr += 4;
                *(int*)outPtr = uid; outPtr += 4;
                *(int*)outPtr = x; outPtr += 4;
                *(int*)outPtr = y; outPtr += 4;
                *(int*)outPtr = z; outPtr += 4;
                *(int*)outPtr = w; outPtr += 4;

                // Copy the data header (size, flags)
                size_t dataSize = data->dataSize;
                uint32_t dataFlags = data->flags;
                // There is a 4-byte gap here (outPtr advances 8 bytes but memcpy uses offset +36)
                // We keep the original layout: skip to offset 9*4=36 for the variable data.
                int* intPtr = (int*)outPtr;
                intPtr[0] = (int)dataSize;  // +24 from start of packed obj
                intPtr[1] = (int)dataFlags; // +28
                // gap at bytes 32-35 (intPtr[2]) is uninitialized
                // Variable data starts at byte 36 (intPtr+9)
                _memcpy(intPtr + 9, (char*)(data + 3), dataSize); // data+3 is start of payload
                outPtr = (char*)(intPtr) + ((dataSize + 0x27) & 0xFFFFFFFC);
            }
        }
        *outBuffer = count;
        return;
    }
    *outBuffer = 0;
}