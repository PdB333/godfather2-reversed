// FUNC_NAME: DualQuaternion::lerp
// Address: 0x00501a30
// Role: Performs linear interpolation (LERP) between two dual quaternions (8 floats).
// Dual quaternion consists of two quaternions: real (indices 0-3) and dual (indices 4-7).
// "this" is the target (to) dual quaternion.
// param_1 (from) is the source dual quaternion.
// param_2 (out) is the output dual quaternion.
// param_3 (t) is the interpolation factor [0,1].
void __thiscall DualQuaternion::lerp(const DualQuaternion& from, DualQuaternion& out, float t)
{
    // Interpolate real part (indices 0-3)
    out.data[0] = (data[0] - from.data[0]) * t + from.data[0];
    out.data[1] = (data[1] - from.data[1]) * t + from.data[1];
    out.data[2] = (data[2] - from.data[2]) * t + from.data[2];
    out.data[3] = (data[3] - from.data[3]) * t + from.data[3];
    // Interpolate dual part (indices 4-7)
    out.data[4] = (data[4] - from.data[4]) * t + from.data[4];
    out.data[5] = (data[5] - from.data[5]) * t + from.data[5];
    out.data[6] = (data[6] - from.data[6]) * t + from.data[6];
    out.data[7] = (data[7] - from.data[7]) * t + from.data[7];
}