// FUNC_NAME: EARSObject::initialize
void EARSObject::initialize(int resourceId)
{
    // Virtual call at vtable+8: base initialization
    (*(void (__thiscall **)(EARSObject *))(*(int *)this + 8))(this);

    if (resourceId != 0)
    {
        // Create or attach a resource; FUN_004265d0 returns a pointer to the resource
        // Offset +0x4: stored resource pointer
        *(int *)(this + 4) = FUN_004265d0(resourceId, this);
        // Virtual call at vtable+4: attach resource with some flag (0)
        (*(void (__thiscall **)(EARSObject *, int, int))(*(int *)this + 4))(this, resourceId, 0);
        // Virtual call at vtable+12: finalize initialization
        (*(void (__thiscall **)(EARSObject *))(*(int *)this + 12))(this);
    }
    else
    {
        // No resource: clear pointer
        *(int *)(this + 4) = 0;
        // Virtual call at vtable+12: finalize initialization
        (*(void (__thiscall **)(EARSObject *))(*(int *)this + 12))(this);
    }
}