// FUNC_NAME: someClass::computeSomeValue
int __fastcall someClass::computeSomeValue(int this)
{
    float fVar1;
    int iVar2;
    int iVar3;
    int result;

    iVar3 = 0;
    if (DAT_01223484 != 0) {
        iVar3 = *(int *)(DAT_01223484 + 0x394); // +0x394: some field
    }
    iVar2 = 0;
    if (DAT_01223484 != 0) {
        iVar2 = *(int *)(DAT_01223484 + 0x3a8); // +0x3a8: some other field
    }
    fVar1 = (float)(iVar2 * iVar3);
    if (iVar2 * iVar3 < 0) {
        fVar1 = fVar1 + DAT_00e44578; // adjust for rounding
    }
    result = (int)(longlong)ROUND(fVar1 * DAT_00d5ef84); // multiply by some constant
    return result * *(int *)(this + 0x11c); // +0x11c: multiplier field
}