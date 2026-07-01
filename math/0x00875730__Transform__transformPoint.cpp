// FUNC_NAME: Transform::transformPoint
// Function address: 0x00875730
// Role: Transforms a local point to world space using a transform object and applies a camera offset correction.
// The transform object (this) contains a 4-component vector (likely position or matrix row).
// The function calls a helper to compute an offset, adds it to the input point, then stores the result with a vertical correction.

void __fastcall Transform::transformPoint(void* this, int someId, float localX, float localY, float localZ)
{
    // Read the first four floats from the transform object (this)
    float v0 = *(float*)this;          // +0x00
    float v1 = *(float*)((int)this + 4); // +0x04
    float v2 = *(float*)((int)this + 8); // +0x08
    float v3 = _DAT_00d5780c;          // Global constant (e.g., 1.0f or 0.0f)

    // Temporary vector for the computed offset
    float offsetX, offsetY, offsetZ;

    // Call helper function to compute offset from the transform's vector and someId
    // The helper likely performs a rotation or matrix multiplication
    FUN_0056b420(someId, &v0, &offsetX);

    // Compute world position by adding offset to local point
    float worldX = localX + offsetX;
    float worldY = localY + offsetY;
    float worldZ = localZ + offsetZ;

    // Store world position at output pointer (unaff_ESI)
    *(float*)(unaff_ESI) = worldX;
    *(float*)((int)unaff_ESI + 4) = worldY;
    *(float*)((int)unaff_ESI + 8) = worldZ;

    // Copy to second output pointer (unaff_EDI) with a vertical correction
    *(float*)(unaff_EDI) = worldX;
    *(float*)((int)unaff_EDI + 4) = worldY - _DAT_00d765e0; // Subtract camera height offset
    *(float*)((int)unaff_EDI + 8) = worldZ;
}