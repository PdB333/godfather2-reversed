// FUNC_NAME: UIElement::copyFrom

void __thiscall UIElement::copyFrom(int *this, void *source)
{
    char cVar1;
    char *pcVar4;
    int *piVar3;
    char *pcVar5;

    cVar1 = FUN_0067e210(); // check if system initialized
    if (cVar1 == '\0') {
        FUN_006817c0(); // initialize system
        FUN_004e0180(); // additional init
    }

    piVar3 = (int *)FUN_006833d0(source); // cast source to object type
    if (piVar3 != this) {
        // copy name buffer (64 bytes)
        pcVar5 = (char *)(**(code **)(*piVar3 + 0x18))(); // virtual getter: getName() at vtable+0x18
        _strncpy((char *)((int)this + 0xb), pcVar5, 0x40);

        // copy description buffer (256 bytes)
        pcVar5 = (char *)(**(code **)(*piVar3 + 0x1c))(); // virtual getter: getDescription() at vtable+0x1c
        _strncpy((char *)((int)this + 0x4c), pcVar5, 0x100); // second buffer at +0x4c

        // null terminate both buffers
        *(char *)((int)this + 0x4b) = '\0'; // end of name buffer
        *(char *)((int)this + 0x14c) = '\0'; // end of description buffer
    }

    FUN_009c7700(); // finalize or update internal state

    // compare name and description, store result flag at +0x0a
    *(char *)((int)this + 0xa) = FUN_0067c9f0((int)this + 0xb, (int)this + 0x4c);

    FUN_00411cf0(); // additional processing

    // set a global flag if name and description are equal
    FUN_0068c590(*(char *)((int)this + 0xa) == '\0');

    // set bit 0 at global +0x4c
    *(uint *)(DAT_012234a4 + 0x4c) |= 1;
}