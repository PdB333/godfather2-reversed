// FUNC_NAME: HashTable::addObject
// Address: 0x00792d80
// Inserts an object into a hash table bucket, resizing the bucket's array if necessary, and sets a flag on the object to indicate it is owned by the table.

void __thiscall HashTable::addObject(void* this, int param_2) // param_2 = object to insert
{
    int* bucket;
    int bucketIndex;
    int* bucketStruct; // points to a bucket metadata struct
    int tmp; // temporary variable used to hold bucket array pointer

    // If the object's reference count or valid flag at +0x78 is less than 1, do nothing.
    if (*(int*)(param_2 + 0x78) < 1) {
        return;
    }

    // Retrieve the internal bucket array or table reference (via a member function)
    // The decompiler shows this as taking no arguments, but it's likely a member function that uses 'this'.
    tmp = (int) getBucketArray(); // FUN_007914e0

    // Compute the bucket index for this object (hash function)
    // The function is called with the address of 'tmp' – may act on the bucket array pointer.
    bucketIndex = hashFunction(&tmp); // FUN_007923a0
    if ((bucketIndex < 0) ||
        (bucketStruct = (int*)(bucketIndex * 0x10 + 4 + *(int*)(this + 0x20)), bucketStruct == nullptr)) {
        // If invalid index or bucket not found, fall back to an alternate bucket.
        bucketStruct = (int*) getAlternateBucket(&tmp); // FUN_00792d10
    }

    // Bucket structure layout:
    // +0x00: pointer to dynamic array of item pointers
    // +0x04: current number of items (size)
    // +0x08: capacity of the array
    int currentSize = bucketStruct[1];
    int capacity = bucketStruct[2];

    if (currentSize == capacity) {
        // Resize the array: if capacity is 0, start with 1; otherwise double.
        int newCapacity = (capacity == 0) ? 1 : (capacity * 2);
        resizeBucketArray(newCapacity); // FUN_006b1e10
    }

    // Get the address where the object pointer will be stored (end of used portion)
    int* slot = (int*)(*bucketStruct + bucketStruct[1] * 4);
    bucketStruct[1] = bucketStruct[1] + 1; // increase size

    if (slot != nullptr) {
        *slot = param_2; // store the object pointer
    }

    // Mark the object as belonging to the table (e.g., 'inTable' flag)
    *(uint*)(param_2 + 0x5c) |= 0x200000;

    // Notify observers that an object was added
    notifyItemAdded(0); // FUN_00790d30

    // If the object has a child/reference at +0xD8, add it as well
    int child = *(int*)(param_2 + 0xD8);
    if (child != 0) {
        int childIndex = hashFunction(&child); // FUN_007923a0
        if ((childIndex < 0) || (childIndex * 0x10 + 4 + *(int*)(this + 0x2c) == 0)) {
            getAlternateBucket(&child); // FUN_00792d10
        }
        addReference(&param_2); // FUN_006b44a0 – possibly increment refcount or link
    }

    return;
}