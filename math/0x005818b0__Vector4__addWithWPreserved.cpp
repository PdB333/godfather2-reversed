// FUNC_NAME: Vector4::addWithWPreserved
// Function address: 0x005818b0
// Adds the first three components of two Vector4 objects and stores the result in 'this'.
// The fourth component (w) remains unchanged.
// __thiscall: this pointer in ECX, param1 in EDX, param2 on stack.

class Vector4 {
public:
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C

    void __thiscall addWithWPreserved(const Vector4* a, const Vector4* b) {
        // Save original w
        float originalW = this->w;

        // Add x, y, z components
        this->x = a->x + b->x;  // offset 0
        this->y = a->y + b->y;  // offset 4
        this->z = a->z + b->z;  // offset 8

        // Restore w (unchanged)
        this->w = originalW;
    }
};