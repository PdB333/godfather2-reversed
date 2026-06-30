// FUNC_NAME: SpatialUtility::determineRelativeOrientation

// Function at 0x0075ced0: Determines relative spatial relationship between two world points with respect to a reference transform.
// Returns one of four orientation codes (1,2,3,4) indicating front/back/left/right quadrant based on dot products.

// Assumes: FUN_00471610 returns pointer to a global transform/entity.
// Assumes: FUN_004a07f0 transforms a vector from world space to local space using an orientation matrix stored at (entity+0x10).
// Assumes: FUN_0056afa0 normalizes a 3D vector in place.

int SpatialUtility::determineRelativeOrientation(float* pointA, float* pointB)
{
    // Get pointer to reference entity transform (e.g., player or camera).
    int entityTransform = FUN_00471610();  // returns ptr to some entity
    float* orientationBasis = (float*)(entityTransform + 0x10);  // +0x10: likely forward direction or part of rotation matrix

    // Get a second reference entity? (maybe re-fetching the same, but used for position offsets)
    int entityPos = FUN_00471610();
    float* refPos = (float*)(entityPos + 0x30);  // +0x30: world position (x, y, z)

    // Vector from refPos to pointA (second parameter originally param_3)
    float vecA[3];
    vecA[0] = pointA[0] - refPos[0];
    vecA[1] = pointA[1] - refPos[1];
    vecA[2] = pointA[2] - refPos[2];

    // Transform vecA into local space using orientationBasis matrix
    float localVecA[3];
    FUN_004a07f0(localVecA, vecA, orientationBasis);  // likely inverse rotation

    // Normalize localVecA
    FUN_0056afa0(localVecA, localVecA);
    float normA[3] = { localVecA[0], localVecA[1], localVecA[2] };

    // Vector from refPos to pointB (first parameter originally param_2)
    float vecB[3];
    vecB[0] = pointB[0] - refPos[0];
    vecB[1] = pointB[1] - refPos[1];
    vecB[2] = pointB[2] - refPos[2];

    // Transform vecB into local space
    float localVecB[3];
    FUN_004a07f0(localVecB, vecB, orientationBasis);

    // Normalize localVecB
    FUN_0056afa0(localVecB, localVecB);
    float normB[3] = { localVecB[0], localVecB[1], localVecB[2] };

    // Extract forward vector from orientation basis (first column? depends on layout)
    // Assume orientationBasis[0] = forward.x, orientationBasis[1] = forward.y, orientationBasis[2] = forward.z? Actually offsets: +0x10, +0x14, +0x18 are used as a vector.
    float forward[3] = { orientationBasis[0], *(float*)(entityTransform + 0x14), *(float*)(entityTransform + 0x18) };

    // Compute cross product: forward × normA -> perp
    float perp[3];
    perp[0] = forward[1] * normA[2] - forward[2] * normA[1];
    perp[1] = forward[2] * normA[0] - forward[0] * normA[2];
    perp[2] = forward[0] * normA[1] - forward[1] * normA[0];

    // Normalize perp
    FUN_0056afa0(perp, perp);

    // Compute dot products for classification
    float dotANormB = normA[0] * normB[0] + normA[1] * normB[1] + normA[2] * normB[2];  // signs: first dot product
    float dotPerpNormB = perp[0] * normB[0] + perp[1] * normB[1] + perp[2] * normB[2];    // signs: second dot product

    // Return quadrant classification
    if (dotANormB <= 0.0f)
    {
        // Behind the direction of normA? Or relative to forward?
        if (dotPerpNormB <= 0.0f)
            return 4;  // behind-left?
        else
            return 3;  // behind-right?
    }
    else
    {
        if (dotPerpNormB > 0.0f)
            return 2;  // front-right?
        else
            return 1;  // front-left?
    }
}