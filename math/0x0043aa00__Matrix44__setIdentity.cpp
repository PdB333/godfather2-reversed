// FUNC_NAME: Matrix44::setIdentity
void Matrix44::setIdentity()
{
    // Global constant, presumably 1.0f for identity scale
    float diagVal = *(float*)&DAT_00e2b1a4;

    // Row 0: [0][0] = diagVal, rest zero
    this->data[0] = diagVal;
    this->data[1] = 0.0f;
    this->data[2] = 0.0f;
    this->data[3] = 0.0f;

    // Row 1: [1][0] zero, [1][1] = diagVal, [1][2-3] zero
    this->data[4] = 0.0f;
    this->data[5] = diagVal;
    this->data[6] = 0.0f;
    this->data[7] = 0.0f;

    // Row 2: [2][0-1] zero, [2][2] = diagVal, [2][3] zero
    this->data[8] = 0.0f;
    this->data[9] = 0.0f;
    this->data[10] = diagVal;
    this->data[11] = 0.0f;

    // Row 3: [3][0-2] zero, [3][3] = diagVal
    this->data[12] = 0.0f;
    this->data[13] = 0.0f;
    this->data[14] = 0.0f;
    this->data[15] = diagVal;
}