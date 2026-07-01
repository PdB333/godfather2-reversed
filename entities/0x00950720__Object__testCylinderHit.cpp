// FUNC_NAME: Object::testCylinderHit
// Function address: 0x00950720
// Role: Checks if a given point (pointX, pointZ, pointY) is inside a cylinder volume defined by the world matrix of an object referenced at this+0x17c. Returns 1 if inside and copies the world matrix to outMatrix, otherwise 0.

extern void __cdecl GetWorldMatrix(float* outMatrix); // FUN_004df780, retrieves world transform

int __thiscall Object::testCylinderHit(float pointX, float pointZ, float pointY, float radiusSquared, float* outMatrix) {
    if (*(int*)((char*)this + 0x17c) == 0) {
        return 0;
    }

    float localWorldMatrix[16];
    GetWorldMatrix(&localWorldMatrix[0]);

    float transX = localWorldMatrix[12]; // +0x30 of matrix
    float transY = localWorldMatrix[13]; // +0x34
    float transZ = localWorldMatrix[14]; // +0x38

    // Cylinder check: pointY must be below the object's Y, and horizontal distance squared <= radiusSquared
    if (pointY < transY) {
        float dx = transX - pointX;
        float dz = transZ - pointZ;
        float distSq = dx * dx + dz * dz;
        if (distSq <= radiusSquared) {
            // Copy the entire world matrix (16 floats) to output
            for (int i = 0; i < 16; ++i) {
                outMatrix[i] = localWorldMatrix[i];
            }
            return 1;
        }
    }
    return 0;
}