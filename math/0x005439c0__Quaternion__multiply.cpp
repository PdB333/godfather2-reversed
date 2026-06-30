// FUNC_NAME: Quaternion::multiply
// Address: 0x005439c0
// Role: Multiply two quaternions (stored as [x, y, z, w]) and store result in this.
struct Quaternion {
    float x, y, z, w;
};

void __thiscall Quaternion::multiply(const float* q1, const float* q2) {
    // Quaternion multiplication: result = q1 * q2
    // q1 and q2 are arrays of [x, y, z, w] order (vector part first, scalar last)
    float aX = q1[0], aY = q1[1], aZ = q1[2], aW = q1[3];
    float bX = q2[0], bY = q2[1], bZ = q2[2], bW = q2[3];

    // Vector part: aW * bVec + bW * aVec + cross(aVec, bVec)
    this->x = aW * bX + bW * aX + (aY * bZ - aZ * bY);
    this->y = aW * bY + bW * aY + (aZ * bX - aX * bZ);
    this->z = aW * bZ + bW * aZ + (aX * bY - aY * bX);

    // Scalar part: aW * bW - dot(aVec, bVec)
    this->w = aW * bW - (aX * bX + aY * bY + aZ * bZ);
}