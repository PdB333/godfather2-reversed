// FUNC_NAME: Vector4::lerp

void __thiscall Vector4::lerp(float *this, Vector4 *to, float t, Vector4 *out)
{
    float src_x, src_y, src_z, src_w;
    float dst_x, dst_y, dst_z, dst_w;

    // Load source components (this is the 'from' vector)
    src_x = this[0]; // +0x00
    src_y = this[1]; // +0x04
    src_z = this[2]; // +0x08
    src_w = this[3]; // +0x0C

    // Load destination components
    dst_x = to[0];  // +0x00
    dst_y = to[1];  // +0x04
    dst_z = to[2];  // +0x08
    dst_w = to[3];  // +0x0C

    // out = src * (1 - t) + dst * t
    out[0] = (dst_x - src_x) * t + src_x;
    out[1] = (dst_y - src_y) * t + src_y;
    out[2] = (dst_z - src_z) * t + src_z;
    out[3] = (dst_w - src_w) * t + src_w;
}