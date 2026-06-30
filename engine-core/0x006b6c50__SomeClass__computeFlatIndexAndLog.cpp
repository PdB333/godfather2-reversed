// FUNC_NAME: SomeClass::computeFlatIndexAndLog
void __thiscall SomeClass::computeFlatIndexAndLog(uint* this, undefined4 param2)
{
    uint index3 = this[3]; // +0x0C
    uint index2 = this[2]; // +0x08
    ulonglong temp1 = (ulonglong)this[0] * 0x21 + (ulonglong)this[1]; // (index0*33 + index1) as 64-bit
    // Multiply by 33: gives index0*1089 + index1*33
    ulonglong temp2 = __allmul(temp1, 0x21, 0);
    // Add index2, then multiply again by 33: yields index0*35937 + index1*1089 + index2*33
    int flatIndex = __allmul(temp2 + (ulonglong)index2, 0x21, 0);
    // Finally add index3
    flatIndex += index3;
    // Call debug/log function with flat index and extra parameter
    FUN_008142f0(2, flatIndex, param2, 1);
}