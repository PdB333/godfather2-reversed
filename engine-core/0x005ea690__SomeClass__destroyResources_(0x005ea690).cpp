// FUNC_NAME: SomeClass::destroyResources (0x005ea690)
// This destructor-style helper frees an array of 5 ObjectPair structures (each containing two pointers)
// and then calls a virtual destructor on a member object at +0x4.

void __thiscall SomeClass::destroyResources()
{
    int i;
    int *pairPtr; // pointer to second element of current ObjectPair

    // Loop over 5 ObjectPair structures (size 0x30 each) stored at offsets 0x1c to 0x10c.
    // The loop iterates backwards from the end of the array.
    i = 4;
    pairPtr = (int *)(this + 0x10c); // start just past the array

    do {
        int *firstPtr = pairPtr - 9;   // first element of the pair (offset -0x24 in bytes)
        pairPtr = pairPtr - 0xc;       // second element of the pair (offset -0x30 in bytes)

        if (*firstPtr != 0) {
            FUN_009c8f10(*firstPtr); // deallocate resource
        }
        if (*pairPtr != 0) {
            FUN_009c8f10(*pairPtr); // deallocate resource
        }
        i = i - 1;
    } while (i >= 0);

    // If the member at +0x4 is non-null, call its virtual destructor (via offset +0x10 in vtable)
    if (*(int *)(this + 4) != 0) {
        (**(code **)(this + 0x10))(*(int *)(this + 4));
    }

    return;
}