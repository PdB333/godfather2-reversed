// FUNC_NAME: Matrix33::Matrix33

Matrix33* __thiscall Matrix33::Matrix33(Matrix33* this) {
    int* data = (int*)this;            // treat as array of 9 ints
    for (int i = 0; i < 3; i++) {      // zero each row of 3 ints
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
        data += 3;                     // advance to next row
    }
    FUN_0089e820();                   // base class or additional initialization
    return this;
}