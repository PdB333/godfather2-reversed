// FUNC_NAME: MathUtils::clampedCosineProjected
float clampedCosineProjected(const float* fromPoint, const float* toPoint, const float* direction, const float* otherPoint) {
    // Constants retrieved from global data (likely -1.0, 1.0, 0.0)
    const float kLowerBound = -1.0f;           // replaces DAT_00e2b1a4 = -1.0
    const float kUpperBound = 1.0f;            // replaces DAT_00e2eff4 = 1.0
    const float kZeroEpsilon = 0.0f;           // replaces DAT_00e2b05c = 0.0

    // Vector from 'fromPoint' to 'toPoint'
    float v1[3];
    v1[0] = toPoint[0] - fromPoint[0];
    v1[1] = toPoint[1] - fromPoint[1];
    v1[2] = toPoint[2] - fromPoint[2];

    // Dot product of v1 with the direction vector
    float t1 = direction[0] * v1[0] + direction[1] * v1[1] + direction[2] * v1[2];

    // Project v1 onto the direction (scaling factor from global)
    float projection1 = t1 * kUpperBound;  // kUpperBound likely = 1.0 -> simple projection

    // Compute transformed vector u1 = v1 + projection1 * direction
    float u1[3];
    u1[0] = v1[0] + projection1 * direction[0];
    u1[1] = v1[1] + projection1 * direction[1];
    u1[2] = v1[2] + projection1 * direction[2];

    // Compute transformed vector for otherPoint (treat it as another point/direction)
    float t2 = direction[0] * otherPoint[0] + direction[1] * otherPoint[1] + direction[2] * otherPoint[2];
    float projection2 = t2 * kUpperBound;

    float u2[3];
    u2[0] = otherPoint[0] + projection2 * direction[0];
    u2[1] = otherPoint[1] + projection2 * direction[1];
    u2[2] = otherPoint[2] + projection2 * direction[2];

    // Compute lengths and dot product between u1 and u2
    float len1 = sqrt(u1[0]*u1[0] + u1[1]*u1[1] + u1[2]*u1[2]);
    float len2 = sqrt(u2[0]*u2[0] + u2[1]*u2[1] + u2[2]*u2[2]);
    float product = len1 * len2;

    // Cosine of angle between u1 and u2
    float cosine = kLowerBound;               // default if product is zero
    if (product != kZeroEpsilon) {
        float dot = u1[0]*u2[0] + u1[1]*u2[1] + u1[2]*u2[2];
        cosine = dot / product;

        // Clamp cosine to [kLowerBound, kUpperBound]
        if (cosine < kLowerBound) {
            cosine = kLowerBound;
        } else if (cosine > kUpperBound) {
            cosine = kUpperBound;
        }
    }

    return cosine;
}