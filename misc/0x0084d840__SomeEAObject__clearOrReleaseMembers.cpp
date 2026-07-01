// FUNC_NAME: SomeEAObject::clearOrReleaseMembers
void __fastcall SomeEAObject::clearOrReleaseMembers(int this)
{
    // Release/re-set fields at +0x04 and +0x0C (likely pointers to allocated objects)
    if (*(int *)(this + 4) != 0) {
        FUN_004daf90((undefined4 *)(this + 4));  // deallocate or release
        *(undefined4 *)(this + 4) = 0;
    }
    if (*(int *)(this + 0xc) != 0) {
        FUN_004daf90((undefined4 *)(this + 0xc));
        *(undefined4 *)(this + 0xc) = 0;
    }
    // Zero out fields at offsets 0x14..0x44 (16 bytes of potentially Vec3 or two quaternions/positions)
    // +0x14, +0x18, +0x1C: position or translation (float x,y,z)
    *(undefined4 *)(this + 0x1c) = 0;  // z
    *(undefined4 *)(this + 0x18) = 0;  // y
    *(undefined4 *)(this + 0x14) = 0;  // x

    // +0x20, +0x24, +0x28: rotation or second vector (float pitch,yaw,roll or another xyz)
    *(undefined4 *)(this + 0x28) = 0;  // third component
    *(undefined4 *)(this + 0x24) = 0;  // second component
    *(undefined4 *)(this + 0x20) = 0;  // first component

    // +0x30..+0x40: scale or multiple floats (scaling/axis)
    *(undefined4 *)(this + 0x30) = 0;
    *(undefined4 *)(this + 0x34) = 0;
    *(undefined4 *)(this + 0x38) = 0;
    *(undefined4 *)(this + 0x3c) = 0;
    *(undefined4 *)(this + 0x40) = 0;

    // +0x2C: another zeroed field
    *(undefined4 *)(this + 0x2c) = 0;

    // Set flag at +0x44, bit 0 (might indicate "dirty" or "needs update")
    *(uint *)(this + 0x44) = *(uint *)(this + 0x44) | 1;
}