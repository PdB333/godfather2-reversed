// FUNC_NAME: MinimapMarker::updateIcon
void __thiscall MinimapMarker::updateIcon(int *this)
{
    int iVar1;
    char cVar2;
    undefined4 uVar3;
    int *piVar4;
    int iVar5;
    undefined4 uVar6;
    undefined4 local_8;
    int local_4;

    iVar1 = this[0x17]; // +0x5C: some ID or handle
    local_4 = 0;
    local_8 = 0;
    if (this[0x1c] == 0) { // +0x70: pointer to parent/manager
        piVar4 = (int *)0x0;
    } else {
        piVar4 = (int *)(this[0x1c] - 0x48); // adjust to get base of parent object
    }
    // Virtual call on parent's vtable at offset 0x1f8 (likely getState or getInfo)
    (**(code **)(*piVar4 + 0x1f8))(iVar1, &local_8);

    cVar2 = FUN_008754e0(&local_8); // check some condition on local_8
    if (cVar2 == '\0') {
        iVar5 = 0;
    } else {
        cVar2 = FUN_008754b0(&local_8); // another condition
        iVar5 = 2 - (uint)(cVar2 != '\0'); // map to 0,1,2
    }

    uVar6 = _DAT_00d5780c; // default color/texture global
    // Check if bit 10 of field at +0xAC is set and local_4 is 4,5,6 (but local_4 is always 0 here)
    if ((((uint)this[0x2b] >> 10 & 1) != 0) &&
       (((local_4 == 4 || (local_4 == 5)) || (local_4 == 6)))) {
        uVar6 = DAT_00d681ac; // alternate color/texture
    }

    // Look up texture from a 2D array indexed by iVar5 and local_4
    uVar3 = FUN_00875af0(iVar1, *(undefined4 *)(&DAT_00d681b0 + iVar5 * 4 + local_4 * 0xc));

    FUN_00460300(uVar6); // set color or play sound?

    // Virtual call on this object at offset 0x2c (likely setTexture or render)
    (**(code **)(*this + 0x2c))(uVar3, 1, 1, 0, 0x3f800000, 0x3f800000); // 1.0f, 1.0f

    return;
}