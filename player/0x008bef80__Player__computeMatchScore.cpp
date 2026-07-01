// FUNC_NAME: Player::computeMatchScore
#include <cstdint>

// Forward declarations of helper functions
static int* GetMatchDataFirst(int param);   // FUN_0084b400
static int* GetMatchDataSecond(int param);  // FUN_0084b430
static int   GetObjectId(int value);        // FUN_006b0f50

// Global pointer from binary (DAT_0112f938 + 0xb0 holds a float multiplier)
extern void* g_globalScoreMultiplierData;

float Player::computeMatchScore() {
    // this+0x19c : pointer to a component (e.g., relationship component)
    int* component = reinterpret_cast<int*>(*(int*)(this + 0x19c));
    
    // component+0x38 : first data block identifier
    int dataBlockID = *(int*)(component + 0x38);
    // component+0xc4 : conditional flag (1 = use first method, else second)
    int flag = *(int*)(component + 0xc4);
    
    int value1, value2;
    if (flag == 1) {
        int* data = GetMatchDataFirst(dataBlockID);
        // Offsets +0x24 and +0x28 contain two values to compare
        value1 = *(int*)(data + 0x24);
        value2 = *(int*)(data + 0x28);
    } else {
        int* data = GetMatchDataSecond(dataBlockID);
        // Offsets +0x20 and +0x24 contain two values to compare
        value1 = *(int*)(data + 0x20);
        value2 = *(int*)(data + 0x24);
    }
    
    // this+0x54 : player/family ID to match against
    int localID = *(int*)(this + 0x54);
    
    int matchCount = 0;
    if (GetObjectId(value1) == localID)
        matchCount++;
    if (GetObjectId(value2) == localID)
        matchCount++;
    
    // Global multiplier at offset 0xb0 of the global data structure
    float multiplier = *reinterpret_cast<float*>(reinterpret_cast<char*>(g_globalScoreMultiplierData) + 0xb0);
    return static_cast<float>(matchCount) * multiplier;
}