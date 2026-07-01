// FUNC_NAME: Transform::combineWith
int Transform::combineWith(Transform *this, Transform *a, Transform *b) {
  // 0x90: offset to translation part of result (this)
  // 0xd0: offset to translation part of b
  // 0x50: offset to translation part of a
  float *resultTrans = (float *)((int)this + 0x90);
  float *bTrans = (float *)((int)b + 0xd0);
  float *aTrans = (float *)((int)a + 0x50);
  int rowCount = 4;
  do {
    // Process 4 rows of the transformation matrices (row-major, 4x4)
    float aRow1 = aTrans[1];
    float aRow2 = aTrans[2];
    float aRow3 = aTrans[3];
    float *bRow = (float *)(((int)b - (int)a) + (int)aTrans);
    float bRow1 = bRow[1];
    float bRow2 = bRow[2];
    float bRow3 = bRow[3];
    float *resultRow = (float *)(((int)this - (int)a) + (int)aTrans);
    *resultRow = *bRow + *aTrans;
    resultRow[1] = bRow1 + aRow1;
    resultRow[2] = bRow2 + aRow2;
    resultRow[3] = bRow3 + aRow3;
    // This appears to perform: resultTrans = bTrans * aTrans (matrix multiply)
    // but the implementation seems simplified — perhaps just blending translations?
    float aCol1 = aTrans[0x11];
    float aCol2 = aTrans[0x12];
    float aCol3 = aTrans[0x13];
    float *bCol = (float *)(((int)b - (int)this) + (int)resultTrans);
    float bCol1 = bCol[1];
    float bCol2 = bCol[2];
    float bCol3 = bCol[3];
    *resultTrans = *bCol + aTrans[0x10];
    resultTrans[1] = bCol1 + aCol1;
    resultTrans[2] = bCol2 + aCol2;
    resultTrans[3] = bCol3 + aCol3;
    // Process the third block using b's translation
    float aElem1 = aTrans[0x21];
    float aElem2 = aTrans[0x22];
    float aElem3 = aTrans[0x23];
    float bElem1 = bTrans[1];
    float bElem2 = bTrans[2];
    float bElem3 = bTrans[3];
    resultTrans[0x10] = aTrans[0x20] + *bTrans;
    resultTrans[0x11] = aElem1 + bElem1;
    resultTrans[0x12] = aElem2 + bElem2;
    resultTrans[0x13] = aElem3 + bElem3;
    // Advance to next row
    aTrans += 4;
    resultTrans += 4;
    bTrans += 4;
    rowCount--;
  } while (rowCount != 0);
  return (int)this;
}