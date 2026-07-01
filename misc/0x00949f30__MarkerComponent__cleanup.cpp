// FUNC_NAME: MarkerComponent::cleanup
void __thiscall MarkerComponent::cleanup(int this)
{
    // +0x11c: flags, bit 17 indicates marker active
    if ((*(uint *)(this + 0x11c) >> 0x11 & 1) != 0) {
        Scripting_RemoveMarker("RemoveMarker", 0, &DAT_00d8b2cc, 1, this + 8);
        *(uint *)(this + 0x11c) &= 0xfffdffff; // clear bit 17
    }
    System_CleanupA();  // FUN_005c0b00
    System_CleanupB();  // FUN_004df630
    // +0x210: pointer to subobject, +0x21c: vtable function (likely destructor)
    if (*(int *)(this + 0x210) != 0) {
        (**(code **)(this + 0x21c))(*(int *)(this + 0x210));
    }
    // +0x1d4: pointer to a structure; sets field at +8 to 0 then nulls pointer
    int *pStruct = *(int **)(this + 0x1d4);
    if (pStruct != 0) {
        *(undefined4 *)(pStruct + 8) = 0;
        *(int *)(this + 0x1d4) = 0;
    }
    // +0x1bc: another subobject with destructor vtable at +0x1c8
    if (*(int *)(this + 0x1bc) != 0) {
        (**(code **)(this + 0x1c8))(*(int *)(this + 0x1bc));
    }
    // +0x194: resource freed by deleteObject
    if (*(int *)(this + 0x194) != 0) {
        deleteObject(*(int *)(this + 0x194));
    }
    System_CleanupC();  // FUN_005c0a90
    // Three resource pointers released via releaseResource
    if (*(int *)(this + 0x168) != 0) {
        releaseResource(this + 0x168);
    }
    if (*(int *)(this + 0x15c) != 0) {
        releaseResource(this + 0x15c);
    }
    if (*(int *)(this + 0x154) != 0) {
        releaseResource(this + 0x154);
    }
}