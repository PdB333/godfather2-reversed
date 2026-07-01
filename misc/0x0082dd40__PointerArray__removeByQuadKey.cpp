// FUNC_NAME: PointerArray::removeByQuadKey
// Function address: 0x0082dd40
// Removes an element from a dynamic array of pointers by matching a quad-key (4 ints).
// The array is stored as: this+0x8 -> pointer to array of pointers, this+0xc -> count.
// Each element at offsets +0x1c, +0x20, +0x24, +0x28 holds the quad-key to compare.
// Returns pointer to the removed element, or nullptr if not found.

int* __thiscall PointerArray::removeByQuadKey(int* key) // this is param_1, key is param_2
{
    uint count = *(uint*)(this + 0xc);          // number of elements
    uint index = 0;

    if (count != 0) {
        int** array = *(int***)(this + 0x8);     // pointer to array of pointers
        do {
            int* element = *array;               // current element pointer
            // Compare quad-key: offsets 0x1c, 0x20, 0x24, 0x28
            if (element != nullptr &&
                *(int*)(element + 0x1c) == key[0] &&
                *(int*)(element + 0x20) == key[1] &&
                *(int*)(element + 0x24) == key[2] &&
                *(int*)(element + 0x28) == key[3])
            {
                // Shift remaining elements left if not the last
                if (index < count - 1) {
                    do {
                        *(int**)(*(int*)(this + 0x8) + index * 4) =
                            *(int**)(*(int*)(this + 0x8) + (index + 1) * 4);
                        index++;
                    } while (index < count - 1);
                }
                *(int*)(this + 0xc) = count - 1;  // decrement count
                return element;                    // return removed element pointer
            }
            index++;
            array++;
        } while (index < count);
    }
    return 0; // not found
}