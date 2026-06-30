// FUNC_NAME: SomeClass::constructor
int __thiscall SomeClass::constructor(void *this) {
    // vtable pointer at global DAT_01205590
    int *vtable = *(int **)DAT_01205590;
    // Call virtual function at offset 0x10 (likely base class initializer)
    ((void (__thiscall *)(void *))vtable[4])(this); // offset 0x10 = index 4

    // Set field at offset +2 to 2 (e.g., a type or flag)
    *(int *)((char *)this + 2) = 2;

    // Set field at offset +4 to a pointer to a local value (0x602)
    // The local variable local_8 holds 0x602, and puStack_14 points to it.
    // The virtual function copies the pointer value into the field.
    int local_8 = 0x602;
    int *puStack_14 = &local_8;
    ((void (__thiscall *)(void *, int **, int))vtable[4])((char *)this + 4, &puStack_14, 4);

    // Set field at offset +8 to 2 (e.g., a size or count)
    int auStack_1c = 2;
    ((void (__thiscall *)(void *, int *, int))vtable[4])((char *)this + 8, &auStack_1c, 4);

    return 0xc; // likely the object size (12 bytes)
}