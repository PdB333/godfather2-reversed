// FUNC_NAME: RefPtr::Release
void __thiscall RefPtr::Release(void)
{
    int *manager;       // Points to the reference-counted table manager
    int *resource;      // Points to the resource object being released
    int index;          // Index into the manager's allocation table
    int *refCountPtr;   // Pointer to the reference count in the manager

    // 'this' is a pointer to a RefPtr object embedded in a larger block.
    // Layout (offsets relative to this):
    //   +0x00 : m_pManager (pointer to the allocation table)
    //   +0x10 : m_pResource (pointer to the referenced resource)
    //   -0x08 : resource index stored just before this RefPtr
    //   -0x04 : base of the outer allocation (the block containing both index and RefPtr)

    if (this == (int *)0x0) {
        return;
    }

    manager = (int *)*this;           // this->m_pManager
    resource = (int *)this[4];        // this->m_pResource (offset 0x10)

    // Release the resource (if non-null)
    if (resource != (int *)0x0) {
        // The resource object layout (relative to resource pointer):
        //   -0x10 : base of resource allocation
        //   -0x08 : index in the manager's allocation table
        //   +0x00 : start of resource data
        index = *(int *)(resource + (-8));  // resource[-8] ?
        // Clear the slot in the manager's allocation table at manager->table[index]
        *(int *)(*(int *)((int)manager + 0xC) + index * 4) = 0;

        // Decrement the manager's reference count
        refCountPtr = (int *)((int)manager + 4);
        *refCountPtr = *refCountPtr - 1;

        // Free the resource object (starting at resource - 0x10)
        (*(code *)DAT_01206694)((int)resource - 0x10);
    }

    // Now release the RefPtr itself (the outer allocation containing this & its index)
    manager = (int *)*this;   // reuse manager (should be same as before)
    // Index for this RefPtr is stored at this[-2] (offset -8 from this)
    index = *(int *)(this + (-2));
    // Clear the slot in the manager's table
    *(int *)(*(int *)((int)manager + 0xC) + index * 4) = 0;

    // Decrement the manager's reference count again
    refCountPtr = (int *)((int)manager + 4);
    *refCountPtr = *refCountPtr - 1;

    // Free the outer allocation block (starting at this - 4)
    (*(code *)DAT_01206694)((int)this - 4);
}