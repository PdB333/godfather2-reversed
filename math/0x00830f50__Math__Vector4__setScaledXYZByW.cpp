// FUNC_NAME: Math::Vector4::setScaledXYZByW
void __thiscall setScaledXYZByW(int thisPtr, float* src) {
    float w = src[3];                     // source w component
    float x = src[0];                      // source x
    float y = src[1];                      // source y
    float z = src[2];                      // source z
    float origW = *(float*)(thisPtr + 0x2c); // preserve destination w

    // Scale xyzw by w, but only store xyz; w is overwritten and then restored
    *(float*)(thisPtr + 0x20) = w * x;    // offset 0x20: stored x
    *(float*)(thisPtr + 0x24) = w * y;    // offset 0x24: stored y
    *(float*)(thisPtr + 0x28) = w * z;    // offset 0x28: stored z
    *(float*)(thisPtr + 0x2c) = w * w;    // temporary write (scaled w)
    *(float*)(thisPtr + 0x2c) = origW;    // restore original w (offset 0x2c)
}