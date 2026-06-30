// FUNC_NAME: setVector2Property
void setVector2Property(void* unused, uint elementIndex, float* newValues)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float* targetArray;
    uint uVar6;

    if (elementIndex != 0) {
        uVar6 = elementIndex & 0xff;
        if ((elementIndex & 0x80000000) == 0) {
            targetArray = (float*)(&DAT_011d97f0 + uVar6 * 0x10);
        } else {
            targetArray = (float*)(&DAT_011ea8f0 + uVar6 * 0x10);
        }
        fVar1 = *newValues;
        fVar2 = *targetArray;
        if (fVar2 != fVar1) {
            *targetArray = fVar1;
        }
        fVar3 = newValues[1];
        fVar4 = targetArray[1];
        if (fVar4 != fVar3) {
            targetArray[1] = fVar3;
        }
        if (fVar4 != fVar3 || fVar2 != fVar1) {
            if ((elementIndex & 0x80000000) != 0) {
                // Callback for negative index (vtable offset 0x178)
                (**(code**)(*DAT_01205750 + 0x178))();
                return;
            }
            // Callback for positive index (vtable offset 0x1b4) with extra args
            (**(code**)(*DAT_01205750 + 0x1b4))(DAT_01205750, uVar6, targetArray, 1);
        }
    }
}