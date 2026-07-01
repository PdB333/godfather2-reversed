// FUNC_NAME: UIRect::setRect
// Function at 0x008361e0: Sets four float components (likely rect bounds) from an array.
// The rect is stored at offsets +0x30 through +0x3c relative to the object base.
// Assumes the class has a base of at least 0x30 bytes before these fields.

struct UIRect {
    // ... preceding members ...
    float x;      // offset +0x30
    float y;      // offset +0x34
    float width;  // offset +0x38
    float height; // offset +0x3c
};

void __thiscall UIRect::setRect(UIRect* this, const float* rectData) {
    // Copy four floats from the input array to the object's rect fields
    this->x      = rectData[0];  // +0x30
    this->y      = rectData[1];  // +0x34
    this->width  = rectData[2];  // +0x38
    this->height = rectData[3];  // +0x3c
}