// FUNC_NAME: VehicleBrain::clampSteeringResponse
long double __fastcall VehicleBrain::clampSteeringResponse(uint thisPtr)
{
    float fVar1;
    long double fVar2;
    long double fVar3;

    // Read input value from offset 0xc, likely m_steeringInput or m_currentAngle
    fVar1 = (float)FUN_0040f220(*(undefined4 *)(thisPtr + 0xc));
    fVar2 = (long double)FUN_0040f220((float)fVar1);

    if (fVar2 < 1.0L) {
        // Small magnitude: keep original value
        double dVar4 = (double)fVar1;
        FUN_00b9b988(); // Possibly some side-effect / debug log
        fVar3 = (float)dVar4;
    } else {
        fVar3 = 0.0L;
        if (fVar1 <= 0.0f) {
            // Negative large input: return a constant value
            return DAT_00e2afac + DAT_00e2afac; // 2 * kSomeGlobalConstant
        }
    }
    return fVar3 + fVar3; // 2 * (original or zero)
}