// FUNC_NAME: SomeClass::destructor
void __thiscall SomeClass::destructor(void) {
    int *refcountObj;
    int *toRelease;
    int *childListIter;
    int *nextChild;

    // Set vtable pointer to derived class vtable
    this->vtablePtr = &PTR_LAB_00e43088;

    // Call base class destructor (or some cleanup function)
    FUN_00652df0();

    // Release a resource at offset 0x1C8 (0x72 * 4)
    FUN_009c8eb0(this->field_0x1C8);

    // Decrement reference count for object at offset 0x1B0 (0x6c * 4)
    refcountObj = this->field_0x1B0;
    if (refcountObj != 0) {
        toRelease = refcountObj + 2; // offset 8: reference count
        *toRelease = *toRelease - 1;
        if (*toRelease == 0) {
            // Call destructor via vtable
            (*(code**)(*refcountObj + 8))();
        }
    }

    // Remove this object from linked list (list A) using fields at +0x1A4, +0x1A8, +0x1AC
    // field_0x1A4 = previous node, field_0x1A8 = next node, field_0x1AC = self pointer (node)
    if (this->field_0x1A4 != 0) {
        if (this->field_0x1A8 == 0) {
            *(int*)(this->field_0x1A4 + 4) = this->field_0x1AC; // prev->next = self
        } else {
            *(int*)(this->field_0x1A8 + 8) = this->field_0x1AC; // next->prev = self
        }
    }
    if (this->field_0x1AC != 0) {
        *(int*)(this->field_0x1AC + 4) = this->field_0x1A8; // self->next = next
        *(int*)(this->field_0x1AC + 8) = this->field_0x1A4; // self->prev = prev
    }

    // Call another cleanup function (maybe second base destructor)
    FUN_00652d00();

    // Remove this object from linked list (list B) using fields at +0x124, +0x128, +0x12C
    if (this->field_0x124 != 0) {
        if (this->field_0x128 == 0) {
            *(int*)(this->field_0x124 + 4) = this->field_0x12C;
        } else {
            *(int*)(this->field_0x128 + 8) = this->field_0x12C;
        }
    }
    if (this->field_0x12C != 0) {
        *(int*)(this->field_0x12C + 4) = this->field_0x128;
        *(int*)(this->field_0x12C + 8) = this->field_0x124;
    }

    // Decrement global counter
    _DAT_01205a30 = _DAT_01205a30 - 1;

    // Set vtable to base class vtable
    this->vtablePtr = &PTR_LAB_00e42de4;

    // Clear all child nodes in linked list starting from field_0x4
    childListIter = this->field_0x4;
    while (childListIter != 0) {
        nextChild = childListIter[2]; // +8: next child pointer
        childListIter[0] = 0; // +0: vtable or data
        childListIter[1] = 0; // +4: next or data
        childListIter[2] = 0; // +8: previous or data
        childListIter = nextChild;
    }
}