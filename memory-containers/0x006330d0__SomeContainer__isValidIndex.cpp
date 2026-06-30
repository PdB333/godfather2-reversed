//FUNC_NAME: SomeContainer::isValidIndex
// Function at 0x006330d0: Checks if an index is within valid range for a container structure.
// Structure offsets: +0x28 (int capacity), +0x47 (byte count)
// Returns 1 if index is valid, 0 otherwise.
__thiscall int SomeContainer::isValidIndex(int index) {
    // Check if index is within the primary range (first 250 entries) or secondary range
    if (((unsigned int)(*(unsigned char *)(this + 0x47)) <= (unsigned int)index) &&
        ((index < 0xfa || (*(int *)(this + 0x28) <= index - 0xfa)))) {
        return 0;
    }
    return 1;
}