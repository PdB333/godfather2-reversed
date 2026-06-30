// FUNC_NAME: UpdateManager::runOnActiveObjects
// Function at 0x00482a50: Iterates over flagged objects and calls a processing function for each active one.
// Offsets: this+0x0C = count (short), this+0x20C = pointer to flags byte array
// objectArray+4 = start of pointer array (likely embedded after vtable or size field)

extern void processObject(void* context, void* object, void* extraContext); // FUN_00408bf0

void UpdateManager::runOnActiveObjects(void* objectArray, void* context, void* extraContext)
{
    uint index = 0;
    short count = *(short*)((char*)this + 0x0C); // Number of tracked objects

    if (count != 0) {
        do {
            // Flags array: each byte has bit 1 (0x02) indicating active
            byte* flags = *(byte**)((char*)this + 0x20C);
            if ((flags[index] & 2) != 0) {
                // Object pointer stored in array at offset 4 (skip vtable/size field)
                void* obj = *(void**)((char*)objectArray + 4 + index * 4);
                processObject(context, obj, extraContext);
            }
            index++;
        } while (index < (uint)count);
    }
}