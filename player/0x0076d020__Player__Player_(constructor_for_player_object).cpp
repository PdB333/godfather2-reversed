// FUNC_NAME: Player::Player (constructor for player object)
// Function address: 0x0076d020
// Reconstructed from Ghidra decompilation

// Forward declarations for external functions and globals
extern void baseConstructor(int arg2, int arg3);
extern float getRandomFloatA();       // FUN_007161a0
extern float getRandomFloatB();       // FUN_00715e30
extern float getRandomFloatC();       // FUN_00716100
extern double getRandomDouble();      // FUN_00716490
extern void setSpecialFlag(int flag); // FUN_0072cb10

// Global constants (offsets/values from data section)
extern float g_spawnProbThreshold;    // DAT_00e51c7c
extern float g_spawnProbFactor;       // DAT_00e44590
extern float g_spawnSpeedMultiplier;  // DAT_00d5efb8
extern float g_negativeOffsetForFloat; // DAT_00e44578 (likely 1.0f or 0.5f)
extern void* g_vtable_Player;         // PTR_LAB_00d66008

// Player class internal structure (incomplete, only used offsets)
struct Player {
    void* vtable;                 // +0x00
    // ... other members ...
    int* m_ptr0x5C;               // +0x5C (offset 0x17 * 4)
    float m_field0x70;            // +0x70 (offset 0x1c)
    float m_field0x74;            // +0x74 (offset 0x1d)
    float m_field0x78;            // +0x78 (offset 0x1e)
    int m_field0x7C;              // +0x7C (offset 0x1f)
    int m_field0x80;              // +0x80 (offset 0x20)
    float m_field0x84;            // +0x84 (offset 0x21)
    float m_field0x88;            // +0x88 (offset 0x22)
    int m_field0x8C;              // +0x8C (offset 0x23)
};

// Constructor
Player* __thiscall Player::Player(int arg2, int arg3) {
    baseConstructor(arg2, arg3);

    this->vtable = &g_vtable_Player;
    this->m_field0x74 = 0.0f;
    this->m_field0x78 = 0.0f;
    this->m_field0x7C = 1;
    this->m_field0x80 = 0;
    this->m_field0x8C = 0;

    int* somePtr = this->m_ptr0x5C;

    this->m_field0x70 = getRandomFloatA();
    this->m_field0x74 = getRandomFloatB();
    this->m_field0x78 = getRandomFloatC();
    this->m_field0x88 = (float)getRandomDouble();

    // Check conditions: bit 14 clear and flag not equal to 4
    if (( (*(uint*)(somePtr + 0x8e4) >> 0xe) & 1) == 0 &&
        *(char*)(somePtr + 0x1b8c) != 4) {
        int randVal = rand();
        // Compare: if threshold < rand() * factor
        if (g_spawnProbThreshold < (float)randVal * g_spawnProbFactor &&
            (this->m_field0x8C & 2) == 0) {
            setSpecialFlag(1);
            this->m_field0x8C |= 2;
            this->m_field0x78 = getRandomFloatC();
            this->m_field0x74 = getRandomFloatB();
        }
    }

    // Compute final float from a signed integer with potential negative offset
    float temp = (float)(*(int*)(somePtr + 0x24bc));
    if (*(int*)(somePtr + 0x24bc) < 0) {
        temp += g_negativeOffsetForFloat;
    }
    this->m_field0x84 = temp * g_spawnSpeedMultiplier;

    return this;
}