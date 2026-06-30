// FUNC_NAME: SearchableArray::findByID
uint __thiscall SearchableArray::findByID(void *this, int id) {
    // this->itemsArray: pointer to array of pointers to int (IDs) at offset +0x8
    // this->itemCount: number of items in array at offset +0xc
    // this->foundItem: stores pointer to found item at offset +0x20
    uint *currentItemPtr = *(uint **)((char *)this + 8);
    uint *endPtr = currentItemPtr + *(int *)((char *)this + 0xc);

    if (currentItemPtr != endPtr) {
        do {
            int *itemValue = (int *)*currentItemPtr;
            if (*itemValue == id) {
                // Store pointer to found entry
                *(int **)((char *)this + 0x20) = itemValue;
                // Return pointer with low byte set to 1 to indicate success
                return ((uint)itemValue & 0xFFFFFF00) | 1;
            }
            currentItemPtr++;
        } while (currentItemPtr != endPtr);
    }
    // Not found: return aligned end-address with low byte cleared
    return (uint)currentItemPtr & 0xFFFFFF00;
}