// FUNC_NAME: sortThreeElements
// Function address: 0x0081ae50
// Sorts three elements (each 16 bytes) using a comparator function.
// This is an inline bubble sort for three items, swapping if comparator returns non-zero.
void sortThreeElements(void* element1, void* element2, void* element3, bool (*comparator)(void*, void*))
{
    // Compare and swap element1 and element2
    if (comparator(element2, element1)) {
        // Swap 16-byte elements
        uint64_t temp0 = *(uint64_t*)element1;
        uint32_t temp1 = *(uint32_t*)((char*)element1 + 8);
        // Copy element2 to element1
        *(uint64_t*)element1 = *(uint64_t*)element2;
        *(uint32_t*)((char*)element1 + 8) = *(uint32_t*)((char*)element2 + 8);
        // Copy temp to element2
        *(uint64_t*)element2 = temp0;
        *(uint32_t*)((char*)element2 + 8) = temp1;
    }

    // Compare and swap element2 and element3
    if (comparator(element3, element2)) {
        uint64_t temp0 = *(uint64_t*)element2;
        uint32_t temp1 = *(uint32_t*)((char*)element2 + 8);
        *(uint64_t*)element2 = *(uint64_t*)element3;
        *(uint32_t*)((char*)element2 + 8) = *(uint32_t*)((char*)element3 + 8);
        *(uint64_t*)element3 = temp0;
        *(uint32_t*)((char*)element3 + 8) = temp1;
    }

    // Final compare and swap for element1 and element2 to ensure full ordering
    if (comparator(element2, element1)) {
        uint64_t temp0 = *(uint64_t*)element1;
        uint32_t temp1 = *(uint32_t*)((char*)element1 + 8);
        *(uint64_t*)element1 = *(uint64_t*)element2;
        *(uint32_t*)((char*)element1 + 8) = *(uint32_t*)((char*)element2 + 8);
        *(uint64_t*)element2 = temp0;
        *(uint32_t*)((char*)element2 + 8) = temp1;
    }
}