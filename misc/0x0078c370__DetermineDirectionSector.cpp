// FUNC_NAME: DetermineDirectionSector
// Function at 0x0078c370: Given two vectors and a current direction index, determines the direction sector (0-7) based on dot product and cross product, applies transition table and threshold to potentially update the index.
// Uses global transition table gDirectionTransitionTable[8][8] and dot thresholds.

#include <cmath>

// Globals (defined elsewhere)
extern const float gDotThreshold1;  // DAT_00d69a74
extern const float gDotThreshold2;  // DAT_00d69a78
extern const float gDotThreshold3;  // DAT_00d69a7c
extern const float gDotThreshold4;  // DAT_00d69a80
extern const float gAngleThreshold; // DAT_00d69a70 - tolerance for dot product difference
extern const char gDirectionTransitionTable[8][8]; // DAT_00d69a88 - transition matrix [oldDir][newDir]

// Function at 0x0078c210: returns reference dot product for a given direction sector
extern float GetSectorDotProduct(int oldDir, int newDir);

int DetermineDirectionSector(float* vecA, float* vecB, int currentDir) {
    // Compute dot product
    float dot = vecA[1] * vecB[1] + vecA[0] * vecB[0] + vecA[2] * vecB[2];
    
    // Cross product z-component (Az*Bx - Ax*Bz) for left/right determination
    bool crossPositive = (vecA[2] * vecB[0] - vecB[2] * vecA[0]) > 0.0f;
    int bVar = crossPositive ? 1 : 0;

    int newDir;
    if (dot <= gDotThreshold1) {
        newDir = 0;
        if (dot <= gDotThreshold2) {
            if (dot <= gDotThreshold3) {
                if (gDotThreshold4 < dot) {
                    newDir = bVar + 1; // sectors 1 or 2
                }
            } else {
                newDir = bVar + 6; // sectors 6 or 7
            }
        } else {
            newDir = bVar + 4; // sectors 4 or 5
        }
    } else {
        newDir = 3; // sector 3
    }

    // Check if transition is allowed and within angle tolerance
    if (gDirectionTransitionTable[currentDir][newDir] == '\0' ||
        fabs(dot - GetSectorDotProduct(currentDir, newDir)) >= gAngleThreshold) {
        // Condition met: update to new direction
        currentDir = newDir;
    }
    // Note: the decompiler showed an "extraout_EDX" assignment that does not affect logic.

    return currentDir;
}