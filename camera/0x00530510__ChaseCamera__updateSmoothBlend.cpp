// FUNC_NAME: ChaseCamera::updateSmoothBlend
void __fastcall ChaseCamera::updateSmoothBlend(const float* source)
{
    // Global smoothing factor (likely 1.0f for standard exponential smoothing)
    static const float kSmoothFactor = 1.0f; // DAT_00e2b1a4

    float srcY = source[1];
    float srcZ = source[2];
    float srcW = source[3];
    float denom = this->accumulatedTime + kSmoothFactor;  // +0x20
    float alpha = kSmoothFactor / denom;

    // Standard lerp for position/quaternion components (indices 0-3)
    this->x = (source[0] - this->x) * alpha + this->x;      // +0x00
    this->y = (srcY     - this->y) * alpha + this->y;       // +0x04
    this->z = (srcZ     - this->z) * alpha + this->z;       // +0x08
    this->w = (srcW     - this->w) * alpha + this->w;       // +0x0C

    // Special lerp for field-of-view/zoom (indices 4-5), using (kSmoothFactor - alpha) as the old factor
    this->fov  = source[4] * alpha + this->fov  * (kSmoothFactor - alpha); // +0x10
    this->zoom = source[5] * alpha + this->zoom * (kSmoothFactor - alpha); // +0x14

    // Accumulate the total elapsed time
    this->accumulatedTime = denom;  // +0x20
}