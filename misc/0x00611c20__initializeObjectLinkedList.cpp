// FUNC_NAME: initializeObjectLinkedList
// Address: 0x00611c20
// Role: Initializes a linked list of 20 objects from a static pointer array.
// Each object has a vtable; virtual functions at offsets 4 and 0x10 are called.
// Objects are linked via offset 4 (next) and assigned an index at offset 12.
// Global head pointer (DAT_012058ec) and counter (DAT_012058f8) are updated.

void initializeObjectLinkedList(void)
{
    int *objectPtr;
    int returnVal;
    int objectId;
    uint i;

    // Global initialization (likely sets up some base state)
    FUN_00609f70();

    // Iterate over 20 object pointers stored in a static array
    for (i = 0; i < 0x14; i++)
    {
        // Retrieve the i-th object pointer from the static array
        objectPtr = *(int **)((int)&PTR_PTR_00f15940 + i * 4);

        // Call virtual function at vtable+4 (likely returns an identifier or name)
        returnVal = (**(code **)(*objectPtr + 4))();

        // Convert the return value into an ID (e.g., hash or lookup)
        objectId = FUN_0060d740(returnVal);

        // Store the ID at offset +0x08
        objectPtr[2] = objectId;

        // Call virtual function at vtable+0x10 (likely initialization/reset)
        (**(code **)(*objectPtr + 0x10))();

        // Link the object into the global singly-linked list:
        // Set next pointer (offset +0x04) to current head
        objectPtr[1] = (int)DAT_012058ec;

        // Increment global counter (used for index assignment)
        DAT_012058f8 = DAT_012058f8 + 1;

        // Update global head to this object
        DAT_012058ec = objectPtr;

        // Store the index (offset +0x0C) from the global counter
        objectPtr[3] = DAT_012058f8;
    }
}