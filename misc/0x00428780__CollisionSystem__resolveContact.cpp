// FUNC_NAME: CollisionSystem::resolveContact

void __thiscall CollisionSystem::resolveContact(float *positionA, float *positionB)
{
    float repulsionFactor = DAT_00e2cd54; // Global repulsion spring constant
    float overlapThreshold = DAT_00e2b1a4; // Global minimum separation threshold

    // Copy positionA (first 4 floats) into this object's storage (indices 0-3)
    this[0] = positionA[0];
    this[1] = positionA[1];
    this[2] = positionA[2];
    this[3] = positionA[3];

    // Copy positionB (first 4 floats) into this object's storage (indices 4-7)
    this[4] = positionB[0];
    this[5] = positionB[1];
    this[6] = positionB[2];
    this[7] = positionB[3];

    // X-axis separation check
    float deltaX = this[4] - this[0]; // positionB.x - positionA.x
    if (deltaX < overlapThreshold) {
        float push = (overlapThreshold - deltaX) * repulsionFactor;
        this[0] -= push; // Move A negative along x
        this[4] += push; // Move B positive along x
    }

    // Y-axis separation check
    float deltaY = this[5] - this[1]; // positionB.y - positionA.y
    if (deltaY < overlapThreshold) {
        float push = (overlapThreshold - deltaY) * repulsionFactor;
        this[1] -= push;
        this[5] += push;
    }

    // Z-axis separation check
    float deltaZ = this[6] - this[2]; // positionB.z - positionA.z
    if (deltaZ < overlapThreshold) {
        float push = (overlapThreshold - deltaZ) * repulsionFactor;
        this[2] -= push;
        this[6] += push;
    }

    // Compute and store the product of the three axis separations (after correction)
    // This is used as a measure of overlap volume or penalty
    this[8] = (this[6] - this[2]) * (this[5] - this[1]) * (this[4] - this[0]);
}