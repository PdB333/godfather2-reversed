// FUNC_NAME: SpatialHashManager::addObject
uint __thiscall SpatialHashManager::addObject(int thisPtr, int object) {
    // thisPtr: pointer to SpatialHashManager instance
    // object: pointer to an entity/object to add (must have a key at +0xa0, +0xa4, +0xa8, +0xac)
    // Returns index of the bucket (cell) the object was added to, or 0xFFFFFFFF on failure.

    if (object == 0) {
        return 0xFFFFFFFF;
    }

    uint bucketIndex = 0;
    uint bucketCount = *(uint *)(thisPtr + 0x3C); // number of buckets in the hash
    if (bucketCount != 0) {
        int **bucketArray = *(int ***)(thisPtr + 0x38); // array of bucket pointers
        do {
            int *bucket = *bucketArray;
            int *bucketObject = *(int **)(bucket + 8); // pointer to the dynamic data array (actually from offset +8? Wait, bucket structure: [0] vtable, [1] ?, [2] dataArrayPtr, [3] count, [4] capacity)
            // Actually, looking at the code: iVar5 = *piVar6; then iVar5 = *piVar6 (bucket pointer)
            // Then iVar2 = **(int **)(iVar5 + 8); // iVar5 is bucket, iVar5+8 is field at offset 8? But earlier bucket is at +0x3c? Let's trace:
            // piVar6 = *(int **)(param_1 + 0x38); -> array of bucket pointers
            // iVar5 = *piVar6; -> bucket pointer
            // iVar2 = **(int **)(iVar5 + 8); -> iVar5+8 is offset 8 in bucket? Actually the code: iVar2 = **(int **)(iVar5 + 8);
            // But the bucket structure from allocation: puVar3[0]=vtable, puVar3[1]=0, puVar3[2]=dataArrayPtr, puVar3[3]=count, puVar3[4]=capacity.
            // So offset 0 is vtable, 4 is field1, 8 is dataArrayPtr, 12 is count, 16 is capacity.
            // Then iVar5+8 is the dataArrayPtr, which is a pointer to an array of integers (object pointers). 
            // Then ** dereferences the first element of that array, which is an object pointer (param_2 candidate).
            // This is a bit weird because they compare with param_2's fields, but it's the first object in the bucket that is used for key comparison.
            // Maybe the bucket's "representative" is the first object? Actually the code checks if the first object in the bucket's data array matches the key.
            // So the bucket's key is derived from the first object stored in it.
            if (*(int *)(iVar5 + 0xC) != 0) { // bucket's count > 0
                int *firstObject = *(int **)(iVar5 + 8); // pointer to data array
                if (firstObject != 0) {
                    // Compare the key (4 uint at offsets 0xa0,0xa4,0xa8,0xac)
                    if (*(int *)(object + 0xA0) == *(int *)(firstObject + 0xA0) &&
                        *(int *)(object + 0xA4) == *(int *)(firstObject + 0xA4) &&
                        *(int *)(object + 0xA8) == *(int *)(firstObject + 0xA8) &&
                        *(int *)(object + 0xAC) == *(int *)(firstObject + 0xAC)) {
                        // Found matching bucket
                        FUN_00822a60(object); // possibly remove from old bucket/cleanup
                        FUN_008228a0(iVar5); // maybe add to this bucket? Or update internal structures
                        return bucketIndex;
                    }
                }
            }
            bucketIndex++;
            bucketArray++;
        } while (bucketIndex < bucketCount);
    }

    // No existing bucket found, create a new one
    // Allocate a new bucket node (0x14 bytes = 5 * 4)
    int *newBucket = (int *)FUN_009c8e50(0x14);
    if (newBucket == 0) {
        newBucket = 0; // allocation failed
    } else {
        newBucket[0] = (int)&PTR_FUN_00d73400; // vtable pointer for bucket class
        newBucket[1] = 0; // unknown field
        int *dataArray = (int *)FUN_009c8e80(0x40); // allocate initial data array (16 ints = 64 bytes? Actually 0x40 = 64 bytes, 16 ints)
        newBucket[2] = (int)dataArray; // pointer to data array
        newBucket[3] = 0; // count of items in bucket
        newBucket[4] = 0x10; // capacity of data array (16 items)
    }

    // Resize main bucket array if needed
    int currentCapacity = *(int *)(thisPtr + 0x40);
    if (bucketCount == currentCapacity) {
        int newCapacity;
        if (currentCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = currentCapacity * 2;
        }
        FUN_00821e00(newCapacity); // resize the bucket array (likely realloc and copy)
    }

    // Add new bucket to the array
    int *bucketArrayPtr = *(int **)(thisPtr + 0x38);
    int *newBucketSlot = bucketArrayPtr + bucketCount * 4; // offset to next empty slot
    *(int *)(thisPtr + 0x3C) = bucketCount + 1; // increment count
    if (newBucketSlot != 0) {
        *newBucketSlot = (int)newBucket;
    }

    // Add the object to the new bucket's data array
    int dataArrayCapacity = newBucket[4];
    int dataArrayCount = newBucket[3];
    if (dataArrayCount == dataArrayCapacity) {
        int newCapacity;
        if (dataArrayCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = dataArrayCapacity * 2;
        }
        FUN_00821e80(newCapacity); // resize the data array
    }
    int *dataArrayPtr = (int *)newBucket[2];
    int *objectSlot = dataArrayPtr + dataArrayCount * 4;
    newBucket[3] = dataArrayCount + 1; // increment count
    if (objectSlot != 0) {
        *objectSlot = object;
    }

    // Sort the data array if more than one item
    if (newBucket[3] > 1) {
        _qsort((void *)newBucket[2], newBucket[3], 4, (_PtFuncCompare *)&LAB_00833690);
    }

    // Additional bookkeeping
    FUN_008208c0(); // possibly update some global counter or event (unrelated to this insertion?)

    int anotherArrayCount = *(int *)(thisPtr + 0x2C);
    int anotherArrayCapacity = *(int *)(thisPtr + 0x28);
    if (anotherArrayCount == anotherArrayCapacity) {
        int newCap;
        if (anotherArrayCapacity == 0) {
            newCap = 1;
        } else {
            newCap = anotherArrayCapacity * 2;
        }
        FUN_00821d50(newCap); // resize another array (maybe for debug or reverse lookup)
    }

    int anotherArrayIndex = *(int *)(thisPtr + 0x28);
    *(int *)(thisPtr + 0x28) = anotherArrayIndex + 1; // increment count
    if (anotherArrayIndex * 0x130 + *(int *)(thisPtr + 0x24) != 0) {
        // The code does: FUN_00820d40(local_140); where local_140 is a 316-byte buffer.
        // This likely copies or initializes something for the new entry.
        // We can't know exactly, but preserve the call.
        char local_140[316];
        FUN_00820d40(local_140);
    }

    // Possibly finalize
    int finalBucketCount = *(int *)(thisPtr + 0x3C);
    FUN_00820940(); // some post-insert cleanup or notification
    return finalBucketCount - 1; // return the index of the newly created bucket (zero-based)
}