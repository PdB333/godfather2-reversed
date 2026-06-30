// FUN_0045c4b0: distanceBetweenPoints
float distanceBetweenPoints(const float* pointA, const float* pointB) {
    // pointA[0] = x, pointA[1] = y, pointA[2] = z
    // pointB[0] = x, pointB[1] = y, pointB[2] = z
    float dx = pointA[0] - pointB[0];
    float dy = pointA[1] - pointB[1];
    float dz = pointA[2] - pointB[2];
    return sqrt(dx * dx + dy * dy + dz * dz);
}