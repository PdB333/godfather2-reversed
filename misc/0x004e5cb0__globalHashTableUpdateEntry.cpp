// FUNC_NAME: globalHashTableUpdateEntry
// Function at 0x004e5cb0: Updates properties of an object stored in a global hash table.
// The hash table is accessed via a global pointer at DAT_01223398.
// Hash table structure: base = *(uint**)(DAT_01223398+8)
//   base+0: unknown (maybe count)
//   base+4: pointer to bucket pointer array (uint**)
//   base+8: bucket count (uint)
// Hash node structures: [key, valuePointer, next] (each 12 bytes)
// The object at valuePointer has fields at +0x30, +0x34, +0x38, +0x3C, +0x84, +0x8C, +0x98 (byte).

extern uint DAT_01223398; // Global pointer to hash table manager

void globalHashTableUpdateEntry(uint key, uint* inputData)
{
    // Get hash table base from global
    uint* hashTableBase = *(uint**)(DAT_01223398 + 8);
    uint bucketCount = *(uint*)(hashTableBase + 8);          // number of hash buckets
    uint** bucketArray = *(uint***)(hashTableBase + 4);     // array of bucket head pointers
    uint bucketIndex = key % bucketCount;
    
    uint* node = bucketArray[bucketIndex];
    while (node != 0)
    {
        if (node[0] == key)
        {
            // Node found: node[1] is a pointer to the target object
            uint obj = node[1];
            // Copy 6 input values into the object at known offsets
            *(uint*)(obj + 0x30) = inputData[0];   // first component (e.g., position.x or attribute A)
            *(uint*)(obj + 0x34) = inputData[1];   // second component
            *(uint*)(obj + 0x38) = inputData[2];   // third component
            *(uint*)(obj + 0x3C) = inputData[3];   // fourth component
            *(uint*)(obj + 0x8C) = inputData[4];   // fifth component
            *(uint*)(obj + 0x84) = inputData[5];   // sixth component (note: offset out of order)
            *(byte*)(obj + 0x98) = 1;              // flag set to true (active/initialized)
            return;
        }
        node = (uint*)node[2]; // move to next node in chain
    }
    // Key not found: original code writes to address 0 (uVar5=0) which would cause a crash.
    // This path may never be reached because the caller ensures the key exists.
    // Alternatively, the decompilation may be missing error handling logic.
}