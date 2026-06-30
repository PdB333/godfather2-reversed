// FUNC_NAME: ContainerSearch::findMatchingElement
undefined4 __thiscall ContainerSearch::findMatchingElement(int this, int *searchParams)
{
    undefined4 *foundElement;
    undefined4 *endPtr;
    undefined4 keyRange[4]; // Actually local_10, local_c, local_8, local_4

    // Compute a key or range using searchParams
    keyRange[0] = FUN_004db060(searchParams[0] + searchParams[2],
                               searchParams[3] + searchParams[0] + searchParams[2]);

    // Initialize the rest of keyRange to 0 (likely unused)
    keyRange[1] = 0;
    keyRange[2] = 0;
    keyRange[3] = 0;

    // Perform a binary search or linear search over the container's array
    FUN_0068f290(&foundElement,
                 *(int *)(this + 0x10),  // start of array
                 *(int *)(this + 0x10) + *(int *)(this + 0x14) * 4, // end (ptr + count*4)
                 &keyRange,              // key to search for
                 &LAB_0068e370,          // comparison callback
                 0);                     // flags

    // Check if element was found and within bounds
    if ((foundElement != (undefined4 *)(*(int *)(this + 0x10) + *(int *)(this + 0x14) * 4)) &&
        (foundElement != endPtr)) {
        return *foundElement;
    }
    return 0;
}