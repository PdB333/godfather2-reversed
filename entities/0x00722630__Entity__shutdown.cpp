// FUNC_NAME: Entity::shutdown
// Function address: 0x00722630
// This function appears to be a destructor or cleanup method for an EARS engine object.
// It resets the vtable, releases internal resources, and decrements a global reference count.

// Offsets within this object:
// +0x00: vtable pointer (set to PTR_FUN_00d62090)
// +0x3C: pointer to another vtable/function table (set to PTR_LAB_00d62080)
// +0x48: pointer to another vtable/function table (set to PTR_LAB_00d6207c)
// +0x14C: pointer to first internal resource (likely an object)
// +0x164: pointer to second internal resource
// +0x17C: pointer to third internal resource

void __thiscall Entity::shutdown(void *this)
{
    // Reset virtual function table pointers (suggests possible re-initialization)
    *(int *)this = &PTR_FUN_00d62090;
    *(int *)((char *)this + 0x3C) = &PTR_LAB_00d62080;
    *(int *)((char *)this + 0x48) = &PTR_LAB_00d6207c;

    // Decrement global reference count or release global lock
    FUN_004086d0(&DAT_0120e93c);

    // Free internal resource at +0x14C if allocated
    if (*(int *)((char *)this + 0x14C) != 0) {
        FUN_004daf90((char *)this + 0x14C);
    }
    // Free internal resource at +0x164 if allocated
    if (*(int *)((char *)this + 0x164) != 0) {
        FUN_004daf90((char *)this + 0x164);
    }
    // Free internal resource at +0x17C if allocated
    if (*(int *)((char *)this + 0x17C) != 0) {
        FUN_004daf90((char *)this + 0x17C);
    }

    // Final global cleanup or integrity check
    FUN_0046c640();
    return;
}