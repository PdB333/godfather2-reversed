// FUNC_NAME: Vec4::subtract

class Vec4 {
public:
    float x, y, z, w;

    void __thiscall subtract(const Vec4& other, Vec4& out) const {
        out.x = this->x - other.x;
        out.y = this->y - other.y;
        out.z = this->z - other.z;
        out.w = this->w - other.w;
    }
};