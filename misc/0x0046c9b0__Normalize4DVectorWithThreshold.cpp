// FUNC_NAME: Normalize4DVectorWithThreshold
// Function at 0x0046c9b0: Normalizes a 4-component vector (quaternion or homogeneous) using a threshold and scaling factor.
// Input vector passed via EAX (in), output stored to param_1 (out, ECX).
// If squared magnitude <= threshold (DAT_00e2cbe0), output is set to zero.
// Otherwise, scale factor = DAT_00e2b1a4 / sqrt(squared magnitude).
#include <cmath>

extern float DAT_00e2cbe0; // Threshold for squared magnitude (if <=, set zero)
extern float DAT_00e2b1a4; // Scaling constant for normalization

void __fastcall Normalize4DVectorWithThreshold(float* out, const float* in)
{
    float magnitudeSq = in[0] * in[0] + in[1] * in[1] + in[2] * in[2] + in[3] * in[3];
    float scale;
    if (magnitudeSq <= DAT_00e2cbe0) {
        scale = 0.0f;
    } else {
        scale = DAT_00e2b1a4 / std::sqrt(magnitudeSq);
    }
    out[0] = in[0] * scale;
    out[1] = in[1] * scale;
    out[2] = in[2] * scale;
    out[3] = in[3] * scale;
}