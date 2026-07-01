// FUNC_NAME: Math::pointInTriangle
bool Math::pointInTriangle(float *point, float *v0, float *v1, float *v2, int axisToIgnore)
{
    float fVar1, fVar2, fVar3, fVar4, fVar5, fVar6;
    float local_40[4]; // vector from point to v0
    float local_30[4]; // vector from point to v2
    float local_20[4]; // vector from point to v1

    // Copy point into local_30
    local_30[0] = point[0];
    local_30[1] = point[1];
    local_30[2] = point[2];

    // Compute vectors from point to each triangle vertex
    local_20[0] = local_30[0] - v1[0];
    local_20[1] = local_30[1] - v1[1];
    local_20[2] = local_30[2] - v1[2];

    local_40[0] = local_30[0] - v0[0];
    local_40[1] = local_30[1] - v0[1];
    local_40[2] = local_30[2] - v0[2];

    local_30[0] = local_30[0] - v2[0];
    local_30[1] = local_30[1] - v2[1];
    local_30[2] = local_30[2] - v2[2];

    // Zero out the axis to ignore (project onto 2D plane)
    local_20[axisToIgnore] = 0.0f;
    local_40[axisToIgnore] = 0.0f;
    local_30[axisToIgnore] = 0.0f;

    // Compute dot products for barycentric coordinate test
    fVar4 = local_20[0] * local_20[0] + local_20[1] * local_20[1] + local_20[2] * local_20[2]; // dot(v1, v1)
    fVar2 = local_40[0] * local_20[0] + local_40[1] * local_20[1] + local_40[2] * local_20[2]; // dot(v0, v1)
    fVar3 = local_30[0] * local_20[0] + local_30[1] * local_20[1] + local_30[2] * local_20[2]; // dot(v2, v1)
    fVar1 = local_40[0] * local_40[0] + local_40[1] * local_40[1] + local_40[2] * local_40[2]; // dot(v0, v0)
    fVar5 = local_30[0] * local_40[0] + local_30[1] * local_40[1] + local_30[2] * local_40[2]; // dot(v2, v0)

    // Barycentric coordinate computation
    fVar6 = fVar1 * fVar4 - fVar2 * fVar2; // denominator
    fVar1 = fVar1 * fVar3 - fVar5 * fVar2; // barycentric u * denominator
    fVar2 = fVar5 * fVar4 - fVar3 * fVar2; // barycentric v * denominator

    // Check if point is inside triangle using barycentric coordinates
    if (((0.0f < fVar1 * fVar6) && (0.0f < fVar2 * fVar6)) &&
        (fVar2 + fVar1 <= fVar6)) {
        return true;
    }
    return false;
}