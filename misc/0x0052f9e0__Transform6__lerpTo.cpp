// FUNC_NAME: Transform6::lerpTo
// Function address: 0x0052f9e0
// Role: Linear interpolation of 6 floats (likely position + rotation) from current state to target with factor t

void __thiscall Transform6::lerpTo(const float* target, float t)
{
    // DAT_00e2b1a4 is a constant 1.0f used for the complement factor (1 - t)
    const float one = 1.0f;

    // Interpolate first 4 floats (e.g., position x,y,z and w or something)
    this->data[0] = (target[0] - this->data[0]) * t + this->data[0];
    this->data[1] = (target[1] - this->data[1]) * t + this->data[1];
    this->data[2] = (target[2] - this->data[2]) * t + this->data[2];
    this->data[3] = (target[3] - this->data[3]) * t + this->data[3];

    // Interpolate last 2 floats (e.g., rotation angles)
    this->data[4] = target[4] * t + this->data[4] * (one - t);
    this->data[5] = target[5] * t + this->data[5] * (one - t);
}