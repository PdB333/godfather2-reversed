// FUNC_NAME: Rect2D::operator=
void __fastcall Rect2D::operator=(Rect2D *this, Rect2D *other)
{
    // Copy assignment operator for a 16-byte rectangle struct (14 bytes used + 2 padding)
    // Field offsets:
    // +0x00: int left
    // +0x04: int top
    // +0x08: int width
    // +0x0C: short layer (16-bit padding after)
    // Total: 4 + 4 + 4 + 2 = 14 bytes, padded to 16

    if (this != other) {
        this->left = other->left;   // copy dword at +0x00
        this->top = other->top;     // copy dword at +0x04
        this->layer = other->layer; // copy short at +0x0C
        this->width = other->width; // copy dword at +0x08
    }
}