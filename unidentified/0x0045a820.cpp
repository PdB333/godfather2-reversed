// FUN_0045a820: EARSObjectHandle::updateRegistration
void __thiscall EARSObjectHandle::updateRegistration(void)
{
    int *handle = (int *)this;
    if (*handle != 0x1961bed) {
        return; // invalid handle magic
    }

    EARSObject *obj = (EARSObject *)handle[2]; // +0x08: pointer to actual object
    uint32_t flags = *(uint32_t *)((char *)obj + 0x24); // object flags

    if (flags & 0x400) {
        // object is enabled; update transforms and visibility
        FUN_0045a7c0(); // likely updateTransforms()
        if (flags & 0x100) {
            FUN_00421260(); // likely updateVisibility()
        }

        // Allocate a new node from the memory pool.
        // The global DAT_01206880 is a pool manager; offset 0x14 is the current allocation pointer.
        int **allocPointer = (int **)(DAT_01206880 + 0x14); // pointer to pool cursor

        // Write the vtable pointer (static symbol) at the current cursor location.
        *(int *)*allocPointer = (int)&PTR_LAB_0110b910; // node vtable

        // Advance cursor by size of vtable pointer (4 bytes)
        *allocPointer = (int *)((int)*allocPointer + 4);

        // Align the cursor to next 4-byte boundary
        *allocPointer = (int *)(((int)*allocPointer + 3) & ~3);

        // Store the object pointer in the allocated node
        **allocPointer = (int)obj;

        // Advance cursor past the stored pointer
        *allocPointer = (int *)((int)*allocPointer + 4);
    } else {
        // Object is disabled; remove it from the list
        ListManager *mgr = (ListManager *)FUN_00420be0(); // get the list manager
        (*(void (__thiscall **)(EARSObject *, int))(*mgr + 4))(obj, 0); // call remove(object,0)
    }
}