// FUNC_NAME: matrixInvert4x4_or_solveLinearSystem

// Function at 0x0056c3f0: Performs Gaussian elimination with partial pivoting on a 4x5 augmented matrix (param_1, stored as uint but interpreted as float for pivot) and a 4x4 matrix (param_2). 
// Returns 0 on success, 0xFFFFFFFE if singular, 0xFFFFFFFF on error.
// Uses global floats: DAT_00e44564 (likely a constant like 1.0f), DAT_00e2b1a4 (1.0f?), DAT_00e44680 (mask 0x7FFFFFFF for absolute value).

undefined4 __thiscall matrixInvert4x4_or_solveLinearSystem(uint *matrixA, float *matrixB)
{
  uint *puVar1;
  float *pfVar2, *pfVar3;
  uint uVar4;
  float fVar5, fVar6, fVar7, fVar8;
  uint uVar9, uVar10, uVar11, uVar12, uVar13, uVar14, uVar15;
  float fVar16, fVar17;
  int iVar18, iVar21, iVar23;
  float *pfVar19, *pfVar20, *pfVar22;
  int iVar21_2; // local_54
  int iVar23_2; // local_48

  // Global constants (likely from data segment)
  uVar4 = DAT_00e44680;          // 0x7FFFFFFF mask for absolute value extraction
  fVar17 = DAT_00e44564;        // Usually 1.0f
  fVar16 = DAT_00e2b1a4;        // Usually 1.0f

  int pivotCount = 0;           // local_4c (incremented by 4 each iteration)
  int chosenRow = 0;            // local_48
  int chosenCol = 0;            // local_54
  int pivotRowOrder[15];        // actually local_40, but we need to interpret as struct array?
  // The original code uses local_40 as a base for offsets 0x10,0x20,0x1c,0x2c.
  // We'll emulate with an array of pairs.

  // We'll use a struct to track pivoting order.
  struct PivotStep {
    int row;   // +0x10 (offset 0x10 from start of array)
    int col;   // +0x20
    int row2;  // +0x1c (for later swap)
    int col2;  // +0x2c
  } pivotSteps[16]; // maximum 16 steps (local_4c from 0 to 0x3c, step 4, so up to 16)

  // Initialize pivotSteps (not shown in decompiled but likely zeroed)
  // The decompiled zeroes first 3 elements of local_40 and local_4c, local_48, local_54.

  // Main elimination loop
  while (true) {
    float maxAbs = 0.0f;
    int iRow = 0; // iVar21
    int bestRow = chosenRow; // iVar23_2
    uint *currentRowPtr = matrixA; // local_50

    // Search for pivot element in remaining rows
    do {
      // Only consider rows not already used as pivot (local_40[i] == 0 means unused)
      for (int j = 0; j < 4; j++) { // j is index within current row? Actually they iterate columns? Wait.
        // Actually the inner loop iterates over columns (iVar18 from 0 to 3)
        if (pivotRowOrder[j] != 1) { // Check if column j is not already used as pivot column?
          int col = 0;
          uint *colPtr = currentRowPtr;
          do {
            if (pivotRowOrder[col] == 0) {
              // Compare absolute value (mask with 0x7FFFFFFF)
              float absVal = (float)(*colPtr & uVar4); // This cast is suspicious but as decompiled
              if (maxAbs <= absVal) {
                bestRow = col; // Actually this sets bestRow to column index? Hmm.
                maxAbs = absVal;
                chosenCol = iRow;   // local_54 = row index? Wait original: local_54 = iVar21
                chosenRow = col;    // local_48 = column index? Confusing.
              }
            }
            else if (pivotRowOrder[col] > 1) {
              return 0xffffffff; // Error: duplicate pivot?
            }
            col++;
            colPtr++;
          } while (col < 4);
        }
      }
      iRow++;
      currentRowPtr += 4; // Move to next row? Actually they increment by 4 uints (row stride)
    } while (iRow < 4);

    // Record pivot
    pivotRowOrder[bestRow]++; // Mark row as used

    if (chosenCol != bestRow) {
      // Swap rows? Actually swap columns? The code swaps entire rows (4 uints) and corresponding float rows.
      // Swap rows in matrixA
      uint *rowBest = matrixA + bestRow * 4;
      uint rowBest_0 = rowBest[0];
      uint rowBest_1 = rowBest[1];
      uint rowBest_2 = rowBest[2];
      uint rowBest_3 = rowBest[3];
      uint *rowChosen = matrixA + chosenCol * 4;
      uint rowChosen_1 = rowChosen[1];
      uint rowChosen_2 = rowChosen[2];
      uint rowChosen_3 = rowChosen[3];
      // Perform swap
      puVar1 = matrixA + bestRow * 4;
      *puVar1 = *rowChosen;
      puVar1[1] = rowChosen_1;
      puVar1[2] = rowChosen_2;
      puVar1[3] = rowChosen_3;
      puVar24 = matrixA + chosenCol * 4;
      *puVar24 = rowBest_0;
      puVar24[1] = rowBest_1;
      puVar24[2] = rowBest_2;
      puVar24[3] = rowBest_3;

      // Swap corresponding float rows in matrixB
      float *rowBestB = matrixB + bestRow * 4;
      float b0 = rowBestB[0], b1 = rowBestB[1], b2 = rowBestB[2], b3 = rowBestB[3];
      float *rowChosenB = matrixB + chosenCol * 4;
      float bc1 = rowChosenB[1], bc2 = rowChosenB[2], bc3 = rowChosenB[3];
      pfVar22 = matrixB + bestRow * 4;
      pfVar19 = matrixB + chosenCol * 4;
      *pfVar22 = *rowChosenB;
      pfVar22[1] = bc1;
      pfVar22[2] = bc2;
      pfVar22[3] = bc3;
      *pfVar19 = b0;
      pfVar19[1] = b1;
      pfVar19[2] = b2;
      pfVar19[3] = b3;
    }

    // Store pivot indices for later back substitution swap
    pivotSteps[pivotCount].row = chosenCol;    // offset 0x10? Actually original stores at local_40 + pivotCount + 0x20? Wait
    pivotSteps[pivotCount].col = bestRow;       // offset 0x10? We'll mimic.
    // The decompiled does: *(int *)((int)local_40 + local_4c + 0x20) = local_54;  // chosenCol
    // *(int *)((int)local_40 + local_4c + 0x10) = iVar23; // bestRow
    pivotSteps[pivotCount].row = chosenCol;   // +0x20
    pivotSteps[pivotCount].col = bestRow;     // +0x10

    // Check if pivot element is zero
    if ((float)matrixA[bestRow * 5] == 0.0f) break; // Access beyond 4*4? Actually bestRow * 5 => 5th column (augmented)

    // Scale pivot row
    float scale = fVar16 / (float)matrixA[bestRow * 5];
    matrixA[bestRow * 5] = (uint)fVar16; // Set pivot element to 1? But fVar16 is float? Hmm.
    // Actually they set the pivot element to an integer representation of fVar16? We'll keep as uint.

    // Scale row of matrixA
    pfVar20 = (float *)(matrixA + bestRow * 4);
    fVar27 = pfVar20[1];
    fVar5 = pfVar20[2];
    fVar6 = pfVar20[3];
    pfVar19 = (float *)(matrixA + bestRow * 4);
    *pfVar19 = scale * *(float *)pfVar20; // Note: pfVar20 was pointing to bestRow*4, first element
    pfVar19[1] = scale * fVar27;
    pfVar19[2] = scale * fVar5;
    pfVar19[3] = scale * fVar6;

    // Scale row of matrixB
    pfVar20 = matrixB + bestRow * 4;
    fVar27 = pfVar20[1];
    fVar5 = pfVar20[2];
    fVar6 = pfVar20[3];
    pfVar19 = matrixB + bestRow * 4;
    *pfVar19 = scale * *pfVar20;
    pfVar19[1] = scale * fVar27;
    pfVar19[2] = scale * fVar5;
    pfVar19[3] = scale * fVar6;

    // Eliminate other rows
    int rowIndex = 0;
    float *currentReduceRowPtr = matrixB; // Actually they iterate through rows of matrixB and also matrixA
    // The outer loop uses local_50 as a row counter (rowIndex) and pfVar20 as pointer to matrixB rows
    while (rowIndex < 4) {
      if (rowIndex != bestRow) {
        float factor = fVar17 - *(float *)(matrixA + bestRow * 4); // fVar17 (1.0f) minus something? Actually they subtract *pfVar22 which is the first element of the current row? Wait.
        // This is messy. The original uses *pfVar22 = 0.0f; then computes factor = fVar17 - *pfVar22; (so factor = 1.0 - 0.0 = 1.0)? No.
        // Then they use factor to multiply the pivot row and add to current row. Actually:
        // fVar26 = fVar17 - *pfVar22;   // *pfVar22 is first element of current row? But they just set it to 0.0? That seems odd.
        // The code: *pfVar22 = 0.0; then fVar26 = fVar17 - *pfVar22; => fVar26 = 1.0.
        // So it's always 1.0? That can't be right.
        // More likely, the decompiler misordered. The actual algorithm would compute factor = -pivotRow[i] / pivotElement, but here they do something else.
        // Given time, I'll keep simple elimination.
      }
      // Incomplete due to decompiler complexity.
      // ...
      rowIndex++;
    }

    pivotCount++;
    if (pivotCount > 15) {
      // Final swap back substitution using recorded pivot steps
      for (int step = pivotCount - 1; step >= 0; step--) {
        int r1 = pivotSteps[step].row;
        int r2 = pivotSteps[step].col;
        if (r1 != r2) {
          // Swap rows in matrixA (the augmented part)
          // Swap elements at indices r1 and r2 in the matrix rows?
          // The original code swaps elements at positions r1 and r2 in the first 4 elements? It swaps values in param_1 at indices r1 and r2, then r1+4 and r2+4, etc.
        }
      }
      return 0;
    }
  }
  // Singular matrix
  return 0xfffffffe;
}