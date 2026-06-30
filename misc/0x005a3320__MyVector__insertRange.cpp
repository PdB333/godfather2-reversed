// FUNC_NAME: MyVector::insertRange
void MyVector::insertRange(int *this, int **posPtr, int **firstPtr, int **lastPtr) {
    int count = (*lastPtr - *firstPtr) / sizeof(int);
    ASSERT(count >= 0);

    if (count > 0) {
        int *insertPos = *posPtr; // insertion point (pointer to element in vector)
        int newSize = this->size + count;

        if (this->capacity <= newSize) {
            int newCapacity = (int)((float)this->capacity * kGrowthFactor);
            if (newCapacity < newSize) {
                newCapacity = newSize;
            }
            int *oldData = this->data;
            FUN_005a3620(newCapacity); // reallocate (updates this->data and this->capacity)
            // adjust insertPos relative to new buffer
            insertPos = this->data + (insertPos - oldData);
        }

        int *endOfOld = this->data + this->size;
        if (insertPos == endOfOld) {
            // appending at end
            FUN_005a3780(*firstPtr); // copy-construct element from source
        } else {
            // shift existing elements to make room
            FUN_005a37d0(insertPos, endOfOld);
            FUN_005a3780(*firstPtr, insertPos); // copy-construct into opened slot
        }

        int *newEnd = this->data + newSize; // one past last element after insert
        if (newEnd != *lastPtr) {
            // The last element (originally at *lastPtr) may have been moved? Actually this seems to handle destruction of the element that was overwritten? The logic decrements ref count.
            int *lastElem = (int *)*newEnd;
            if (lastElem != nullptr) {
                (*lastElem)--;
                if (*(int *)*lastElem == 0) {
                    // free the reference-counted object
                    FUN_005a1b40();
                    (*gFreeFunc)(*lastElem, 0x30);
                }
            }
            *newEnd = 0;
        }

        this->size = newSize;
    }
}