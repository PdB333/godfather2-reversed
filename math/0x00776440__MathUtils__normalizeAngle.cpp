// FUNC_NAME: MathUtils::normalizeAngle
float MathUtils::normalizeAngle(float angle)
{
    float fVar1;
    float fVar2;
    
    // _DAT_00d5eee8 is likely 1/(2*PI) or similar conversion factor
    fVar2 = angle * _DAT_00d5eee8;
    
    // Bit manipulation to extract integer part (truncation toward zero)
    fVar1 = (float)(DAT_00e44648 | DAT_00e44564 & (uint)fVar2);
    fVar1 = (fVar2 + fVar1) - fVar1;
    
    // Subtract integer part * full circle (DAT_00d5d70c is 2*PI)
    angle = angle - (fVar1 - (float)(-(uint)((float)(DAT_00e44564 & (uint)fVar2) < fVar1 - fVar2)
                                    & _DAT_00d5780c)) * DAT_00d5d70c;
    
    // If result is still >= 2*PI, subtract one more full circle
    if (DAT_00d5eeec < angle) {
        angle = angle - DAT_00d5d70c;
    }
    
    return (float10)angle;
}