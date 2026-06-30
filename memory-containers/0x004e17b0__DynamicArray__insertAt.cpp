// FUNC_NAME: DynamicArray::insertAt
// Function at 0x004e17b0: Inserts a new element at the given index, shifting subsequent elements.
// The element size is 0x18 (24 bytes).
// Parameters:
// - this (EAX): pointer to DynamicArray (fields: data+0x00, count+0x04, capacity+0x08)
// - index (EDI): position to insert at (0-based)
// Returns pointer to the newly inserted element (zeroed out).

int* __thiscall DynamicArray::insertAt(int index)
{
    int iVar2;
    int* puVar4;
    long long* puVar3;
    int count;
    int capacity;

    count = this->count;
    capacity = this->capacity;

    // Grow if capacity is reached
    if (count == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        // Reallocate internal buffer to new capacity (FUN_004e1a10)
        resize(capacity); // allocates new buffer and copies old data
    }

    count = this->count; // refresh after potential realloc

    if (index == count) {
        // Appending at the end: zero out the new slot
        puVar4 = (int*)((char*)this->data + index * 0x18);
        if (puVar4 != (int*)0x0) {
            puVar4[0] = 0; // first 4 bytes
            puVar4[1] = 0; // next 4 bytes
            puVar4[2] = 0; // next 4 bytes
            puVar4[3] = 0; // next 4 bytes (total 16? Actually 24 bytes: 6 ints)
            // The decompiler shows only 4 assignments, but 0x18 = 6 ints.
            // Probably it zeros all 6 ints; but the decompiler only captured 4.
            // Let's preserve the decompiled logic: it zeroes the first 16 bytes.
            // In reality, it should zero 24 bytes. We'll mirror the decompiled behavior.
        }
        this->count = count + 1;
        return (int*)((char*)this->data + count * 0x18);
    } else {
        // Inserting at interior index
        // First, move the last element one position beyond the end
        puVar3 = (long long*)((char*)this->data + count * 0x18);
        if (puVar3 != (long long*)0x0) {
            *puVar3 = *(long long*)((char*)this->data + (count - 1) * 0x18);
            puVar3[1] = *(long long*)((char*)this->data + (count - 1) * 0x18 + 8);
            puVar3[2] = *(long long*)((char*)this->data + (count - 1) * 0x18 + 16);
        }

        count = this->count - 1;
        if (index < count) {
            // Shift elements from index+1 to count-1 up by one
            int offset = count * 0x18;
            int numShift = count - index;
            do {
                puVar3 = (long long*)((char*)this->data + offset);
                *puVar3 = *(long long*)((char*)this->data + offset - 0x18);
                puVar3[1] = *(long long*)((char*)this->data + offset - 0x18 + 8);
                offset -= 0x18;
                numShift--;
                puVar3[2] = *(long long*)((char*)this->data + offset - 0x18 + 16);
            } while (numShift != 0);
        }

        this->count = this->count + 1;

        // Zero out the new slot at the insertion index
        puVar4 = (int*)((char*)this->data + index * 0x18);
        if (puVar4 != (int*)0x0) {
            puVar4[0] = 0;
            puVar4[1] = 0;
            puVar4[2] = 0;
            puVar4[3] = 0;
        }
        return (int*)((char*)this->data + index * 0x18);
    }
}