// FUNC_NAME: Vector4::add
void __thiscall Vector4::add(float4* this, float4* other, float4* out) {
    out->x = this->x + other->x;
    out->y = this->y + other->y;
    out->z = this->z + other->z;
    out->w = this->w + other->w;
}