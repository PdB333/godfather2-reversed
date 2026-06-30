// FUNC_NAME: GameObject::destroy
void __thiscall GameObject::destroy(GameObject *this) {
    int iVar1;
    int *piVar2;

    // Set vtable to base class (or active state)
    this->vtable = &PTR_FUN_00e31680;
    this->vtable2 = &PTR_LAB_00e31684;  // secondary vtable at +0x04

    iVar1 = this->field_0x68;  // +0x68 (offset 0x1a)
    if (iVar1 != 0) {
        // Remove object from a linked list or memory pool at global offset
        piVar2 = (int *)(DAT_01206880 + 0x14);
        **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01123be8;
        *piVar2 = *piVar2 + 4;
        *(int *)*piVar2 = iVar1;
        *piVar2 = *piVar2 + 4;
        this->field_0x68 = 0;   // +0x68
        this->field_0x6c = 0;   // +0x6c
    }

    FUN_00450e00();                     // Global cleanup routine
    FUN_009c8f10(this->field_0x58);     // Release sub-object at +0x58
    FUN_0049c640();                     // Another cleanup

    // Set vtable to destroyed state
    this->vtable = &PTR_LAB_00e31690;

    // Clear global flag
    DAT_012233a4 = 0;
}