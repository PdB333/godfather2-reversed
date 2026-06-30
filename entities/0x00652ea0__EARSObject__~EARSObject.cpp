// FUNC_NAME: EARSObject::~EARSObject
void __thiscall EARSObject::~EARSObject(void) {
    int *refCountPtr;
    int *refCountPtr2;
    undefined4 *listNode;
    undefined4 *nextNode;

    // Set vtable to derived class vtable (or current class)
    this->vtable = &PTR_LAB_00e43088;

    // Call base destructor or cleanup function
    FUN_00652df0();

    // Release a resource at offset 0x72 (0x72*4 = 0x1C8)
    FUN_009c8eb0(this->field_0x72);

    // Decrement reference count at offset 0x6C (0x6C*4 = 0x1B0)
    refCountPtr = (int *)this->field_0x6C;
    if (refCountPtr != (int *)0x0) {
        refCountPtr2 = refCountPtr + 2; // offset 8 from refCountPtr
        *refCountPtr2 = *refCountPtr2 - 1;
        if (*refCountPtr2 == 0) {
            // Call destructor via vtable at refCountPtr
            (**(code **)(*refCountPtr + 8))();
        }
    }

    // Remove node from linked list at offsets 0x69, 0x6A, 0x6B (0x1A4, 0x1A8, 0x1AC)
    if (this->field_0x69 != 0) {
        if (this->field_0x6A == 0) {
            *(undefined4 *)(this->field_0x69 + 4) = this->field_0x6B;
        } else {
            *(undefined4 *)(this->field_0x6A + 8) = this->field_0x6B;
        }
        if (this->field_0x6B != 0) {
            *(undefined4 *)(this->field_0x6B + 4) = this->field_0x6A;
        }
    }

    // Another cleanup function
    FUN_00652d00();

    // Remove node from another linked list at offsets 0x49, 0x4A, 0x4B (0x124, 0x128, 0x12C)
    if (this->field_0x49 != 0) {
        if (this->field_0x4A == 0) {
            *(undefined4 *)(this->field_0x49 + 4) = this->field_0x4B;
        } else {
            *(undefined4 *)(this->field_0x4A + 8) = this->field_0x4B;
        }
        if (this->field_0x4B != 0) {
            *(undefined4 *)(this->field_0x4B + 4) = this->field_0x4A;
        }
    }

    // Decrement global instance counter
    _DAT_01205a30 = _DAT_01205a30 - 1;

    // Set vtable to base class vtable (or after destruction)
    this->vtable = &PTR_LAB_00e42de4;

    // Clear linked list starting at offset 0x4 (this->field_0x4)
    listNode = (undefined4 *)this->field_0x4;
    while (listNode != (undefined4 *)0x0) {
        nextNode = (undefined4 *)listNode[2]; // next pointer at offset 8
        listNode[0] = 0;
        listNode[1] = 0;
        listNode[2] = 0;
        listNode = nextNode;
    }
    return;
}