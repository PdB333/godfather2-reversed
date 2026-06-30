// FUNC_NAME: Component::constructor

// Constructor for a component class (size 0x60 bytes). 
// Sets vtable pointer at offset +0x58, initializes global flag, and optionally deallocates.
int __thiscall Component::constructor(Component *this, byte flags)
{
    int *vtableSlot;

    if (this == (Component *)0x0) {
        vtableSlot = (int *)0x0;
    } else {
        vtableSlot = (int *)((char *)this + 0x58); // vtable stored at +0x58
    }
    *vtableSlot = (int)&gComponentVTable; // PTR_LAB_00d5f2f0
    g_someGlobalFlag = 0; // DAT_0112a874
    initializeBase(); // FUN_00473880 - likely base class init
    if ((flags & 1) != 0) {
        operatorDelete(this, 0x60); // FUN_0043b960 - deallocate object (size 0x60)
    }
    return (int)this;
}