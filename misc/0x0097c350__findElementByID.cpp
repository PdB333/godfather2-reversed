// FUNC_NAME: findElementByID
// Function address: 0x0097c350
// Searches a linear array of 0x10-byte elements for one whose field at +0x8 matches the given ID.
// Returns pointer to the element if found, else 0.
// param_1: ID to search for
// param_2: pointer to container struct: [0] = base pointer to array, [4] = count of elements

int* findElementByID(int id, int* container) {
    int* result = 0;
    unsigned int index = 0;

    if (container[1] != 0) { // count > 0
        int* element = (int*)(container[0] + 8); // start at offset 8 of first element
        while (*element != id) {
            index++;
            element += 4; // advance 16 bytes (4 ints) to next element's offset 8
            if ((unsigned int)container[1] <= index) {
                return result; // not found
            }
        }
        // found: compute pointer to start of element
        result = (int*)(container[0] + index * 0x10);
    }
    return result;
}