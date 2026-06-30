// FUNC_NAME: InternalArray::removeTrailingZeroElements
void InternalArray::removeTrailingZeroElements() {
    int count = this->count;          // +0x00: number of active elements
    if (count > 0) {
        do {
            // Check from the end: stop if last element is non-zero
            if (this->data[count - 1] != 0) break;
            count--;
            this->count = count;
        } while (count > 0);
        count = this->count;          // re-read after loop
    }
    if (count == 0) {
        this->writeIndex = 0;         // +0x08: reset write position when array is empty
    }
}