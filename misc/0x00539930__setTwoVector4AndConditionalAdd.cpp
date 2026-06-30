// FUNC_NAME: setTwoVector4AndConditionalAdd

#include <cstdint>

// Global storage (base addresses guessed from offsets)
// Equivalent to struct with 4 floats at 0x0121b830 and 0x0121b840
static Vector4 gGlobalVectorA;   // Address: 0x0121b830
static Vector4 gGlobalVectorB;   // Address: 0x0121b840

// Condition globals
static void* gCurrentContext = reinterpret_cast<void*>(0x012058e8); // Pointer to current rendering context
static void* gSpecificContext  = reinterpret_cast<void*>(0x0121b740); // Specific context to check
static int32_t gStateFlag1      = 0; // Address: 0x0121b754
static int32_t gStateFlag2      = 0; // Address: 0x0121bbb8

// Identifiers for the add call (likely indices or IDs)
static int32_t gAddId1 = 0; // Address: 0x0121b9d4
static int32_t gAddId2 = 0; // Address: 0x0121b9d8

// Forward declaration of the add function (FUN_0060add0)
extern void addVectorToList(void* list, int32_t id, const Vector4& vec);

// Reconstructed function
// Presumed to be a member function of some manager, but no this used directly
void __thiscall setTwoVector4AndConditionalAdd(Vector4* param1, Vector4* param2)
{
    // Store both 4-component vectors to global memory
    gGlobalVectorA = *param1;
    gGlobalVectorB = *param2;

    // Condition: are we in the correct context and flags match?
    if ((gCurrentContext == gSpecificContext) && (gStateFlag1 == gStateFlag2))
    {
        // Queue the vectors with specific IDs
        addVectorToList(reinterpret_cast<void*>(gStateFlag2), gAddId1, gGlobalVectorA);
        addVectorToList(reinterpret_cast<void*>(gStateFlag2), gAddId2, gGlobalVectorB);
    }
}