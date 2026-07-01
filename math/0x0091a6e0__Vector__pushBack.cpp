// FUNC_NAME: Vector::pushBack
// Function at 0x0091a6e0: Adds an element to the dynamic array (vector). 
// Structure offsets: 
//   +0x4c: data pointer (int*)
//   +0x50: size (int)
//   +0x54: capacity (int)
void __thiscall Vector::pushBack(int thisPtr, int element)
{
    int capacity = *(int*)(thisPtr + 0x54);
    int size = *(int*)(thisPtr + 0x50);
    
    if (size == capacity) {
        // Need to grow the array
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // Reallocate to new capacity
        FUN_00917990(newCapacity); // likely reallocate(thisPtr, newCapacity)
    }
    
    // Write element at current end
    int* dataPtr = *(int**)(thisPtr + 0x4c);
    if (dataPtr != nullptr) {
        dataPtr[*(int*)(thisPtr + 0x50)] = element;
    }
    // Increment size
    *(int*)(thisPtr + 0x50) = *(int*)(thisPtr + 0x50) + 1;
}