// FUNC_NAME: SomeCollection::findFirstIndex
int __thiscall SomeCollection::findFirstIndex(void (*callback)(uint32_t, uint32_t, uint32_t param_2), uint32_t param_2)
{
    BucketArray* bucketArray = *(BucketArray**)(this + 0x30); // +0x30: pointer to bucket array structure
    Element* currentElement;
    uint32_t currentBucket;
    int index = 0;

    resetIterator(); // FUN_00573aa0 - initializes iteration state

    if (bucketArray != nullptr) {
        // Iterate over all elements in all buckets
        while (true) {
            while (true) {
                // Evaluate the callback on the current element's data fields (offset 0x00 and 0x04)
                if ((*callback)(currentElement->field0, currentElement->field1, param_2) & 1) {
                    return index;
                }
                // Move to next element in the same bucket's linked list (next pointer at +0x0C)
                currentElement = currentElement->next;
                index++;
                if (bucketArray->buckets == nullptr) break;
                if (currentElement == nullptr) {
                    // Current bucket exhausted, find next non-empty bucket
                    do {
                        if (bucketArray->count <= currentBucket) goto noMoreElements; // overflow check
                        currentElement = bucketArray->buckets[currentBucket]; // get head of next bucket
                        currentBucket++;
                    } while (currentElement == nullptr);
                }
            }
    noMoreElements:
            // If we've processed all buckets but currentElement is null, we're done
            if (currentElement == nullptr) break;
        }
    }
    return -1;
}