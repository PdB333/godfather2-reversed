// FUNC_NAME: AngleInterpolate
void AngleInterpolate(float* result, float t, float* from, float* to)
{
    float zDiff = to[2] - from[2]; // Z angle difference
    // Check if the wrapped Z difference exceeds a threshold (DAT_00e44630 likely a pointer to float threshold, e.g., 0.5 rad? But we treat as value)
    // The PTR_FUN_00e4462c is a pointer to a float, and DAT_00e44680 might be a mask (0x7FFFFFFF?) for magnitude.
    // We simplify: if (abs(wrappedZDiff) > thresholdZ)
    if (*(float*)PTR_FUN_00e4462c <= (float)((uint)(zDiff) & DAT_00e44680))
    {
        // Large angular difference in Z axis: fall back to quaternion slerp to avoid gimbal lock
        float quatFrom[4]; // +0x00: quaternion x, y, z, w
        float quatTo[4];   // +0x00: quaternion x, y, z, w
        float quatResult[4]; // +0x00: interpolated quaternion

        // Convert Euler angles (X, Y, Z order?) to quaternion
        FUN_0056d370(from[1], from[0], from[2], quatFrom); // Note: from[1] = Y, from[0] = X, from[2] = Z
        FUN_0056d370(to[1], to[0], to[2], quatTo);

        // Spherical linear interpolation (slerp)
        FUN_0056cc80(t, quatFrom, quatTo, quatResult, DAT_00e2e780); // DAT_00e2e780 likely a boolean (used for shortPath? or normalization)

        // Convert quaternion back to Euler angles
        FUN_0056d810(quatResult, &result[1], &result[0], &result[2]); // Extract Y, X, Z? Actually order: param1[1], param1[0], param1[2] – so Y, X, Z
        // result[3] remains unset? But in the else branch it's set to 0.0; here it might be left as is. From the else branch we set result[3]=0; so this path might have garbage in result[3].
        // However, the caller probably expects result[3] to be 0. Quaternion slerp path doesn't set it; consistent? Maybe it's unused.
        return;
    }

    // Small angular difference: use angle-aware linear interpolation
    float yDiff = to[1] - from[1]; // Y angle difference
    // Check if wrapped Y difference is small
    if ((float)((uint)(yDiff) & DAT_00e44680) <= DAT_00e2afac)
    {
        // Small Y difference: simple linear interpolation (no wrap)
        result[1] = yDiff * t + from[1];
    }
    else
    {
        // Large Y difference: need to handle angle wrap-around
        // DAT_00e2a848 likely is -PI or a specific offset (like 360 degrees in radians)
        // Based on the sign of from[1] relative to to[1], use an offset to take the shorter path.
        float offset = DAT_00e2a848;
        if (from[1] < to[1])
        {
            offset = DAT_00e44780; // likely +2PI or another offset
        }
        // Compute interpolated angle with wrap correction
        float angle = ((yDiff + offset) * t + from[1]); // unwrap and interpolate
        result[1] = (float)FUN_0056aee0(angle, DAT_00e2a848); // Normalize back to range (e.g., [-PI, PI])
    }

    // Interpolate X and Z axes linearly (no wrap needed)
    result[0] = (to[0] - from[0]) * t + from[0];
    result[2] = (zDiff) * t + from[2];
    result[3] = 0.0f; // Fourth component (e.g., w) set to 0 (likely unused or for homogenous coordinates)
}