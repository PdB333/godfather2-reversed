// FUNC_NAME: SomeClass::someMethod
int __fastcall SomeClass::someMethod(int this)
{
    int iVar1;
    undefined4 uVar2;

    iVar1 = *(int *)(this + 0x58); // +0x58: pointer to some sub-object
    if ((iVar1 != 0) && (iVar1 = iVar1 + -0x48, iVar1 != 0)) {
        uVar2 = FUN_009a8830(*(undefined4 *)(this + 0x50), this + 0x6c, this + 0x78, 0x3f800000); // 0x3f800000 = 1.0f
        *(undefined4 *)(this + 0x90) = uVar2; // +0x90: store result
        iVar1 = *(int *)(this + 0x58);
        if (iVar1 != 0) {
            *(char *)(iVar1 + 0x19c) = *(char *)(iVar1 + 0x19c) + 1; // +0x19c: increment counter
            return iVar1 + -0x48;
        }
        iVar1 = 0;
        cRam000001e4 = cRam000001e4 + 1; // global counter increment
    }
    return iVar1;
}