// FUNC_NAME: RenderObject::setColor
// Function address: 0x008e79c0
// Sets an RGBA color (4 ints) stored at offset 0x180-0x18c.
// If the new color differs, the old resource pointer at offset 0x190 (if non-null) is freed via FUN_004daf90,
// then the new color values are copied in.

#include <cstddef>

class RenderObject {
public:
    void setColor(const int* color); // __thiscall

    // +0x180 : int color[4];  // RGBA (or similar 4-component integer value)
    // +0x190 : void* resourcePtr; // optional associated resource (e.g., texture) freed on color change
};

void __thiscall RenderObject::setColor(const int* color) {
    // Compare new color with current
    if (this->color[0] != color[0] ||
        this->color[1] != color[1] ||
        this->color[2] != color[2] ||
        this->color[3] != color[3]) {

        // Free existing resource if present
        if (this->resourcePtr != nullptr) {
            // FUN_004daf90 likely destroys/releases the object pointed to by resourcePtr
            FUN_004daf90(reinterpret_cast<undefined4*>(this->resourcePtr));
            this->resourcePtr = nullptr;
        }

        // Update color values
        this->color[0] = color[0];
        this->color[1] = color[1];
        this->color[2] = color[2];
        this->color[3] = color[3];
    }
}