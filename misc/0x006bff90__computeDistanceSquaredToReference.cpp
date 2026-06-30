// FUNC_NAME: computeDistanceSquaredToReference
float computeDistanceSquaredToReference(float* vecIn) {
    float refX;  // local_c
    float refY;  // local_8
    float refZ;  // local_4

    // Get reference position (e.g., camera, player, or some origin point)
    getReferencePosition(&refX, 0);  // 0 might indicate which reference (camera, etc.)

    // Compute squared Euclidean distance between vecIn and reference position
    float dx = vecIn[0] - refX;
    float dy = vecIn[1] - refY;
    float dz = vecIn[2] - refZ;
    return dx * dx + dy * dy + dz * dz;
}