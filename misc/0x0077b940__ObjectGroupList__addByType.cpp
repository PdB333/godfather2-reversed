// FUNC_NAME: ObjectGroupList::addByType
/**
 * Reconstructed C++ for function at 0x0077b940
 * 
 * Adds an element to one of four internal dynamic arrays based on its type field.
 * The element's type field at +0x58 determines which array to use:
 *   - 0 or 1: array at offset +0x04
 *   - 2:       array at offset +0x10
 *   - 3:       array at offset +0x1C
 *   - 4:       array at offset +0x28
 * Each dynamic array has a pointer to elements, a count, and a capacity (12 bytes total).
 * If full, the array is grown (capacity doubled) via growArray().
 */

typedef int Element; // placeholder for the actual object type (likely a class)

// Realloc helper; not shown here, assumed at 0x0077b420
void __thiscall growArray(int newCapacity);

void __thiscall ObjectGroupList::addByType(int thisPtr, Element* element) {
    int* arrayPtr;        // pointer to the dynamic array's pointer
    int* countPtr;        // pointer to the count element
    int* capacityPtr;     // pointer to the capacity element
    int currentCount;
    int currentCapacity;

    // Select the appropriate array slot based on element->type (+0x58)
    int type = *(int*)(element + 0x58); // element->type field at offset 0x58
    switch (type) {
        case 2:
            // Array slot at this+0x10
            arrayPtr = (int*)(thisPtr + 0x10);
            break;
        case 3:
            // Array slot at this+0x1C
            arrayPtr = (int*)(thisPtr + 0x1C);
            break;
        case 4:
            // Array slot at this+0x28
            arrayPtr = (int*)(thisPtr + 0x28);
            break;
        default:
            // Default array slot at this+0x04 (used for types 0,1, and others)
            arrayPtr = (int*)(thisPtr + 0x04);
            break;
    }

    // The three fields: arrayPtr[0] = base pointer, [1] = count, [2] = capacity
    currentCount = arrayPtr[1];
    currentCapacity = arrayPtr[2];

    // Check if array is full
    if (currentCount == currentCapacity) {
        // Grow the array: if capacity is 0, set to 1; otherwise double it
        int newCapacity;
        if (currentCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = currentCapacity * 2;
        }
        growArray(newCapacity); // called with new capacity
    }

    // Write element pointer to the next free slot
    int* slot = (int*)(*arrayPtr + arrayPtr[1] * 4); // base + count*4
    arrayPtr[1] += 1; // increment count
    if (slot != nullptr) {
        *slot = (int)element; // store element pointer
    }
}