// FUNC_NAME: Unknown::destructor (releases resource at offset 0xB0)
void __thiscall Unknown::~Unknown(void* this)
{
    int** ppResource; // pointer to resource pointer at offset 0xB0

    // Set vtable pointer to derived class vtable
    *(void**)this = &PTR_FUN_00d73398;

    ppResource = (int**)((char*)this + 0xB0); // offset 0xB0: pointer to allocated resource
    if (*ppResource != 0) {
        // Custom release function (likely frees memory and sets pointer to null)
        releaseResource(ppResource); // FUN_004daf90
        *ppResource = 0;
    }

    // Redundant check (compiler artifact or dead code)
    if (*ppResource != 0) {
        releaseResource(ppResource);
    }

    // Set vtable to base class vtable (for correct destruction chain)
    *(void**)this = &PTR_LAB_00e32854;
}