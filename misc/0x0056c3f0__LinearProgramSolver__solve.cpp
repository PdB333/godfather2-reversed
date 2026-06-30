// FUNC_NAME: LinearProgramSolver::solve
// Address: 0x0056c3f0
// Role: Solves a linear programming problem using the simplex method (pivot iteration)
// Works on a 4x5 matrix (uint) and a 4x4 matrix (float) representing constraints/objective
// Returns 0 on success, 0xfffffffe if unbounded, 0xffffffff on error

#include <cstdint>

#define MASK_CONSTANT      0x00e44680  // bitmask used for pivot selection?
#define ONE_MINUS_EPSILON  0x00e44564  // ~1.0 or similar
#define CONSTANT_VALUE     0x00e2b1a4  // scaling factor?

int32_t __thiscall LinearProgramSolver::solve(uint32_t* constraintMatrix, float* dualMatrix)
{
    uint32_t mask = MASK_CONSTANT;
    float oneMinusEpsilon = ONE_MINUS_EPSILON;
    float constantValue = CONSTANT_VALUE;

    int32_t pivotRow = 0;
    int32_t pivotCol = 0;
    int32_t status[4] = {0, 0, 0, 0}; // 0=unused, 1=basic, >1=error
    int32_t pivotHistory[16]; // stored in local_40 + 0x10,0x20 offsets
    int32_t iteration = 0;

    while (true)
    {
        float maxVal = 0.0f;
        int32_t bestRow = pivotRow;
        int32_t bestCol = 0;
        uint32_t* rowPtr = constraintMatrix;

        // Find pivot: largest (value & mask) among columns for rows with status!=1,
        // and rows with status==0
        for (int32_t col = 0; col < 4; col++)
        {
            if (status[col] == 1) continue; // basic column, skip

            for (int32_t row = 0; row < 4; row++)
            {
                if (status[row] == 0)
                {
                    float candidate = (float)(rowPtr[row] & mask);
                    if (candidate > maxVal)
                    {
                        maxVal = candidate;
                        bestRow = row;
                        bestCol = col;
                    }
                }
                else if (status[row] > 1)
                {
                    return 0xFFFFFFFF; // error
                }
            }
            rowPtr += 4; // move to next row block? Actually rowPtr points to start of row? Wait...
        }

        status[bestRow]++;

        if (bestCol != bestRow)
        {
            // Swap rows in constraintMatrix (4 consecutive uint32s per row)
            uint32_t* srcRow = &constraintMatrix[bestRow * 4];
            uint32_t* dstRow = &constraintMatrix[bestCol * 4];
            for (int32_t i = 0; i < 4; i++)
            {
                uint32_t temp = srcRow[i];
                srcRow[i] = dstRow[i];
                dstRow[i] = temp;
            }

            // Swap rows in dualMatrix (4 consecutive floats per row)
            float* srcDual = &dualMatrix[bestRow * 4];
            float* dstDual = &dualMatrix[bestCol * 4];
            for (int32_t i = 0; i < 4; i++)
            {
                float temp = srcDual[i];
                srcDual[i] = dstDual[i];
                dstDual[i] = temp;
            }
        }

        // Record pivot history
        pivotHistory[iteration * 2] = bestRow;      // stored at offset 0x10
        pivotHistory[iteration * 2 + 1] = bestCol; // stored at offset 0x20

        // Check if the pivot element (column index 4) is zero
        float pivotElement = (float)constraintMatrix[bestRow * 5 + 4]; // index 4 (5th column)
        if (pivotElement == 0.0f)
            return 0xFFFFFFFE; // unbounded

        // Scale pivot row so that pivot element becomes constantValue
        float scale = constantValue / pivotElement;
        constraintMatrix[bestRow * 5 + 4] = (uint32_t)constantValue;

        float* pivotRowStart = (float*)&constraintMatrix[bestRow * 4];
        for (int32_t i = 0; i < 4; i++)
        {
            pivotRowStart[i] *= scale;
            dualMatrix[bestRow * 4 + i] *= scale;
        }

        // Eliminate other rows using pivot row
        float* pivotRowFloatA = (float*)&constraintMatrix[bestRow * 4];
        float* pivotRowFloatB = &dualMatrix[bestRow * 4];

        for (int32_t row = 0; row < 4; row++)
        {
            if (row == bestRow) continue;

            float factor = oneMinusEpsilon - pivotRowFloatA[row]; // ???
            pivotRowFloatA[row] = 0.0f; // zero out pivot column in this row

            float* targetRowA = (float*)&constraintMatrix[row * 4];
            float* targetRowB = &dualMatrix[row * 4];

            for (int32_t i = 0; i < 4; i++)
            {
                targetRowA[i] = factor * pivotRowFloatA[i] + targetRowA[i];
                targetRowB[i] = factor * pivotRowFloatB[i] + targetRowB[i];
            }
        }

        iteration++;
        if (iteration > 15) // 0xf
        {
            // Final pass: sort rows based on pivot history (swap back?)
            for (int32_t i = 0; i > -13; i -= 4) // loop from 0 down to -12 step -4
            {
                int32_t a = pivotHistory[i + 7]; // offset 0x1c
                int32_t b = pivotHistory[i + 11]; // offset 0x2c
                if (a != b)
                {
                    // Swap rows a and b in constraintMatrix
                    for (int32_t j = 0; j < 4; j++)
                    {
                        uint32_t temp = constraintMatrix[a * 4 + j];
                        constraintMatrix[a * 4 + j] = constraintMatrix[b * 4 + j];
                        constraintMatrix[b * 4 + j] = temp;
                    }
                }
            }
            return 0;
        }
    }
}