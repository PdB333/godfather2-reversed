// FUNC_NAME: MathUtils::Vector3Normalize
// Address: 0x00574370
// Normalizes a 3D vector (src) to unit length, with a threshold to avoid division by zero.
// The result is stored in dst. Threshold and scale constants are global (likely 0.0f and 1.0f).

static const float kNormalizeEpsilon = DAT_00e2cbe0;  // threshold for zero-length
static const float kNormalizeScale   = DAT_00e2b1a4;  // typically 1.0f

void __fastcall Vector3Normalize(const float* src, float* dst)
{
    float sx = src[0];
    float sy = src[1];
    float sz = src[2];

    float lengthSq = sx * sx + sy * sy + sz * sz;
    float scale;

    if (lengthSq <= kNormalizeEpsilon) {
        scale = 0.0f;
    } else {
        scale = kNormalizeScale / sqrtf(lengthSq);
    }

    dst[0] = sx * scale;
    dst[1] = sy * scale;
    dst[2] = sz * scale;
}