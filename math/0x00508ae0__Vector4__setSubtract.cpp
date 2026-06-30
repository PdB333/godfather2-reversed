// FUNC_NAME: Vector4::setSubtract
// Address: 0x00508ae0
// Role: Subtracts two 4D vectors component-wise (only xyz, preserves w).
// Called via __thiscall (this in ECX, a in EDX, b on stack).
// Original decompile: __fastcall with three parameters, but reinterpreted as member function.

void __thiscall Vector4::setSubtract(const Vector4& a, const Vector4& b)
{
    // Preserve the w component (unchanged by subtraction)
    float w = this->w;

    // Subtract x, y, z components
    this->x = a.x - b.x;
    this->y = a.y - b.y;
    this->z = a.z - b.z;

    // Restore w
    this->w = w;
}