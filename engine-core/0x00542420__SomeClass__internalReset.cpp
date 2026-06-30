// FUNC_NAME: SomeClass::internalReset
// Address: 0x00542420 - Likely a member function that resets a node or entry within a manager, adjusting linked list pointers and zeroing a field at offset +0xC.
void __thiscall SomeClass::internalReset(int thisPtr)
{
    // thisPtr is the 'this' pointer passed in ECX.
    // Call a function using the address (thisPtr - 4). This likely accesses a base class or previous link.
    sub_9F1B20(thisPtr - 4);

    int adjustedPtr;
    if (thisPtr == 4) {
        // Special case: if 'this' is 4 (unusual, maybe an error or sentinel), use 0.
        adjustedPtr = 0;
    } else {
        // Otherwise compute forward offset for another call.
        adjustedPtr = thisPtr + 4;
    }

    sub_9F1AD0(adjustedPtr); // Address at +4: possibly next link or sibling.
    sub_9F01A0();            // Global state update (e.g., increment manager count).

    // Zero out a field at offset +0xC from this object.
    *(int *)(thisPtr + 0xC) = 0;
}