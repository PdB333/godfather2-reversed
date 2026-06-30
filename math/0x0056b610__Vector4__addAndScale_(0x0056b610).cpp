// FUNC_NAME: Vector4::addAndScale (0x0056b610)
// Reconstructed C++ for __thiscall member function of a 4-element float vector class (likely EARS::Math::Vector4 or similar).
// Operation: out[i] = scalar * (this[i] + other[i])

struct Vector4 {
    float v[4];
};

void __thiscall Vector4::addAndScale(const Vector4* other, float scalar, Vector4* out) const
{
    // Load this vector elements
    float this0 = this->v[0];
    float this1 = this->v[1];
    float this2 = this->v[2];
    float this3 = this->v[3];

    // Load other vector elements
    float other0 = other->v[0];
    float other1 = other->v[1];
    float other2 = other->v[2];
    float other3 = other->v[3];

    // Compute scaled sum
    out->v[0] = scalar * (this0 + other0);
    out->v[1] = scalar * (this1 + other1);
    out->v[2] = scalar * (this2 + other2);
    out->v[3] = scalar * (this3 + other3);
}