// FUNC_NAME: Math::Vector4::fromVector3AndDefaultW
void __fastcall Math::Vector4::fromVector3AndDefaultW(Math::Vector4 *this, Math::Vector3 *src)
{
    // Equivalent to: Vector4 out = {src->x, src->y, src->z, defaultW};
    // +0x00: x, +0x04: y, +0x08: z, +0x0C: w
    *this->x = src->x;       // local_20 = *src
    *this->y = src->y;       // local_1c = src[1]
    *this->z = src->z;       // local_18 = src[2]
    this->w = DAT_00e2b1a4;  // default W component (likely 1.0f for points, 0.0f for vectors)
    FUN_005e7440(this);      // further initialization (e.g., normalize? or build matrix?)
}