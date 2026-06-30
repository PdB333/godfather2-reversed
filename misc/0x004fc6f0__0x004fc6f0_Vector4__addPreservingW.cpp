// FUNC_NAME: 0x004fc6f0 Vector4::addPreservingW
class Vector4 {
public:
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C

    // __thiscall: this in ECX, a in EDX, b on stack
    // Sums x,y,z from a and b into this, preserves this->w unchanged.
    void __fastcall add(const Vector4* a, const Vector4* b) {
        float savedW = w;          // fVar1 = in_EAX[3]
        x = a->x + b->x;           // *in_EAX = *param_2 + *param_3
        y = a->y + b->y;           // in_EAX[1] = fVar2 + fVar5
        z = a->z + b->z;           // in_EAX[2] = fVar3 + fVar6
        w = savedW;                // in_EAX[3] = fVar1
    }
};