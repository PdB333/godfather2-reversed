//FUNC_NAME: EARSArray::insert
// Address: 0x006b0e40
// Role: Insert an element at a given index in a dynamic array of 8-byte elements.
// The array structure: +0x00 = data pointer, +0x04 = size, +0x08 = capacity.
// Elements are 8 bytes each (two 32-bit values).

class EARSArray {
public:
    uint32_t* m_pData;      // +0x00
    uint32_t  m_size;       // +0x04
    uint32_t  m_capacity;   // +0x08

    // Insert a new element at the given index. Returns pointer to the inserted slot.
    // If index == m_size, appends at the end.
    // If index < m_size, shifts elements to the right.
    // Automatically grows capacity if full (doubles, or sets to 1 if zero).
    uint32_t* __thiscall insert(uint32_t index) {
        uint32_t* pSlot;
        uint32_t i;

        // Check if we need to grow the array
        if (m_size == m_capacity) {
            uint32_t newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
            resizeArray(newCapacity);  // FUN_006afc10 - reallocate to new capacity
        }

        // If appending at the end, just increment size and return pointer to new slot
        if (index == m_size) {
            m_size++;
            return &m_pData[index * 2];  // each element is 2 uint32_t (8 bytes)
        }

        // Otherwise, we need to shift elements to make room.
        // First, get pointer to the slot where the new element will go.
        pSlot = &m_pData[index * 2];

        // If the slot is not null (should always be valid), copy the previous element into it?
        // Actually, this code copies the element that was at index-1 into the current slot?
        // Wait, let's re-read the decompiled code:
        // *puVar1 = puVar1[-2];  // copy previous element's first uint32
        // puVar1[1] = puVar1[-1]; // copy previous element's second uint32
        // This seems to be shifting the element at index-1 into the slot at index?
        // But that would overwrite the slot we want to insert into.
        // Actually, the loop below shifts elements from the end down to index+1.
        // The code before the loop appears to handle the case where index < size:
        // It copies the element at index-1 into the current slot (which is the slot we want to insert into).
        // That would be wrong. Let's re-analyze.

        // Re-reading the decompiled code carefully:
        // uVar2 = param_1[1];  // size
        // puVar1 = (undefined4 *)(*param_1 + uVar2 * 8);  // pointer to element at index = size? No, uVar2 is size, so that's past the end.
        // Actually, the code does:
        // puVar1 = (undefined4 *)(*param_1 + uVar2 * 8);
        // Then if (param_2 == uVar2) { ... } else { if (puVar1 != 0) { *puVar1 = puVar1[-2]; puVar1[1] = puVar1[-1]; } }
        // That's weird: puVar1 points to the element at index = size (one past the end). Then it copies the element at index-2 and index-1 into that slot? That would be copying from the previous element? No, puVar1[-2] and puVar1[-1] are the two uint32 of the element at index-1 (since each element is 8 bytes, puVar1[-2] is the first uint32 of the previous element, puVar1[-1] is the second uint32). So it copies the last element (at index size-1) into the slot at index size (which is beyond the array). That doesn't make sense.

        // Actually, I think the decompiler might have misordered the code. Let's look at the original assembly or think about the algorithm.
        // The typical insertion algorithm for a dynamic array:
        // 1. Ensure capacity.
        // 2. If index == size, just append.
        // 3. Else, shift elements from size-1 down to index to the right by one position.
        // 4. Then insert at index.
        // The decompiled code seems to do:
        // - First, it gets a pointer to the element at the current size (past the end).
        // - If index == size, it just increments size and returns that pointer.
        // - Else, it copies the element at index-1 into that past-the-end slot? That would be wrong.
        // Wait, maybe the pointer calculation is different: *param_1 + uVar2 * 8 gives the address of the element at index = size? That's correct.
        // Then it does: *puVar1 = puVar1[-2]; puVar1[1] = puVar1[-1]; This copies the element at index-1 into the slot at index size. That would be extending the array by one element and copying the last element to the new slot. Then later the loop shifts elements from size-1 down to index+1 to the right, effectively moving the last element to the new slot and then shifting others. That is a valid algorithm: first duplicate the last element to the new slot (which is beyond the current size), then shift elements from size-1 down to index+1 to the right by one, overwriting the duplicate? Actually, it would overwrite the duplicate? Let's simulate:
        // Initial: [A, B, C, D] size=4, capacity=4, insert at index=1.
        // Step: copy D to slot 4 (new slot): [A, B, C, D, D] (size still 4, but we have a 5th slot? Actually capacity might have been increased first. Let's assume capacity is enough.)
        // Then loop: for i from size-1 down to index+1: shift element at i-1 to i.
        // i=3: shift C to slot 3: [A, B, C, C, D]
        // i=2: shift B to slot 2: [A, B, B, C, D]
        // Then after loop, we return pointer to slot at index (1) and the element at index 1 is still B? But we haven't inserted the new element yet. The function returns a pointer to the slot, and the caller is expected to write the new element there. So the slot at index 1 is now occupied by B (from the shift). That's correct: after shifting, the slot at index is free (the original B moved to index 2). So the algorithm works: first duplicate the last element to the new slot (which is beyond the current size), then shift elements from size-1 down to index+1 to the right, which effectively moves the last element into the new slot and shifts others. The duplicate at the end is overwritten by the shift of the last element? Actually, the last element (D) is moved to slot 4 (new slot) first. Then when shifting, the element at index size-1 (which is D) is shifted to slot size? No, the loop shifts from size-1 down to index+1, so it shifts element at index size-2 to index size-1, etc. So the duplicate at slot size is not overwritten; it becomes the new last element. That's correct: the array grows by one, and the last element is duplicated? Wait, that would duplicate the last element. Actually, the algorithm should shift all elements from index to size-1 to the right, not duplicate the last. The typical algorithm: for i from size-1 down to index: array[i+1] = array[i]; then array[index] = new. That shifts all elements from index to size-1 to the right. The decompiled code seems to do: first copy array[size-1] to array[size] (duplicate last), then shift from size-2 down to index: array[i+1] = array[i]. That results in the last element being duplicated? Let's test: size=4, index=1. After first copy: [A, B, C, D, D]. Then shift: i=3: array[4] = array[3]? Actually, the loop goes from size-1 down to index+1? The decompiled loop: while (uVar2 = uVar2 - 1, param_2 < uVar2) { ... } where uVar2 starts as size? Let's see: uVar2 = param_1[1]; then while (uVar2 = uVar2 - 1, param_2 < uVar2) { ... }. So it decrements uVar2 first, then checks if index < uVar2. So uVar2 goes from size-1 down to index+1? Actually, initial uVar2 = size. Then first iteration: uVar2 becomes size-1, check if index < size-1. If yes, then shift element at uVar2-1 to uVar2? The code inside: puVar1 = (undefined4 *)(*param_1 + uVar2 * 8); *puVar1 = *(undefined4 *)(*param_1 + -8 + uVar2 * 8); puVar1[1] = puVar1[-1]; So it copies element at uVar2-1 to uVar2. So it shifts element at uVar2-1 to uVar2. So the loop shifts elements from size-1 down to index+1 to the right by one. That means the element at index+1 gets the element at index, etc. So after the loop, the element at index+1 is the original element at index, and the element at index is still the original? Actually, the loop starts from the end: first iteration shifts element at size-2 to size-1, then size-3 to size-2, etc., until it shifts element at index to index+1. So the element at index is not overwritten yet. Then after the loop, the function returns the pointer to the slot at index, and the caller writes the new element there. So the algorithm is correct: it shifts all elements from index to size-1 to the right by one, but it does so by first copying the last element to a new slot (size) and then shifting the rest. That's a common pattern to avoid overwriting. So the initial copy of the last element to the new slot is necessary to free up the last slot for the shift. So the algorithm is:
        // 1. Ensure capacity.
        // 2. If index == size, just append.
        // 3. Else, copy the last element (at size-1) to the new slot at size (which is beyond current size, but capacity allows).
        // 4. Then shift elements from size-2 down to index to the right by one (i.e., for i from size-1 down to index+1: array[i] = array[i-1]).
        // 5. Return pointer to slot at index.
        // That matches the decompiled code.

        // So we'll implement that.

        // Get pointer to the new slot at the end (size)
        uint32_t* pNewSlot = &m_pData[m_size * 2];  // element at index = size

        // Copy the last element (at index size-1) into the new slot
        pNewSlot[0] = pNewSlot[-2];  // copy first uint32 of last element
        pNewSlot[1] = pNewSlot[-1];  // copy second uint32

        // Now shift elements from size-1 down to index+1 to the right
        uint32_t i = m_size;
        while (i--, index < i) {
            uint32_t* pDest = &m_pData[i * 2];
            uint32_t* pSrc = &m_pData[(i - 1) * 2];
            pDest[0] = pSrc[0];
            pDest[1] = pSrc[1];
        }

        // Increment size
        m_size++;

        // Return pointer to the slot at the insertion index
        return &m_pData[index * 2];
    }

private:
    void resizeArray(uint32_t newCapacity);  // FUN_006afc10 - external function
};