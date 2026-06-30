// FUNC_NAME: Math::lerpQuat
void __fastcall Math::lerpQuat(float *result, float *a, float *b, float t)
{
    // Interpolate quaternion components: result = a * t + b
    // Quaternion has 4 components (w, x, y, z or x, y, z, w)
    result[0] = t * a[0] + b[0];
    result[1] = t * a[1] + b[1];
    result[2] = t * a[2] + b[2];
    result[3] = t * a[3] + b[3];
    // Preserve original result[3] value? Likely bug or intentional override
    result[3] = a[3]; // +0x0C: w component retained from source
}