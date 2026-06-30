// FUNC_NAME: Vector4::multiplyWithWOverride
// Function address: 0x00582ef0
// Multiplies two 4-component vectors (component-wise) and stores the result in this,
// then overrides the fourth component (w) with a global constant (likely 1.0f).
// Each vector stores a pointer to float data at offset +0x08.

void __thiscall Vector4::multiplyWithWOverride(void* this, void* vecA, void* vecB) {
    // vecA: input vector A, at offset +0x08 is a float* to its data
    float* aData = *(float**)((char*)vecA + 8);
    float aX = aData[0];
    float aY = aData[1];
    float aZ = aData[2];
    float aW = aData[3];

    // vecB: input vector B
    float* bData = *(float**)((char*)vecB + 8);
    float bX = bData[0];
    float bY = bData[1];
    float bZ = bData[2];
    float bW = bData[3];

    // this object's data pointer at +0x08
    float* outData = *(float**)((char*)this + 8);
    outData[0] = aX * bX; // x component
    outData[1] = aY * bY; // y component
    outData[2] = aZ * bZ; // z component
    outData[3] = g_wOverride; // w component overwritten (global constant at 0x00e2b1a4, likely 1.0f)
}