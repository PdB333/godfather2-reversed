// FUNC_NAME: EARSMath::Vector4::scaleFromPreservingW
// Address: 0x004eb210
// Role: Scales x,y,z components of this vector from a source vector, preserving the w component.
// Called via __thiscall, this in ECX, source vector pointer in EDX (param_2), scale factor in stack.
// The decompiler shows __fastcall but uses in_EAX as this; likely misidentified convention.

void __fastcall Vector4::scaleFromPreservingW(float *this, float *source, float scale) // this in EAX, source in EDX
{
    float sourceY = source[1];
    float sourceZ = source[2];
    float sourceW = source[3];
    float savedW = this[3]; // preserve this->w

    this[0] = scale * source[0]; // x
    this[1] = scale * sourceY;   // y
    this[2] = scale * sourceZ;   // z
    this[3] = scale * sourceW;   // temporary w (discarded)
    this[3] = savedW;           // restore w
    return;
}