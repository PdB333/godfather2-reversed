// FUNC_NAME: DynamicArray::ensureCapacity
void DynamicArray::ensureCapacity(uint newCapacity)
{
    int* oldArray;
    uint copyCount;
    int* newArray;
    
    if (this->mCapacity < newCapacity) {
        // Allocate new array buffer
        newArray = (int*)allocateMemory(newCapacity * 4);
        
        if (this->mArray != 0) {
            copyCount = 0;
            // Copy existing elements to new array
            if (this->mCount != 0) {
                do {
                    if (newArray != (int*)0x0) {
                        newArray[copyCount] = this->mArray[copyCount];
                    }
                    copyCount++;
                } while (copyCount < this->mCount);
            }
            // Free old array
            deallocateMemory(this->mArray);
        }
        // Update pointers and capacity
        this->mArray = newArray;
        this->mCapacity = newCapacity;
    }
}