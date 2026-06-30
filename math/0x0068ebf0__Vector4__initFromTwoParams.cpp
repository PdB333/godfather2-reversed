// FUNC_NAME: Vector4::initFromTwoParams
// Function at 0x0068ebf0: Initializes a Vector4 (four floats) to zero, then fills it from two parameters.
// The actual filling is delegated to FUN_0069cc50 (likely a math helper).
// param_2 and param_3 are source data (e.g., pointers to other vectors or scalar values).

struct Vector4 {
    float x, y, z, w;
};

Vector4* Vector4::initFromTwoParams(Vector4* this, uint32_t param2, uint32_t param3) {
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->w = 0.0f;
    FUN_0069cc50(param2, param3, this); // fills the vector based on param2 and param3
    return this;
}