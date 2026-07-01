// FUNC_NAME: BaseObject::constructor
undefined4* __fastcall BaseObject::constructor(BaseObject* this)
{
    uint puVar1;
    undefined4* puVar2;

    puVar1 = FUN_00840250(); // likely memory allocator or system function
    puVar2 = (undefined4*)FUN_008401e0(0x190, puVar1); // allocate 400 bytes (0x190)
    if (puVar2 != (undefined4*)0x0) {
        FUN_00848d00(); // base class constructor
        FUN_008420b0(); // init base class vtable or something
        puVar2[4] = &PTR_LAB_00d74828; // set vtable at offset +16
        *puVar2 = &PTR_FUN_00d74894; // set vtable at offset 0
        puVar2[0x60] = 0; // clear field at offset 0x180 (0x60 * 4)
        puVar2[0x61] = 0; // clear field at offset 0x184
    }
    // call some registration/init function with a member at offset 0x38
    puVar1 = FUN_00848c30(*(undefined4*)(this + 0x38));
    *(undefined4*)(this + 0x38) = puVar1;
    if (puVar2 != (undefined4*)0x0) {
        return puVar2 + 4; // return pointer to object start +4
    }
    return (undefined4*)0x0;
}