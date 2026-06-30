// FUNC_NAME: MathUtils::buildHorizontalDirection
void MathUtils::buildHorizontalDirection(float angle, float* outVec) {
    double dAngle = (double)angle;
    // outVec layout: [0] = x, [1] = y, [2] = z (based on offset +0, +4, +8)
    outVec[1] = 0.0f; // y coordinate always zero for horizontal direction
    // FUN_00b99fcb likely cos: outVec[0] = cos(angle)
    outVec[0] = (float)cos(dAngle);
    // FUN_00b99e20 likely sin: outVec[2] = sin(angle)
    outVec[2] = (float)sin(dAngle);
}