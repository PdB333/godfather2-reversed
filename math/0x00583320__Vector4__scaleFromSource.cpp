// FUNC_NAME: Vector4::scaleFromSource
// Function at 0x00583320: Scales a 4-component vector from a source by a factor, then fixes the w component to a global constant (likely 1.0 for homogeneous coordinates).
// Uses __fastcall with 'this' in ECX, source object pointer in EDX (param_2), scale factor on stack.
// The class has a float* data member at offset +0x8 (pointer to 4 floats: x, y, z, w).
// Global constant DAT_00e2b1a4 is used to override the w component after scaling.

void __fastcall Vector4::scaleFromSource(void *this, void *source, float scale)
{
    float *srcData = *(float **)((int)source + 8); // source->data
    float srcY = srcData[1];
    float srcZ = srcData[2];
    float srcW = srcData[3];

    float *dstData = *(float **)((int)this + 8); // this->data
    dstData[0] = scale * srcData[0]; // x
    dstData[1] = scale * srcY;       // y
    dstData[2] = scale * srcZ;       // z
    dstData[3] = scale * srcW;       // w

    // Override w component with a global constant (likely 1.0f for vector homogeneity or quaternion normalization)
    dstData[3] = DAT_00e2b1a4;
}