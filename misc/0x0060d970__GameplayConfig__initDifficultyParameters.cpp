// FUNC_NAME: GameplayConfig::initDifficultyParameters
// Address: 0x0060d970
// This function initializes difficulty scaling parameters for gameplay AI and player adjustment.
// It clamps player and enemy level values, sets various global flags and constants, then
// calls another function to apply the difficulty curves.

#include <cstdint> // for int32_t, int, etc.

// Forward declaration of the function that applies difficulty settings
extern void applyDifficultySettings(float* weights1, int unkFlag, float* weights2);

// Global constants (likely defined elsewhere)
extern const float g_defaultDifficultyValue; // DAT_00e2b1a4
extern const float g_someOtherFloat;         // DAT_00e2cd54
extern const float g_yetAnotherFloat;        // DAT_0120589c

// Global variables to be modified
extern int g_playerLevel;        // DAT_012058d0
extern int g_enemyLevel;         // DAT_00f15988
extern int g_someFlag1;          // DAT_011f3a44
extern int g_someInt1;           // DAT_011f3a3c
extern int g_someFlag2;          // DAT_011f3a38
extern int g_someFlag3;          // DAT_011f3a14
extern float g_someVec3[3];      // DAT_011f4220, 4224, 4228
extern int g_someInt2;           // DAT_011f3a34
extern float g_someFloat1;       // DAT_011f422c
extern float g_someFloat2;       // DAT_011f4230

void GameplayConfig::initDifficultyParameters(void)
{
    // Two local arrays representing difficulty curves for different aspects
    float difficultyWeights1[8]; // local_30, local_2c, ..., local_14
    float difficultyWeights2[8]; // local_50, local_4c, ..., local_34

    // Initialize first array: first three zeros, then default value, then zero, then default
    difficultyWeights1[0] = 0.0f;
    difficultyWeights1[1] = 0.0f;
    difficultyWeights1[2] = 0.0f;
    difficultyWeights1[3] = g_defaultDifficultyValue;
    difficultyWeights1[4] = g_defaultDifficultyValue;
    difficultyWeights1[5] = g_defaultDifficultyValue;
    difficultyWeights1[6] = 0.0f;
    difficultyWeights1[7] = g_defaultDifficultyValue;

    // Initialize second array: first two zeros, rest default
    difficultyWeights2[0] = 0.0f;
    difficultyWeights2[1] = 0.0f;
    difficultyWeights2[2] = g_defaultDifficultyValue;
    difficultyWeights2[3] = g_defaultDifficultyValue;
    difficultyWeights2[4] = g_defaultDifficultyValue;
    difficultyWeights2[5] = g_defaultDifficultyValue;
    difficultyWeights2[6] = g_defaultDifficultyValue;
    difficultyWeights2[7] = g_defaultDifficultyValue;

    // Clamp player level to minimum 27 (0x1b)
    if (g_playerLevel < 0x1b) {
        g_playerLevel = 0x1b;
    }
    // Clamp enemy level to maximum 27 (0x1b)
    if (g_enemyLevel > 0x1a) {
        g_enemyLevel = 0x1b;
    }
    g_someFlag1 = 0;

    // Clamp player level to minimum 25 (0x19)
    if (g_playerLevel < 0x19) {
        g_playerLevel = 0x19;
    }
    // Clamp enemy level to maximum 25 (0x19)
    if (g_enemyLevel > 0x19) {
        g_enemyLevel = 0x19;
    }
    g_someInt1 = 7; // DAT_011f3a3c

    // Clamp player level to minimum 24 (0x18)
    if (g_playerLevel < 0x18) {
        g_playerLevel = 0x18;
    }
    // Clamp enemy level to maximum 24 (0x18)
    if (g_enemyLevel > 0x18) {
        g_enemyLevel = 0x18;
    }
    g_someFlag2 = 0; // DAT_011f3a38

    // Clamp player level to minimum 15 (0xf)
    if (g_playerLevel < 0xf) {
        g_playerLevel = 0xf;
    }
    // Clamp enemy level to maximum 15 (0xf)
    if (g_enemyLevel > 0xf) {
        g_enemyLevel = 0xf;
    }
    g_someFlag3 = 0; // DAT_011f3a14

    // Final clamp to 23 (0x17)
    if (g_playerLevel < 0x17) {
        g_playerLevel = 0x17;
    }
    if (g_enemyLevel > 0x17) {
        g_enemyLevel = 0x17;
    }

    // Set global vector to default value (likely color or offset)
    g_someVec3[0] = g_defaultDifficultyValue; // +0x00
    g_someVec3[1] = g_defaultDifficultyValue; // +0x04
    g_someVec3[2] = g_defaultDifficultyValue; // +0x08

    g_someInt2 = 8; // DAT_011f3a34

    // Set two floats from constants
    g_someFloat1 = g_someOtherFloat;    // DAT_011f422c
    g_someFloat2 = g_yetAnotherFloat;   // DAT_011f4230

    // Apply the difficulty curves with a flag of 0
    applyDifficultySettings(difficultyWeights1, 0, difficultyWeights2);
}