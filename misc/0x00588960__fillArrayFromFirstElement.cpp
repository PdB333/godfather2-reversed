// FUNC_NAME: fillArrayFromFirstElement
// Function address: 0x00588960
// Role: Broadcasts the first element of an int array to all subsequent elements, 
//       calling a helper function on each iteration.
// Parameters (passing convention: EAX = endPtr, EDI = startPtr)
void fillArrayFromFirstElement(void)
{
    int* startPtr;   // unaff_EDI (register EDI)
    int* endPtr;     // in_EAX (register EAX)
    int byteDiff;    // iVar1
    int* dest;       // temporary for clarity

    // byteDiff = endPtr - startPtr (in bytes)
    byteDiff = (int)endPtr - (int)startPtr;

    // Loop while byteDiff/4 > 1 (i.e., at least one element after the first)
    for ( ; 1 < byteDiff >> 2; byteDiff -= 4) {
        // Write the first element to the location at offset (byteDiff - 4) from start
        dest = (int*)((int)startPtr + byteDiff - 4);
        *dest = *startPtr;
        // Call some per‑element function (presumably a constructor or callback)
        FUN_00588b80();
    }
}