// FUNC_NAME: Quaternion::lerp
// Address: 0x00844400
// Performs: out = start + t * this (linear interpolation of four floats, e.g., quaternion or vector4)
void __thiscall Quaternion::lerp(float* this, float* start, float t, float* out) {
    // this:      +0x00 = x, +0x04 = y, +0x08 = z, +0x0C = w
    // start:     +0x00 = x, +0x04 = y, +0x08 = z, +0x0C = w
    // out:       +0x00 = x, +0x04 = y, +0x08 = z, +0x0C = w
    out[0] = t * this[0] + start[0];
    out[1] = t * this[1] + start[1];
    out[2] = t * this[2] + start[2];
    out[3] = t * this[3] + start[3];
}