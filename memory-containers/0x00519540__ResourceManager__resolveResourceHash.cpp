// FUNC_NAME: ResourceManager::resolveResourceHash
uint __thiscall ResourceManager::resolveResourceHash(void *this, uint param1, uint param2)
{
    // Check if both resource pointers (offsets +0x14 and +0x24) are null
    if (*(int *)(this + 0x14) == 0 && *(int *)(this + 0x24) == 0)
    {
        // If both null, return a masked version of 'this' pointer (lower byte cleared)
        return (uint)this & 0xFFFFFF00;
    }

    // Check if pointer at +0x1C is null
    if (*(int *)(this + 0x1C) == 0)
    {
        int iVar2 = 0;
        // If pointer at +0x14 is not null, compute a value using TLS (thread-local storage)
        if (*(int *)(this + 0x14) != 0)
        {
            // Access TLS: FS:[0x2C] gives thread local storage base, then dereference +8
            iVar2 = *(int *)(*(int **)(__readfsdword(0x2C)) + 8) + *(int *)(this + 0x14);
        }

        if (iVar2 == 0)
        {
            // If computed value is zero, call a virtual function via vtable at +0x24, offset 0x18
            uint uVar1 = (*(code **)(**(int **)(this + 0x24) + 0x18))(param1, param2);
            return uVar1;
        }
    }

    // Otherwise, call a helper function with offset 0x30 from the object at +0x24
    uint uVar1 = FUN_00518F00(*(int *)(this + 0x24) + 0x30);
    return uVar1;
}