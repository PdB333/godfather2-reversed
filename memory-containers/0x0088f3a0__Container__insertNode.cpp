// FUNC_NAME: Container::insertNode
// Function at 0x0088f3a0: Allocates a new node (0x14 bytes) and inserts it into a container,
// incrementing a size counter at this+0x14. The insertion is controlled by a flag uVar2,
// which is set to 1 if the check condition fails (param5==0, param3!=this+4, and *(param3+0x10)<=*param4).
// param2 is an output pointer that receives the newly allocated node.
void __thiscall Container::insertNode(int this, int *outNode, int element, uint *keyValue, char checkFlag)
{
    int newNode;
    bool performInsert;

    // Determine whether to perform insertion based on checkFlag and a comparison of values
    if (checkFlag == '\0' && element != this + 4 && *(uint *)(element + 0x10) <= *keyValue) {
        performInsert = 1;
    } else {
        performInsert = 0;
    }

    // Allocate a 20-byte node from EASTL's default allocator (debug line 0xe9)
    newNode = FUN_0068ab90(0x14, "EASTL", 0, 0,
                          "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xe9);

    // Store the key value at offset +0x10 of the new node
    // (the condition is assumed to always succeed after a valid allocation)
    *(uint *)(newNode + 0x10) = *keyValue;

    // Insert the new node into the container (this+4 is likely the head/root)
    FUN_00ab3da0(newNode, element, this + 4, performInsert);

    // Increment the container's element count (stored at this+0x14)
    *(int *)(this + 0x14) = *(int *)(this + 0x14) + 1;

    // Return the new node via output parameter
    *outNode = newNode;
    return;
}