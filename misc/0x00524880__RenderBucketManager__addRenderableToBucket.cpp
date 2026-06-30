// FUNC_NAME: RenderBucketManager::addRenderableToBucket
void RenderBucketManager::addRenderable(void* renderableObj, int bucketIndex)
{
    int bucketItemCount = gBucketItemCount; // DAT_01194a9c
    // Get the bucket struct for this index
    void* bucket = *(void**)(gBucketArray + bucketIndex * 4); // &DAT_01197d10 + param_2*4
    int currentFront = *(int*)((char*)bucket + 0x458); // +0x458: pointer to front item or priority key
    if (currentFront == 0) {
        currentFront = 0;
    } else {
        currentFront = currentFront - 4; // adjust? maybe a pointer to previous item
    }

    int objKey = *(int*)(*(int*)((char*)renderableObj + 0x10) + 0x5c); // +0x10: pointer to render data, +0x5c: sort key
    bool canInsert = (objKey == currentFront) ||
                     ( (*(unsigned char*)((char*)objKey + 0xac) & 8) != 0 &&
                       *(char*)((char*)bucket + 0x451) != 0 );
    if (canInsert && bucketItemCount < 0x400) {
        int result = checkInsertion(objKey); // FUN_005247a0 – returns non-zero if allocation ok
        if (result != 0) {
            int itemIndex = bucketItemCount * 0xc; // each item is 12 bytes
            // Store new item in the global pool
            *(void**)(gBucketItemPool + itemIndex) = *(void**)((char*)renderableObj + 0x10); // +0x10: pointer to render data
            *(void**)(gBucketItemPool + itemIndex + 4) = *(void**)((char*)renderableObj + 0x0c); // +0x0c: maybe transform or position
            gBucketItemCount = bucketItemCount + 1;
            // The third field is a pointer to the bucket's current front, then update bucket front
            *(void**)(gBucketItemPool + itemIndex + 8) = *(void**)((char*)result + 0x14); // store old front
            *(void**)((char*)result + 0x14) = (void*)(gBucketItemPool + itemIndex); // bucket now points to new item
        }
    }
}