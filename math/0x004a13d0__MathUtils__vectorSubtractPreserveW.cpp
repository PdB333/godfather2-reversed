// FUNC_NAME: MathUtils::vectorSubtractPreserveW
// Address: 0x004a13d0
// Performs 3-component vector subtraction (a - b) and writes to dest, preserving the fourth component (w) of dest unchanged.
// Typically used for position vectors where w is a homogeneous coordinate that should not be modified by subtraction.

void __fastcall vectorSubtractPreserveW(float* dest, const float* a, const float* b) {
    // dest is passed in EAX (implicit this in __fastcall), a in EDX, b on stack (param_3)
    // Context: 4-float vectors, only x,y,z are subtracted; w is left untouched.

    float ax = a[0], ay = a[1], az = a[2];
    float bx = b[0], by = b[1], bz = b[2];
    float originalW = dest[3]; // preserve dest's w component

    dest[0] = ax - bx;
    dest[1] = ay - by;
    dest[2] = az - bz;
    dest[3] = originalW; // restore w (must not be changed)
}