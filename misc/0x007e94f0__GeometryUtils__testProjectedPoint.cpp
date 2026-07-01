//FUNC_NAME: GeometryUtils::testProjectedPoint
bool GeometryUtils::testProjectedPoint(void* context, float* lineStart, float* lineEnd, float* referencePoint, 
                                       undefined4 param5, undefined4 param6, undefined4 param7)
{
    // Global constants (likely from game config or engine)
    // DAT_00e44564: some constant value (e.g., plane distance or height)
    // _DAT_00d6fda4: bias term for projection calculation
    float constant = DAT_00e44564; // +0x0
    float bias = _DAT_00d6fda4;    // +0x0

    // Compute direction vector from lineStart to lineEnd
    float dirX = lineEnd[0] - lineStart[0];
    float dirY = lineEnd[1] - lineStart[1];
    float dirZ = lineEnd[2] - lineStart[2];

    // Compute vector from referencePoint to (constant, constant, constant)
    float toConstX = constant - referencePoint[0];
    float toConstY = constant - referencePoint[1];
    float toConstZ = constant - referencePoint[2];

    // Dot product of direction and (constant - referencePoint) plus bias
    float t = dirX * toConstX + dirY * toConstY + dirZ * toConstZ + bias;

    // Compute projected point on line: lineStart + t * (constant - referencePoint)
    float projectedPoint[3];
    projectedPoint[0] = lineStart[0] + toConstX * t;
    projectedPoint[1] = lineStart[1] + toConstY * t;
    projectedPoint[2] = lineStart[2] + toConstZ * t;

    // Call inner function to test the projected point against the segment
    char result = FUN_007e92f0(context, lineStart, projectedPoint, referencePoint, 
                                param5, param6, param7);
    return result == '\0';
}