// FUNC_NAME: ObjectBucketList::updateActiveBuckets
void ObjectBucketList::updateActiveBuckets(void)
{
    // This function traverses a linked list of buckets (each holding an array of entries)
    // and processes entries based on their type and a flag at target+5.
    // - Bucket nodes: offset+0x07: byte with count exponent (1<<exp entries), offset+0x10: array, offset+0x18: next
    // - Entry struct (20 bytes): +0 type, +4* target (pointer to object), +8 value
    // - Object at target has a byte at offset+5 that is used as a "valid" flag.

    ObjectBucket* bucket = reinterpret_cast<ObjectBucket*>(in_EAX);
    if (bucket == nullptr) {
        return;
    }

    do {
        // Number of entries in this bucket = 1 << (byte at offset 0x07 masked to lower 5 bits)
        int entryCount = 1 << (static_cast<unsigned char>(bucket->entryCountShift) & 0x1F);
        if (entryCount != 0) {
            int entryOffset = entryCount * 20; // size of each entry = 0x14 (20 bytes)
            do {
                entryOffset -= 20; // move to previous entry
                ObjectBucketEntry* entry = reinterpret_cast<ObjectBucketEntry*>(bucket->entries + entryOffset);
                --entryCount;

                int entryType = entry->type;
                int* target = entry->target; // pointer to some object

                if (entryType == 4) {
                    // Set bit 0 at target+5 (mark as "active")
                    *reinterpret_cast<unsigned char*>(target + 1) |= 1; // target+5 (since target is int*, +1 is +4 bytes, then +1 byte = +5)
                }

                // For types > 3: if the flag at target+5 is NOT set, reset the entry
                if ((entryType > 3) && ((*reinterpret_cast<unsigned char*>(target + 1) & 1) == 0)) {
                    entry->value = 0;
                    entry->type = -1; // invalid/empty
                }
            } while (entryCount != 0);
        }

        bucket = reinterpret_cast<ObjectBucket*>(bucket->next);
    } while (bucket != nullptr);
}