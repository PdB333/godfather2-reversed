// FUNC_NAME: Vec4::setXyzPreserveW
void __fastcall Vec4::setXyzPreserveW(undefined4 param_1, undefined4 *srcPtr)
{
    // This function is a member of a 16-byte (4 x 32-bit) structure, likely an aligned Vector4.
    // It copies the first three components (x, y, z) from source into this, leaving the fourth (w) unchanged.
    // The signature uses __fastcall, but 'this' is passed in EAX (not ECX) – either an optimization or custom convention.
    // param_1 (ECX) is unused.

    undefined4 originalW; // original w component of this
    undefined4 srcY, srcZ, srcW; // source components

    originalW = in_EAX[3];        // save this->w
    srcY = srcPtr[1];              // source y
    srcZ = srcPtr[2];              // source z
    srcW = srcPtr[3];              // source w (will be overwritten below)
    *in_EAX = *srcPtr;            // this->x = source.x
    in_EAX[1] = srcY;             // this->y = source.y
    in_EAX[2] = srcZ;             // this->z = source.z
    in_EAX[3] = srcW;             // temporarily set this->w = source.w
    in_EAX[3] = originalW;        // restore this->w (keep original w)
}