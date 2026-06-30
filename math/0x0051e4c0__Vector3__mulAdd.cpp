// FUNC_NAME: Vector3::mulAdd
void __thiscall Vector3::mulAdd(const Vector3* scale, const Vector3* offset, Vector3* out) const
{
    float x = this->x;
    float y = this->y;
    float z = this->z;
    float sx = scale->x;
    float sy = scale->y;
    float sz = scale->z;
    float ox = offset->x;
    float oy = offset->y;
    float oz = offset->z;

    out->x = x * sx + ox;
    out->y = y * sy + oy;
    out->z = z * sz + oz;
}