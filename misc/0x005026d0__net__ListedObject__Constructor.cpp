// FUNC_NAME: net::ListedObject::Constructor
void __fastcall net::ListedObject::Constructor(NET::ListedObject *this) {
    // Set vtable to base class (e.g., Object)
    this->vtable = (void*)&PTR_FUN_00e37e18;
    // Call base class constructor (sets its vtable and initializes base members)
    FUN_004ebba0();
    // After base constructor, EDX likely holds this pointer (extraout_EDX)
    // Set own vtable for this derived class
    this->vtable = (void*)&PTR_FUN_00e37110;

    int *nodeData = (int *)this[4]; // this+0x10 (offset 4 ints)
    if (nodeData != 0) {
        // Global linked list head stored at DAT_01206880 + 0x14
        int **listHead = (int **)(DAT_01206880 + 0x14);
        // Insert node into list
        *(void***)*listHead = (void**)&PTR_LAB_01123be8; // Prev pointer?
        *listHead = *listHead + 1; // Advance to next slot? Actually listHead is pointer to head pointer
        // More likely: listHead points to a linked list where each node has prev/next pointers
        // Re-analyze: piVar2 = (int *)(DAT_01206880 + 0x14); // Get pointer to head?
        // *(undefined***)*piVar2 = &PTR_LAB_01123be8; // Set something at the head
        // *piVar2 = *piVar2 + 4; // Increment the pointer? Looks like building a list of function pointers?
        // Actually it seems to be adding to a global array of registered objects
        // Let's reconstruct based on pattern: it stores nodeData (the pointer from this+0x10) into a global list
        // The global appears to be a vector or array of pointers with sentinel
        // For clarity, we'll keep as-is with comments
        int *cursor = (int *)(DAT_01206880 + 0x14);
        *(void***)*cursor = (void**)&PTR_LAB_01123be8; // Store sentinel tag?
        *cursor = *cursor + 4; // Move to next slot
        *(int*)*cursor = (int)nodeData; // Store the node pointer
        *cursor = *cursor + 4; // Advance again
        // Clear the node's stored pointer (this+0x10) and next field (this+0x14)
        this[4] = 0;
        this[5] = 0;
    }
}