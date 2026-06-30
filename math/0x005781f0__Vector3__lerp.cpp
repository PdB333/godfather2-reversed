// FUNC_NAME: Vector3::lerp
void Vector3::lerp(Vector3* result, float t)
{
    // Call to clamp or validate t (0.0 to 1.0)
    FUN_0056cc80(t);

    // Source vectors are in unaff_EDI (start) and unaff_ESI (end)
    // +0x10 = x, +0x14 = y, +0x18 = z, +0x1c = w (or unused)
    float startX = *(float*)(unaff_EDI + 0x10);
    float startY = *(float*)(unaff_EDI + 0x14);
    float startZ = *(float*)(unaff_EDI + 0x18);
    float endX = *(float*)(unaff_ESI + 0x10);
    float endY = *(float*)(unaff_ESI + 0x14);
    float endZ = *(float*)(unaff_ESI + 0x18);

    // Linear interpolation: result = start + (end - start) * t
    result->x = (endX - startX) * t + startX;
    result->y = (endY - startY) * t + startY;
    result->z = (endZ - startZ) * t + startZ;
}