// FUNC_NAME: BoundingBox::operator=(BoundingBox&&)
// Address: 0x0082d200
// Role: Move assignment operator for BoundingBox (likely Havok hkAabb-like structure).
// Copies the 32-byte AABB data (hkVector4 min/max) at +0x60 and 20 bytes of additional state at +0x4c,
// then resets the source object to default state.

class BoundingBox {
public:
    // +0x4c: 5x int32 state fields (offset 0x4c..0x5c)
    int field_0x4c;   // +0x4c
    int field_0x50;   // +0x50
    int field_0x54;   // +0x54
    int field_0x58;   // +0x58
    int field_0x5c;   // +0x5c

    // +0x60..0x7F: 32 bytes representing AABB min/max (two hkVector4)
    // Using double for alignment (8 bytes each), but actual type likely float4.
    double min_x; // +0x60
    double min_y; // +0x68
    double min_z; // +0x70
    double pad1;  // +0x78 (or max_x??) – Assuming 8-byte doubles for simplicity.
    // In practice, these are hkVector4 with 4 floats (16 bytes each) but here stored as 8-byte chunks.
    // The exact layout is unknown; we copy as raw 8-byte values.

    // Move assignment operator
    BoundingBox& operator=(BoundingBox&& other) noexcept {
        if (this != &other) {
            // Clean up source object before taking over its data
            other.reset();  // FUN_00820830 – assumed to set source to default

            // Copy the 32-byte AABB data (two hkVector4)
            this->min_x = other.min_x;
            this->min_y = other.min_y;
            this->min_z = other.min_z;
            this->pad1  = other.pad1;

            // Copy the additional state fields
            this->field_0x4c = other.field_0x4c;
            this->field_0x50 = other.field_0x50;
            this->field_0x54 = other.field_0x54;
            this->field_0x58 = other.field_0x58;
            this->field_0x5c = other.field_0x5c;
        }
        return *this;
    }

private:
    // Resets this bounding box to a default/empty state (called on the source after move)
    void reset() {
        // Implementation at 0x00820830 – likely sets fields to zero or identity
    }
};