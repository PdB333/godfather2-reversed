// FUNC_NAME: Quaternion::lerpAxisOnly
void __thiscall Quaternion::lerpAxisOnly(float *a, float *b, float t)
{
    // a and b are pointers to 4-component quaternions (x, y, z, w)
    // This function interpolates only the x, y, z components while preserving the original w (rotation angle)
    float aY = a[1];   // +0x04
    float aZ = a[2];   // +0x08
    float aW = a[3];   // +0x0C
    float originalW = this->w; // +0x0C

    float bY = b[1];   // +0x04
    float bZ = b[2];   // +0x08
    float bW = b[3];   // +0x0C

    // Lerp x, y, z
    this->x = t * a[0] + b[0]; // +0x00
    this->y = t * aY + bY;     // +0x04
    this->z = t * aZ + bZ;     // +0x08

    // Compute a temporary w but immediately discard it and restore the original
    this->w = t * aW + bW;
    this->w = originalW;       // preserve original w
}