// FUNC_ADDR: 0x00435b70 - EARSMultiBaseObject::~EARSMultiBaseObject (destructor with multi‑inheritance vtable fixup and custom subobject cleanup)
void __thiscall EARSMultiBaseObject::~EARSMultiBaseObject(undefined4 *this) // this == param_1
{
    int *subObject; // iVar1

    // Set vtable pointers for the two base classes (offset 0 and 4)
    this[0] = &PTR_FUN_00e30eac;   // +0x00: base class 1 vtable
    this[1] = &PTR_LAB_00e30eb8;   // +0x04: base class 2 vtable

    // Call base class destructor (likely the most derived first base)
    FUN_0043e380(this);

    // Global cleanup? (static function, no arguments)
    FUN_00439930();

    // Free a member at offset 0xA4 (0x29 * 4)
    memFree(this[0x29]);            // +0xA4: pointer to dynamically allocated data

    // Access sub‑object at offset 0x90 (0x24 * 4)
    subObject = (int *)this[0x24];  // +0x90: pointer to a sub‑object
    if (subObject != 0) {
        // Free a member inside the sub‑object at offset 0x14
        memFree(*(undefined4 *)((int)subObject + 0x14));

        // If there's a custom deleter, call it
        if (*(int *)((int)subObject + 4) != 0) {
            // subObject+0x10 is a function pointer, subObject+0x4 is its argument
            (**(code **)((int)subObject + 0x10))(*(int *)((int)subObject + 4));
        }

        // Delete the sub‑object itself
        deleteObject(subObject);
    }

    // Update vtable pointers after destruction (sometimes used for finalization)
    this[1] = &PTR_LAB_00e30ebc;   // +0x04: alternative vtable (maybe empty base)
    g_destructorComplete = 0;       // global flag: DAT_012233f0
    this[0] = &PTR_LAB_00e30ea0;   // +0x00: final vtable (likely base of most derived)

    return;
}