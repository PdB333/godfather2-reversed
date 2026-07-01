// FUNC_NAME: SomeClass::evaluateProbability
undefined4 __thiscall SomeClass::evaluateProbability(int *this, undefined4 *outResult, float *outFloat, undefined1 *outFlag, float valueA, float valueB)
{
    bool bVar1;
    double fVar2;
    float fVar3;
    float diff;

    diff = valueA - valueB;
    if (DAT_00d5eee4 <= diff) {
        // Call virtual function at vtable+0x1b8 (likely random number generator)
        fVar2 = (double)(*(code **)(*this + 0x1b8))();
        fVar3 = (float)(fVar2 / (double)diff);
        if (fVar2 / (double)diff < (double)DAT_00d5f378) {
            return 0;
        }
    }
    else {
        fVar3 = DAT_00d5f378;
        if ((diff < _DAT_00d5780c) && (fVar3 = DAT_00d5efd0, diff < _DAT_00d5c458)) {
            *outFlag = 1;
            fVar3 = DAT_00d5efd0;
        }
    }
    bVar1 = fVar3 < DAT_00d5efd0;
    *outResult = 0;
    if (bVar1) {
        return 1;
    }
    *outFloat = _DAT_00d5780c;
    return 1;
}