// FUNC_NAME: EARS::Math::Vector4::addScaled
// Function address: 0x006dfc90
// Combines two 4-element vectors: out = base + scale * this
void Vector4::addScaled(const Vector4& base, float scale, Vector4& out) const
{
    // out = base + scale * (*this)
    out.components[0] = base.components[0] + scale * this->components[0];
    out.components[1] = base.components[1] + scale * this->components[1];
    out.components[2] = base.components[2] + scale * this->components[2];
    out.components[3] = base.components[3] + scale * this->components[3];
}