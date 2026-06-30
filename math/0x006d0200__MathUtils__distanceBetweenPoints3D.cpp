// FUNC_NAME: MathUtils::distanceBetweenPoints3D
float MathUtils::distanceBetweenPoints3D(float* pointA, float* pointB)
{
    float dx = pointA[0] - pointB[0]; // x component
    float dy = pointA[1] - pointB[1]; // y component
    float dz = pointA[2] - pointB[2]; // z component
    
    return sqrt(dx * dx + dy * dy + dz * dz);
}