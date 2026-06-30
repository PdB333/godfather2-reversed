// FUNC_NAME: MathUtils::computeDistanceBetweenPoints
double MathUtils::computeDistanceBetweenPoints(void* obj)
{
    // obj points to a structure containing two 3D position vectors
    // First vector at offset +0x20, second at offset +0x30 (each: x, y, z as 4-byte floats)
    float* pointA = (float*)((unsigned char*)obj + 0x20);
    float* pointB = (float*)((unsigned char*)obj + 0x30);

    double dx = (double)pointA[0] - (double)pointB[0];
    double dy = (double)pointA[1] - (double)pointB[1];
    double dz = (double)pointA[2] - (double)pointB[2];

    return sqrt(dx * dx + dy * dy + dz * dz);
}