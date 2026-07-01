// FUNC_NAME: Destructible::~Destructible
void __fastcall Destructible::~Destructible(void* thisPtr) {
    // param_1 in decompiled is this pointer, passed in ECX (__fastcall)
    int* this_ = (int*)thisPtr;

    // Set vtable to derived class vtable (likely this class's own vtable)
    *this_ = &PTR_LAB_00d6f9bc;
    // Set another vtable or function pointer at +0x74 (0x1d * 4)
    this_[0x1d] = (int)&PTR_LAB_00d6f9b8;

    // If there's a child object at +0x7C (0x1f * 4), release it
    if (this_[0x1f] != 0) {
        // Presumably delete or release the child
        FUN_00851230(this_[0x1f]);
        FUN_009f01a0(); // Possibly a post-release cleanup
    }

    // Some generic cleanup
    FUN_007e17b0();

    // Iterate over a linked list at +0x98 (0x26 * 4)
    int* node = (int*)this_[0x26];
    while (node != nullptr) {
        // Check if node type is valid (non-zero and not a sentinel 0x48)
        if ((node[0] != 0) && (node[0] != 0x48)) {
            // Notify something at +0x58 (0x16 * 4) about this node
            FUN_007208e0(this_[0x16]);
        }
        node = (int*)node[3]; // Next node at offset +0x0C (3 * 4)
    }

    // Another linked list at +0xAC (0x2b * 4)
    node = (int*)this_[0x2b];
    while (node != nullptr) {
        if ((node[0] != 0) && (node[0] != 0x48)) {
            FUN_0071f540(this_[0x16]); // Different notification
        }
        node = (int*)node[3];
    }

    // Array of objects at +0xD4 (0x35 * 4), with count at +0xD8 (0x36 * 4)
    int count = this_[0x36];
    while (--count >= 0) {
        // Each slot is 8 bytes? Actually each element is 8 bytes (2 ints)
        int* elem = (int*)(this_[0x35] + count * 8);
        if (elem[0] != 0) {
            FUN_004daf90(elem); // Release individual element
        }
    }
    // Free the array itself
    if (this_[0x35] != 0) {
        FUN_009c8f10(this_[0x35]);
    }

    // Another cleanup pair (unknown purpose)
    FUN_007e2d30();
    FUN_007e2c60();
    FUN_007e2c60(); // Called twice?

    // Second array at +0x8C (0x23 * 4) with count at +0x90 (0x24 * 4)
    count = this_[0x24];
    while (--count >= 0) {
        int* elem = (int*)(this_[0x23] + count * 8);
        if (elem[0] != 0) {
            FUN_004daf90(elem);
        }
    }
    if (this_[0x23] != 0) {
        FUN_009c8f10(this_[0x23]);
    }

    // Release a single object stored at +0x84 (0x21 * 4)
    if (this_[0x21] != 0) {
        FUN_004daf90((int*)(this_ + 0x21)); // Note: address of the field, not its value
    }

    // Reset the function pointer at +0x74 to a new one (likely base class vtable entry)
    this_[0x1d] = (int)&PTR_FUN_00e32808;

    // Clear a linked list at +0x78 (0x1e * 4) by setting first and second fields to 0
    int* iter = (int*)this_[0x1e];
    while (iter != nullptr) {
        int* next = (int*)iter[1]; // Next node at offset +0x04
        iter[0] = 0; // Clear first field
        iter[1] = 0; // Clear second field
        iter = next;
    }

    // Reset vtable to base class vtable (destructor chain)
    *this_ = (int)&PTR_LAB_00d6b95c;
    // Call base class destructor
    FUN_0080ea60();
}