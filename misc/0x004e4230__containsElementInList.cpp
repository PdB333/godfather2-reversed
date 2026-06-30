// FUNC_NAME: containsElementInList
// Function at 0x004e4230: Searches a list container for a specific value.
// The container structure has:
//   +0x08: array of int pointers (search targets)
//   +0x18: uint32_t count of elements
// In the original assembly, the container pointer is passed in EDX (param_2),
// and the search value is passed in the EDI register (not shown in signature).
// For clarity, we make the search value an explicit parameter.

bool __fastcall containsElementInList(void* listContainer, int searchValue) // listContainer in EDX, searchValue in EDI
{
    uint index = 0;
    uint foundIndex = 0xFFFFFFFF;

    uint count = *(uint*)((int)listContainer + 0x18);
    if (count != 0) {
        // Walk the array until a match is found or we run out of elements
        while (true) {
            foundIndex = index;
            if (*(int*)((int)listContainer + 0x8 + index * 4) != searchValue) {
                index++;
                if (count <= index) {
                    return false; // not found
                }
                // continue loop
            } else {
                break; // found
            }
        }
    }

    // If we exit the loop, either we found a match (foundIndex != -1) or count was 0
    return (foundIndex != 0xFFFFFFFF);
}