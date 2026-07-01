// FUNC_NAME: ObjectList::pushBack
// Function at 0x00791e70 - adds an element (param_2) to a dynamic array pointed by this+0xAC.
// The array descriptor at this+0xAC has 12 bytes: int* array, int size, int capacity.
// After insertion, if certain conditions (this+0x9C != 0 && != 0x48, flags at 0x5C bits 17/18 clear),
// it calls first and second virtual functions of the added object (param_2 is treated as a vtable pointer).

void __thiscall ObjectList::pushBack(int thisPtr, int* element)
{
    // Dynamic array descriptor stored at this+0xAC
    struct DynamicArray {
        int* array;      // +0x00: pointer to element buffer
        int size;        // +0x04: number of elements
        int capacity;    // +0x08: allocated capacity
    };

    DynamicArray* arr = *(DynamicArray**)(thisPtr + 0xAC);

    // Lazy initialization of the descriptor
    if (arr == nullptr) {
        arr = (DynamicArray*)allocateMemory(12); // 3 ints
        if (arr != nullptr) {
            arr->array = nullptr;
            arr->size = 0;
            arr->capacity = 0;
        }
        *(DynamicArray**)(thisPtr + 0xAC) = arr;
    }

    // Grow if full
    if (arr->size == arr->capacity) {
        int newCapacity = (arr->capacity == 0) ? 1 : (arr->capacity * 2);
        growArray(newCapacity); // Likely reallocates array and updates capacity
    }

    // Insert element at the end
    int* slot = arr->array + arr->size;
    arr->size++;
    if (slot != nullptr) {
        *slot = (int)element; // element is stored as a raw pointer
    }

    // Conditional invocation of element's virtual methods (if element is an object)
    int unknownFlagField = *(int*)(thisPtr + 0x9C); // +0x9C: some type/state flag
    int stateFlags = *(int*)(thisPtr + 0x5C);       // +0x5C: bitfield of states

    if (unknownFlagField != 0 && unknownFlagField != 0x48 && ((stateFlags >> 0x11) & 1) == 0) {
        // Call vtable function at index 0
        (**(code (**)(void))element)(thisPtr);
        if (((stateFlags >> 0x12) & 1) == 0) {
            // Call vtable function at index 1
            (**(code (**)(int))(element + 4))(thisPtr);
        }
    }
}