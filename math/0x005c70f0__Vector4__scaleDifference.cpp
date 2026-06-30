// FUNC_NAME: Vector4::scaleDifference
// Address: 0x005c70f0
// Computes component-wise scaled difference: out[i] = (this[i] - other[i]) * gScale[i]
// Assumes this, other, out are pointers to 4-float arrays.
// Globals represent per-component scaling factors (likely from data or config).
void __thiscall Vector4::scaleDifference(float *other, float *out)
{
    // this (in_EAX) points to the object's internal float array (4 components)
    // Use local constants for readability
    const float scaleX = _DAT_00e3eb50; // +0x00 scaling factor for X
    const float scaleY = _UNK_00e3eb54; // +0x04 scaling factor for Y
    const float scaleZ = _UNK_00e3eb58; // +0x08 scaling factor for Z
    const float scaleW = _UNK_00e3eb5c; // +0x0C scaling factor for W

    // Compute scaled differences
    out[0] = (this[0] - other[0]) * scaleX;
    out[1] = (this[1] - other[1]) * scaleY;
    out[2] = (this[2] - other[2]) * scaleZ;
    out[3] = (this[3] - other[3]) * scaleW;
}