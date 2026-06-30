// FUNC_NAME: Vector4f::add
// Function address: 0x006d4000
// Role: Adds two 4-component float vectors, stores result in a third (this + other -> result)
void __thiscall Vector4f::add(const float* otherVec, float* resultVec)
{
    // this vector components (in_EAX)
    float vx = this[0]; // +0x00
    float vy = this[1]; // +0x04
    float vz = this[2]; // +0x08
    float vw = this[3]; // +0x0C

    // other vector components (param_1)
    float ox = otherVec[0];
    float oy = otherVec[1];
    float oz = otherVec[2];
    float ow = otherVec[3];

    // sum stored to output (param_2)
    resultVec[0] = vx + ox;
    resultVec[1] = vy + oy;
    resultVec[2] = vz + oz;
    resultVec[3] = vw + ow;
}