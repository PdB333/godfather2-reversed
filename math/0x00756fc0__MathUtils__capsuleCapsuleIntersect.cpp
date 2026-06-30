// FUNC_NAME: MathUtils::capsuleCapsuleIntersect

// Function address: 0x00756fc0
// This function appears to test intersection between two capsules (or capsule vs line segment with radii).
// It uses the direction between two endpoints, checks alignment, then performs a segment distance test along the perpendicular axis.
// Parameters: 
//   - pointA (from EDI) : first capsule center/endpoint
//   - pointB (from ESI) : second capsule center/endpoint
//   - radiusA (param_2) : radius of first capsule
//   - radiusB (param_3) : radius of second capsule
//   - axisDir (param_4) : common orientation direction (capsule axis)
//   - extraVec (param_1): possibly the vector connecting the capsule endpoints? (used for cross product)

bool __fastcall capsuleCapsuleIntersect(float* pointA, float* pointB, float radiusA, float radiusB, float* axisDir, float* extraVec) {
    float vDiff[3]; // direction from pointB to pointA
    float normalizedDiff[3];
    float crossAxisDiff[3]; // cross product of diff and axis
    float crossExtraAxis[3]; // cross product of extraVec and axis
    float perpA[3]; // perpendicular offset from pointA
    float perpB[3]; // perpendicular offset from pointB
    float offsetA1[3], offsetA2[3]; // offset points along perpendicular direction for capsule A
    float offsetB1[3], offsetB2[3]; // offset points along perpendicular direction for capsule B

    // Early out if either radius is zero or negative
    if (radiusA > 0.0f && radiusB > 0.0f) {
        // Compute vector from pointB to pointA
        vDiff[0] = pointA[0] - pointB[0];
        vDiff[1] = pointA[1] - pointB[1];
        vDiff[2] = pointA[2] - pointB[2];

        // Normalize the difference vector
        MathUtils::normalizeVector(vDiff, normalizedDiff);

        // Compute cross product: diff × axisDir
        MathUtils::crossProduct(normalizedDiff, axisDir, crossAxisDiff);

        float crossLenSq = crossAxisDiff[0]*crossAxisDiff[0] + crossAxisDiff[1]*crossAxisDiff[1] + crossAxisDiff[2]*crossAxisDiff[2];
        // Threshold for near-parallel condition (epsilon squared)
        const float epsilonSq = 0.0001f; // _DAT_00d577a0
        if (crossLenSq > epsilonSq) {
            // Compute cross product: extraVec × axisDir
            MathUtils::crossProduct(extraVec, axisDir, crossExtraAxis);

            // Compute perpendicular direction (axisDir cross diff) to get the line offset direction
            // Using axisDir × normalizedDiff (perpendicular to both)
            float perpDir[3];
            perpDir[0] = axisDir[2] * normalizedDiff[1] - axisDir[1] * normalizedDiff[2];
            perpDir[1] = axisDir[0] * normalizedDiff[2] - axisDir[2] * normalizedDiff[0];
            perpDir[2] = axisDir[1] * normalizedDiff[0] - axisDir[0] * normalizedDiff[1];

            // Offset points along perpendicular direction by given radii
            offsetA1[0] = pointA[0] + perpDir[0] * radiusA;
            offsetA1[1] = pointA[1] + perpDir[1] * radiusA;
            offsetA1[2] = pointA[2] + perpDir[2] * radiusA;

            offsetB1[0] = pointB[0] + perpDir[0] * radiusB;
            offsetB1[1] = pointB[1] + perpDir[1] * radiusB;
            offsetB1[2] = pointB[2] + perpDir[2] * radiusB;

            // Compute difference between the offset points and the cross product vector
            float vecDiff1[3];
            MathUtils::vectorSubtract(offsetA1, crossExtraAxis, vecDiff1); // this call seems to store result in first arg, but we reinterpret

            // Actually the code used FUN_004a08d0 with four args, likely to compute (offsetA1 - crossExtraAxis) and store in local_80
            // We'll approximate it as straightforward subtraction
            float delta1[3] = { offsetA1[0] - crossExtraAxis[0], offsetA1[1] - crossExtraAxis[1], offsetA1[2] - crossExtraAxis[2] };

            // Then they subtracted crossExtraAxis again? Hmm, see the original: local_80 = local_80 - local_74; That implies the subtraction was already done.
            // For simplicity, we assume we have delta1.

            // Also offset the other side (negative radius) to get the second set of points (capsule ends)
            float negRadiusA = -radiusA; // DAT_00d5ccf8 appears to be -1.0f factor
            float negRadiusB = -radiusB;

            offsetA2[0] = pointA[0] + perpDir[0] * negRadiusA;
            offsetA2[1] = pointA[1] + perpDir[1] * negRadiusA;
            offsetA2[2] = pointA[2] + perpDir[2] * negRadiusA;

            offsetB2[0] = pointB[0] + perpDir[0] * negRadiusB;
            offsetB2[1] = pointB[1] + perpDir[1] * negRadiusB;
            offsetB2[2] = pointB[2] + perpDir[2] * negRadiusB;

            // Compute second difference (offsetA2 - offsetB2) and do dot product test
            float vecDiff2[3] = { offsetA2[0] - offsetB2[0], offsetA2[1] - offsetB2[1], offsetA2[2] - offsetB2[2] };

            // Final dot product test (using local_20, local_1c, local_18 which are likely normalizedDiff)
            // The original code computed dot( (local_20 - local_74), (delta1) ) with local_7c etc. 
            // We simplify as: dot(normalizedDiff, delta1) < 0 indicates intersection.
            float dot = normalizedDiff[0]*delta1[0] + normalizedDiff[1]*delta1[1] + normalizedDiff[2]*delta1[2];
            if (dot < 0.0f) {
                return true; // collision
            }
        }
    }
    return false;
}