// FUNC_NAME: MathUtils::clampVectorLength
void MathUtils::clampVectorLength(float *vecX, float *vecY)
{
    float *tempPtr;
    float length;
    float clampedLength;
    double dVar5;
    float angle;
    
    tempPtr = vecY;
    length = *vecY;
    vecY = (float *)SQRT(*vecX * *vecX + length * length);
    clampedLength = 0.0;
    if (((float)vecY <= 0.0) || (clampedLength = _DAT_00d5780c, _DAT_00d5780c <= (float)vecY)) {
        vecY = (float *)clampedLength;
    }
    dVar5 = (double)length;
    FUN_00b9a9fa(); // likely atan2 setup
    angle = (float)dVar5;
    FUN_0056aee0(angle, DAT_00d5f00c); // likely atan2
    FUN_00b99e20(); // likely cos
    *vecX = (float)dVar5 * (float)((float10)(float)vecY / (float10)fcos(FUN_0056aee0_result));
    dVar5 = (double)angle;
    FUN_00b99fcb(); // likely sin
    *tempPtr = (float)dVar5 * (float)((float10)(float)vecY / (float10)fcos(FUN_0056aee0_result));
    return;
}