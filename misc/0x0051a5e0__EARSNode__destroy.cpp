// FUNC_NAME: EARSNode::destroy
void __thiscall EARSNode::destroy(void)
{
    int index;
    ChildObject* child; // pointer to each child object (struct of 20 bytes)
    short childCount;

    // Pre-destruction update
    FUN_0051d6b0(); // likely EARSNode::preDestroyUpdate()

    childCount = *(short*)(this + 0x80); // +0x80: number of children
    if (0 < childCount) {
        // Array of child objects starts at +0xf4, each 20 bytes (5 ints)
        // The first field at offset 0 is a pointer to a child object
        child = *(ChildObject**)(this + 0xf4);
        do {
            if (child != (ChildObject*)0) {
                child->destroy(); // FUN_005343f0: specific child destruction method
            }
            index++;
            child = (ChildObject*)((int)child + 20); // advance to next child slot (5 * 4 bytes)
        } while (index < childCount);
    }

    // Release ref-counted object at +0x20
    if (*(int*)(this + 0x20) == 0) {
        // Already null, force clear (redundant)
        *(int*)(this + 0x20) = 0;
        return;
    }
    // Decrement reference count (ref count at object+4)
    int* refCount = (int*)(*(int*)(this + 0x20) + 4);
    *refCount = *refCount - 1;
    if (*(int*)(*(int*)(this + 0x20) + 4) == 0) {
        // No more references, delete via vtable (first entry +4)
        (**(code**)(**(int**)(this + 0x20) + 4))(); // virtual destructor
    }
    *(int*)(this + 0x20) = 0; // clear pointer
    return;
}