// FUNC_NAME: Vector4::subtract
void __thiscall Vector4::subtract(float *this, float *other, float *result)
{
    // Subtract two 4-component vectors: result = this - other
    // this is passed in EAX (in_EAX), other is param_1, result is param_2
    float thisX = this[1]; // +0x04
    float thisY = this[2]; // +0x08
    float thisZ = this[3]; // +0x0C
    float otherX = other[1]; // +0x04
    float otherY = other[2]; // +0x08
    float otherZ = other[3]; // +0x0C
    
    *result = *this - *other;           // result.x = this.x - other.x
    result[1] = thisX - otherX;         // result.y = this.y - other.y
    result[2] = thisY - otherY;         // result.z = this.z - other.z
    result[3] = thisZ - otherZ;         // result.w = this.w - other.w
}