// FUNC_NAME: createTransformationNode
// Address: 0x005195b0
// Role: Constructs a transformation node from optional source matrix, a 4‑float vector, and additional parameters.
//       The function first fills a matrix structure (param_2) then calls FUN_00424470 to create
//       a node object and attaches the matrix data and other fields to it.

#include <cstdint>

// Global constant (likely 1.0f)
extern const float DAT_00e2b1a4;

// External function that allocates/initializes a node object (returns pointer in EDX)
extern int FUN_00424470();

// External vtable pointer for the transformation node type
extern void* PTR_LAB_00e381a0;

// External global referenced by ESI in this function (maybe a singleton or static data)
extern uint64_t unaff_ESI[2];

int __fastcall createTransformationNode(float* inSrcMatrix, float* outMatrix,
                                         int param_3, float* inExtra,
                                         int param_5, int param_6)
{
    float fVar4 = DAT_00e2b1a4;
    float fVar5, fVar6, fVar7, fVar8;

    // Set vtable pointer at offset 0 of the output structure
    *(void**)outMatrix = &PTR_LAB_00e381a0;

    if (inSrcMatrix == nullptr)
    {
        // No source matrix: fill a 4x4 identity-like matrix at indices 0x10..0x1f
        // (16 floats, row-major, last row is (0,0,0,fVar4) unless changed later)
        outMatrix[0x10] = fVar4;  // Row0 Col0
        outMatrix[0x11] = 0.0f;   // Row0 Col1
        outMatrix[0x12] = 0.0f;   // Row0 Col2
        outMatrix[0x13] = 0.0f;   // Row0 Col3
        outMatrix[0x14] = 0.0f;   // Row1 Col0
        outMatrix[0x15] = fVar4;  // Row1 Col1
        outMatrix[0x16] = 0.0f;   // Row1 Col2
        outMatrix[0x17] = 0.0f;   // Row1 Col3
        outMatrix[0x18] = 0.0f;   // Row2 Col0
        outMatrix[0x19] = 0.0f;   // Row2 Col1
        outMatrix[0x1a] = fVar4;  // Row2 Col2
        outMatrix[0x1b] = 0.0f;   // Row2 Col3
        // Last row locals: fVar5, fVar6, fVar7 remain 0.0, fVar8 = fVar4
        fVar5 = 0.0f;
        fVar6 = 0.0f;
        fVar7 = 0.0f;
        fVar8 = fVar4;
    }
    else
    {
        // Copy the entire 4x4 source matrix (16 floats) into the output
        outMatrix[0x10] = inSrcMatrix[0];
        outMatrix[0x11] = inSrcMatrix[1];
        outMatrix[0x12] = inSrcMatrix[2];
        outMatrix[0x13] = inSrcMatrix[3];
        outMatrix[0x14] = inSrcMatrix[4];
        outMatrix[0x15] = inSrcMatrix[5];
        outMatrix[0x16] = inSrcMatrix[6];
        outMatrix[0x17] = inSrcMatrix[7];
        outMatrix[0x18] = inSrcMatrix[8];
        outMatrix[0x19] = inSrcMatrix[9];
        outMatrix[0x1a] = inSrcMatrix[10];
        outMatrix[0x1b] = inSrcMatrix[11];
        fVar5 = inSrcMatrix[12];
        fVar6 = inSrcMatrix[13];
        fVar7 = inSrcMatrix[14];
        fVar8 = inSrcMatrix[15];
    }

    // Write the fourth row (indices 0x1c..0x1f) from the local variables
    outMatrix[0x1c] = fVar5;
    outMatrix[0x1d] = fVar6;
    outMatrix[0x1e] = fVar7;
    outMatrix[0x1f] = fVar8;

    // Copy the 4‑float vector (e.g. translation/color) to indices 0xc..0xf
    outMatrix[0xc] = inExtra[0];
    outMatrix[0xd] = inExtra[1];
    outMatrix[0xe] = inExtra[2];
    outMatrix[0xf] = inExtra[3];

    // Condition: if the first three components of the vector are equal to the global constant,
    // set the fourth component to that constant; otherwise set to 0.
    // (This mimics quaternion or scaling logic.)
    if (outMatrix[0xc] == fVar4 && outMatrix[0xd] == fVar4 && outMatrix[0xe] == fVar4)
        outMatrix[0xf] = fVar4;
    else
        outMatrix[0xf] = 0.0f;

    // Store two additional integer/float parameters at indices 10 and 0xb
    // These might be flags, handles, or other data.
    *(int*)(outMatrix + 0xb) = param_6;   // offset 0x2c
    *(int*)(outMatrix + 10)   = param_5;  // offset 0x28

    // Create the actual node object via another function
    int node = FUN_00424470();

    // Initialize node fields using the passed parameter and global ESI data
    *(int*)(node + 0xc0) = param_3;                 // Some identifier
    *(uint64_t*)(node + 0x18) = unaff_ESI[0];       // First quadword from global
    *(uint64_t*)(node + 0x20) = unaff_ESI[1];       // Second quadword from global
    *(int*)(node + 0x10) = 0;                       // Zero out field
    *(int*)(node + 200) = 0;                        // offset 0xC8 (200 decimal)
    *(int*)(node + 0xc4) = 0;                       // Zero out another field

    return node;  // Return the newly created node's pointer
}