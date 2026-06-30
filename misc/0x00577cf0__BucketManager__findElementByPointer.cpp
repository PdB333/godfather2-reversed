// FUNC_NAME: BucketManager::findElementByPointer
int __thiscall BucketManager::findElementByPointer(void* target)
{
    // +0x70: pointer to bucket table (manages multiple bucket arrays)
    // +0x74: short bucket index (selects which bucket to search)
    
    // Get bucket table base pointer from this+0x70
    int* bucketTable = *(int**)(this + 0x70);
    // Offset into bucket table (+0x40) to get the bucket array address
    int* bucketArray = *(int**)((char*)bucketTable + 0x40); // bucketArray is an array of bucket headers

    short bucketIdx = *(short*)(this + 0x74);
    // Each bucket header is 8 bytes: 4 bytes count, 4 bytes pointer to elements
    int* bucketHeader = (int*)((char*)bucketArray + bucketIdx * 8);

    int count = bucketHeader[0]; // number of elements in this bucket
    if (count != 0)
    {
        int* elements = (int*)bucketHeader[1]; // pointer to array of elements
        // Each element is 12 bytes (3 ints), first int is the ID/pointer we compare
        for (int i = 0; i < count; i++)
        {
            if (elements[0] == (int)target) // compare first field
            {
                return i; // return index within bucket
            }
            elements += 3; // advance by 12 bytes (3 ints)
        }
    }
    return -1; // not found
}