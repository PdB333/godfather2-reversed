// FUNC_NAME: DynamicArray::insertElement
// Purpose: Insert an element at given index, shifting elements right.  
// Struct layout: [0] pointer to data array, [4] current count, [8] capacity.
// Each element is 8 bytes (two uint32).
// Returns pointer to the newly inserted (empty) element slot.
// @param index (in EDI): insertion index
int* DynamicArray::insertElement( int index )
{
    // ------------------------------------------------------------------
    // Step 1: Expand capacity if current size equals capacity
    // ------------------------------------------------------------------
    int currentCount = this->count;  // +0x04
    int capacity     = this->capacity; // +0x08

    if( currentCount == capacity )
    {
        // Grow: capacity=0 -> 1, else double
        if( capacity == 0 )
            capacity = 1;
        else
            capacity *= 2;

        // Reallocate (expected to update this->data, this->capacity)
        FUN_00444020( capacity );   // reallocate
    }

    // ------------------------------------------------------------------
    // Step 2: Shift elements right to make room at 'index'
    // ------------------------------------------------------------------
    int   countBefore = this->count;
    int*  base        = this->data;  // +0x00

    if( index != countBefore )  // inserting somewhere in the middle
    {
        // Copy the last element one slot to the right to start shift chain
        int* pDest = base + countBefore * 2; // new element slot (two ints)
        if( pDest != nullptr )
        {
            // Copy element from countBefore-1 to slot countBefore
            pDest[0] = pDest[-2];  // first int of element at index countBefore-1
            pDest[1] = pDest[-1];  // second int of element at index countBefore-1
        }

        // Now shift elements from (index .. countBefore-2) to the right
        int slotIdx = countBefore; // start from old size
        while( slotIdx = slotIdx - 1, index < slotIdx )
        {
            int* pSrc  = base + (slotIdx - 1) * 2; // element at slotIdx-1
            int* pDest = base + slotIdx * 2;       // element at slotIdx
            pDest[0] = pSrc[0];
            pDest[1] = pSrc[1];
        }
    }

    // ------------------------------------------------------------------
    // Step 3: Update count and return pointer to vacated slot
    // ------------------------------------------------------------------
    this->count = this->count + 1;

    return base + index * 2;  // pointer to the inserted element (8 bytes)
}