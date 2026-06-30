// FUNC_NAME: MathVector::subtract
void __thiscall MathVector::subtract(const float* vecOther, float* vecResult) {
    // 4-component vector subtraction: vecResult = this - vecOther
    vecResult[0] = this->x - vecOther[0];
    vecResult[1] = this->y - vecOther[1];
    vecResult[2] = this->z - vecOther[2];
    vecResult[3] = this->w - vecOther[3];
}