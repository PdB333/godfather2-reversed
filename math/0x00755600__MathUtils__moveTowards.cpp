// FUNC_NAME: MathUtils::moveTowards
void moveTowards(float* in_pTarget, float* in_pSource, float* out_pResult)
{
    // Compute vector from target to source: source - target
    float diffX = in_pSource[0] - in_pTarget[0];
    float diffY = in_pSource[1] - in_pTarget[1];
    float diffZ = in_pSource[2] - in_pTarget[2];

    // Normalize the difference (direction from target toward source)
    normalizeVector3(&diffX);  // 0x0056afa0: normalizes in-place

    // Scale by fixed step size (global speed/factor)
    float step = DAT_00d5d7b8; // global constant

    // Move source in that direction by step, store result
    out_pResult[0] = diffX * step + in_pSource[0];
    out_pResult[1] = diffY * step + in_pSource[1];
    out_pResult[2] = diffZ * step + in_pSource[2];
}