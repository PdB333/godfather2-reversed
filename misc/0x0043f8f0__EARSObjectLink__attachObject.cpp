// FUNC_NAME: EARSObjectLink::attachObject
void __thiscall EARSObjectLink::attachObject(int *object, int parent) {
    // this->objectPtr (offset 0x00): pointer to the EARS object being attached
    this->objectPtr = object;               // *unaff_EDI = param_1

    // Call virtual function at vtable offset 8 on the object (likely pre-attach init)
    (**(code **)(*object + 8))();

    if (parent != 0) {
        // Create a new child link using parent context and the object
        // FUN_004265d0 is probably an allocation/creation function returning a pointer
        int *newChild = FUN_004265d0(parent, object);
        this->childPtr = newChild;          // unaff_EDI[1] = uVar1 (offset 0x04)

        // Call virtual function at offset 4 on the object (attach to parent)
        (**(code **)(*object + 4))(parent, 0);

        // Call virtual function at offset 12 on the object (post-attach finalization)
        (**(code **)(*object + 0xc))();
    } else {
        this->childPtr = 0;                 // unaff_EDI[1] = 0
        // Call virtual function at offset 12 without parent action
        (**(code **)(*object + 0xc))();
    }
}