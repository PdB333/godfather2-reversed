// FUNC_NAME: MathUtils::cosDegrees
// Function at 0x004174a0: Wrapper around fcos (extended precision cosine), likely converts degrees to radians internally if needed
// Note: param_1 is a float (angle), returns an unkbyte10 (extended precision float)

unkbyte10 MathUtils::cosDegrees(float angle)
{
    return fcos((float10)angle);
}