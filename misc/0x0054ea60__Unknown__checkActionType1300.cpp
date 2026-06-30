// FUNC_NAME: Unknown::checkActionType1300
// Address: 0x0054ea60
// Searches for an action type ID (0x1300) in a component array, then looks up a resource and calls a virtual method.
// Likely part of AI behavior or state machine.

int __thiscall FUN_0054ea60(void) {
    int componentCount;
    int componentBasePtr;
    int index;
    int *arrayPtr;
    int *localArray[2]; // for resource lookup

    // Read a byte at this+0x10 to get an offset, then add to this to get component base.
    // Then read count from componentBase+0x78
    componentBasePtr = *(char *)(this + 0x10) + this;
    componentCount = *(int *)(componentBasePtr + 0x78);

    index = 0;
    if (componentCount > 0) {
        arrayPtr = *(int **)(componentBasePtr + 0x74);
        // Search for value 0x1300 in the array
        while (*arrayPtr != 0x1300) {
            index++;
            arrayPtr += 4;
            if (componentCount <= index) {
                return 0;
            }
        }
        // Found: call resource lookup function (likely static)
        FUN_004af8c0(localArray, 0x2001);
        if (localArray[0] != 0) {
            // Call virtual method at offset 0x10 (4th method) with hash 0xd80c71d2
            char result = (*(char (**)(int, int **))(*(int *)localArray[0] + 0x10))(0xd80c71d2, localArray);
            if ((result != 0) && (unaff_ESI != 0)) {
                return 1;
            }
        }
    }
    return 0;
}