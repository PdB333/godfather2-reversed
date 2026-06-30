// FUNC_NAME: IntList::contains
// Function address: 0x004e4230
// Searches a dynamic array of integers for a given value.
// The array is stored at +0x8, count at +0x18.
// The search value is passed in EDI (implicit register parameter).
// Returns true if the value is found, false otherwise.

bool __fastcall IntList_contains(void* this_unused, IntList* list) {
    // list->count at offset +0x18
    uint count = *(uint*)((uint)list + 0x18);
    uint index = 0;
    uint foundIndex = 0xFFFFFFFF; // Unlikely sentinel value

    if (count != 0) {
        // Loop until index exceeds count or a match is found
        while (true) {
            foundIndex = index;
            // Compare the array element at base+8 + index*4 to the search value in EDI
            if (*(int*)((uint)list + 8 + index * 4) == unaff_EDI) {
                break; // Match found, foundIndex is the index
            }
            index++;
            if (count <= index) {
                return false; // Exhausted all elements, no match
            }
        }
    }
    // Return true only if a match was found (foundIndex != -1)
    return foundIndex != 0xFFFFFFFF;
}