// FUNC_NAME: Quaternion::lerp
void __thiscall Quaternion::lerp(const float *target, float t, float *out) const {
    // Linear interpolation of a 4-component vector/quaternion.
    // this[0..3] = source, target[0..3] = destination, t = blend factor, out = result.
    float src_y = this[1];   // +0x04
    float src_z = this[2];   // +0x08
    float src_w = this[3];   // +0x0C
    float dst_y = target[1];
    float dst_z = target[2];
    float dst_w = target[3];
    out[0] = (target[0] - this[0]) * t + this[0];
    out[1] = (dst_y - src_y) * t + src_y;
    out[2] = (dst_z - src_z) * t + src_z;
    out[3] = (dst_w - src_w) * t + src_w;
}