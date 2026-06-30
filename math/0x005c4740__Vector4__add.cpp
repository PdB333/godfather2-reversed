// FUNC_NAME: Vector4::add
// Function at 0x005c4740: Adds two 4-component vectors.
// Takes 'this' as first operand (in EAX), param_1 as second operand, stores result in param_2.
// All vectors are stored as arrays of 4 floats.

void __thiscall Vector4::add(float* this, float* other, float* outResult)
{
    // Load components from this
    float thisX = this[0];
    float thisY = this[1];
    float thisZ = this[2];
    float thisW = this[3];

    // Load components from other
    float otherX = other[0];
    float otherY = other[1];
    float otherZ = other[2];
    float otherW = other[3];

    // Compute sum
    outResult[0] = thisX + otherX;
    outResult[1] = thisY + otherY;
    outResult[2] = thisZ + otherZ;
    outResult[3] = thisW + otherW;

    return;
}