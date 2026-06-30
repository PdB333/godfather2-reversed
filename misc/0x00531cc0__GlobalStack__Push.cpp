// FUNC_NAME: GlobalStack::Push

// Function at 0x00531cc0: Pushes a new element onto a global stack or registry.
// This appears to be part of a reference counting or manager registration system.
// The global variables are likely linked list head, counter, and node fields.

void GlobalStack::Push(void)
{
    uint uVar1;

    // Call a virtual function (or interface method) at vtable offset 1 (index 1, i.e. second function)
    // Assumes DAT_0121bc10 points to an object with a vtable.
    uVar1 = (*(code **)(DAT_0121bc10 + 4))();  // Call through vtable[1] (since +4 = offset for first virtual method in typical vtable layout)

    // Store result of some global function into _DAT_0121bc18
    _DAT_0121bc18 = FUN_0060d740(uVar1);       // Possibly a conversion or hash function

    // Call another virtual function at vtable offset 4 (index 4, i.e. fifth function)
    (*(code **)(DAT_0121bc10 + 0x10))();       // vtable offset 0x10 = 16 bytes = fourth entry (assuming 4-byte pointers)

    // Save current head of global list into _DAT_0121bc14
    _DAT_0121bc14 = DAT_012058ec;              // Previously stored head pointer

    // Increment global counter (maybe node count or timestamp)
    DAT_012058f8 = DAT_012058f8 + 1;

    // Set head to point to the structure at DAT_0121bc10
    DAT_012058ec = &DAT_0121bc10;

    // Store the new counter value into _DAT_0121bc1c
    _DAT_0121bc1c = DAT_012058f8;

    return;
}