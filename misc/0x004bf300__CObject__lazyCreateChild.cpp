// FUNC_NAME: CObject::lazyCreateChild

void __thiscall CObject::lazyCreateChild(int this)
{
    // Check prerequisites: resource pointer (+0x8) is non-null,
    // factory object (+0xc) is non-null,
    // and the factory's virtual method at vtable[2] returns a handle.
    // Then allocate child object if not already created (+0x36c == 0).
    if ((*(int *)(this + 0x8) != 0) && (*(int **)(this + 0xc) != nullptr))
    {
        // Call a virtual function on the factory object (vtable offset 0x8)
        // to obtain a creation parameter (e.g., a resource handle).
        int handle = (*(int (__thiscall **)(int))(*(*(int **)(this + 0xc)) + 8))(*(int *)(this + 0xc));

        // Check if child object has not been created yet.
        if (*(int *)(this + 0x36c) == 0)
        {
            // Allocate memory for a new object of size 0x6c.
            void *alloc = AllocateMemory(0x6c);
            if (alloc != nullptr)
            {
                // Construct the child object using a factory function,
                // passing the parameter from offset +0x374 and the handle.
                void *child = ConstructChild(*(int *)(this + 0x374), handle);
                *(int *)(this + 0x36c) = (int)child;
            }
            else
            {
                *(int *)(this + 0x36c) = 0;
            }
        }
    }
}