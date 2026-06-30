// FUNC_NAME: Transform::applyLocalOffset
// Address: 0x00582c70
// Role: Applies the local translation and optional rotation composition from this transform to a source transform (quaternion + translation). 
//   If this transform's rotation is identity (qw == 1.0f), the source rotation is copied unchanged; otherwise a conversion function is called.
//   The translation component is added to the source translation, and the 4th translation component (w) is preserved.
// Structure:
//   this +0x0C : w-component of quaternion (rotation identity check)
//   this +0x10 : translation X
//   this +0x14 : translation Y
//   this +0x18 : translation Z
//   this +0x1C : translation W (scale? - not used)

void __thiscall Transform::applyLocalOffset(const float* src, float* dst) {
    // Global constant - likely 1.0f representing identity quaternion w
    const float IDENTITY_QW = DAT_00e2b1a4; // value unknown, assumed 1.0f

    if (*(reinterpret_cast<const float*>(this) + 0x0C) == IDENTITY_QW) {
        // Rotation is identity: copy source rotation directly
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
    } else {
        // Non-identity rotation: convert / combine (likely quaternion multiplication)
        FUN_0056cba0(); // unknown helper
    }

    // Add this transform's translation to source translation
    dst[4] = src[4] + reinterpret_cast<const float*>(this)[0x10];  // translation X
    dst[5] = src[5] + reinterpret_cast<const float*>(this)[0x14];  // translation Y
    dst[6] = src[6] + reinterpret_cast<const float*>(this)[0x18];  // translation Z
    // dst[7] is left unchanged (preserves homogeneous w-component)
}