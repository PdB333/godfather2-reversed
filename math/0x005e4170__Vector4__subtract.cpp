// FUNC_NAME: Vector4::subtract
class Vector4 {
public:
    float x, y, z, w;

    // Subtract vector 'a' from vector 'b', storing result in this vector (w component unchanged)
    // __fastcall: this in ecx, a in edx, b on stack
    void __fastcall subtract(const float* a, const float* b) {
        float ay = a[1];
        float az = a[2];
        float aw = a[3];
        float by = b[1];
        float bz = b[2];
        float bw = b[3];
        float srcW = this->w;  // preserve original w

        this->x = a[0] - b[0];
        this->y = ay - by;
        this->z = az - bz;
        this->w = aw - bw;  // subtract w components
        this->w = srcW;     // restore original w (so only xyz are modified)
    }
};