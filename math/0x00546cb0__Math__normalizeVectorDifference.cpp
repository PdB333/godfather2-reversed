// FUNC_NAME: Math::normalizeVectorDifference
void __thiscall Math::normalizeVectorDifference(Vector4* outResult, const Vector4& subtract, float* outLength)
{
    // Copy the source vector (implicitly passed in EAX) to the output
    *outResult = *reinterpret_cast<const Vector4*>(this);
    
    // Compute difference: source - subtract
    outResult->x -= subtract.x;
    outResult->y -= subtract.y;
    outResult->z -= subtract.z;
    outResult->w -= subtract.w;
    
    float lenSq = outResult->x * outResult->x + outResult->y * outResult->y + outResult->z * outResult->z;
    float len = sqrtf(lenSq);  // FUN_00414a80 is likely sqrt
    
    // Normalize to a fixed length (constant from DAT_00e2b1a4, likely 1.0f)
    float scale = kNormalizedLength / len;
    outResult->x *= scale;
    outResult->y *= scale;
    outResult->z *= scale;
    outResult->w *= scale;
    
    *outLength = len;
    
    return;
}