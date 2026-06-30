// FUNC_NAME: AptValue::isNull
bool AptValue::isNull(void)
{
    int *piVar1;
    code *pcVar2;
    uint uVar3;
    undefined4 uVar4;
    uint *this;
    int fs_offset;
    undefined *local_14;
    char *local_10;
    undefined4 local_c;
    int local_8;
    undefined1 *local_4;
    
    if (this != (uint *)0x0) goto LAB_0059ca9e;
    local_14 = &DAT_00e3b9b8;
    local_10 = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    local_c = 0x2d9;
    local_8 = 2;
    local_4 = &DAT_01128f16;
    if (DAT_01128f16 == '\0') goto LAB_0059ca9e;
    piVar1 = *(int **)(**(int **)(fs_offset + 0x2c) + 0x30);
    uVar3 = 1;
    if (piVar1 == (int *)0x0) {
LAB_0059ca7b:
        if ((uVar3 & 2) != 0) {
            *local_4 = 0;
        }
    }
    else {
        uVar3 = (**(code **)(*piVar1 + 8))(&local_14,&DAT_00e3b9b8);
        if (local_4 != (undefined1 *)0x0) goto LAB_0059ca7b;
    }
    if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
       (((uVar3 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
        pcVar2 = (code *)swi(3);
        uVar4 = (*pcVar2)();
        return uVar4;
    }
LAB_0059ca9e:
    // Check if the AptValue type is Null (0x12 = AptNull) and the reference count is 0
    if (((*this & 0x7fff) == 0x12) && ((~(byte)(*this >> 0xf) & 1) == 0)) {
        return 1;
    }
    return 0;
}