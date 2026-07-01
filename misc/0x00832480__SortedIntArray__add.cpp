// FUNC_NAME: SortedIntArray::add
void __thiscall SortedIntArray::add(SortedIntArray* this, int value)
{
    // This function adds a value to a dynamically-sized sorted array.
    // The array stores ints, and after insertion, the entire array is sorted.
    // Members:
    // +0x08: int* data (pointer to allocated memory)
    // +0x0C: int count (number of elements currently stored)
    // +0x10: int capacity (allocated capacity in elements)

    int currentCapacity = this->capacity;

    // If count equals capacity, need to grow
    if (this->count == currentCapacity) {
        // If capacity is 0, set new capacity to 1; otherwise double it
        int newCapacity = (currentCapacity == 0) ? 1 : (currentCapacity * 2);
        reserve(newCapacity); // FUN_0082b950 – reallocates internal array
    }

    // Insert the new value at the end of the array
    int* nextSlot = this->data + this->count;
    this->count++;
    *nextSlot = value;

    // If more than one element, sort the whole array
    // Comparator at LAB_00833690 is assumed to be a standard ascending integer comparison (a - b)
    if (this->count > 1) {
        qsort(this->data, this->count, sizeof(int), compareInt); // qsort with global comparator
    }
}