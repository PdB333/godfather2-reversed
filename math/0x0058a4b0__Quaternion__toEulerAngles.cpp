// FUNC_NAME: Quaternion::toEulerAngles
void __thiscall Quaternion::toEulerAngles(float *pitch, float *yaw, float *roll)
{
    float w = this->mData[0];   // +0x00
    float z = this->mData[3];   // +0x0C  (quaternion has order w,x,y,z, so index 3 is z)
    float x = this->mData[1];   // +0x04
    float y = this->mData[2];   // +0x08

    float temp1 = z * w;                      // z*w
    float temp2 = y * x;                      // y*x
    float temp3 = (z * y + x * w) * kConstant1;  // (z*y + x*w) * C1
    double pitchComponent = (double)((y * w - z * x) * kConstant2); // (y*w - z*x) * C2

    // First call to a library function (likely atan2 or asin) – arguments passed via FPU stack
    FUN_00b9a9fa(temp2, temp1, x * x, w * w, temp3, (y * y + x * x) * kConstant1);

    float constant1 = kConstant1;
    *pitch = (float)pitchComponent;

    double yawComponent = (double)((temp2 + temp1) * constant1);
    FUN_00b9a9fa();     // Second call – probably adjusts FPU stack or computes yaw
    *yaw = (float)yawComponent;

    double rollComponent = (double)temp3;
    FUN_00b9a9fa();     // Third call – computes roll
    *roll = (float)rollComponent;
}