// FUNC_NAME: SlotArray::trimTrailingZeros
// Function address: 0x00665b10
// Removes trailing zero entries from an array of ints, updating count and clearing a flag when empty.
// Structure offsets:
//   +0x00 count (int) - number of used elements
//   +0x08 flag (int) - set to 0 when array becomes empty after trimming
//   +0x0C array (int*) - pointer to array of ints
void SlotArray::trimTrailingZeros() {
    int count = this->count;
    if (count > 0) {
        do {
            // Check the last element (index count-1); if non-zero, stop trimming
            if (this->array[count - 1] != 0) {
                break;
            }
            count--;
            this->count = count;
        } while (count > 0);
        count = this->count; // reload count after possible decrement
    }
    if (count == 0) {
        this->flag = 0; // mark as empty
    }
}