// FUNC_NAME: ScriptVirtualMachine::executeRandomInt
// Address: 0x006326d0
// This function appears to be part of a script interpreter's random number generation.
// It reads the number of free 8-byte slots in the output buffer to determine the random range type:
//   0 slots? (not handled, falls through to default which writes a random value and advances pointer)
//   1 slot  -> generates random in [0, arg] (where arg is implicitly the random value itself? Strange)
//   2 slots -> generates random in [arg1, arg2]
// The function uses a pseudo-random float from rand() and scales it.
// It writes the result as an 8-byte pair: opcode 3 (likely integer constant) and the value.

#include <cstdlib>
#include <cstdint>

// Constants for float-to-int conversion (likely from IEEE 754 tricks)
static const float RAND_SCALE = *(float*)0x00e44590; // 1.0f / 32767.0f? 
static const uint32_t FLOAT_TO_INT_MAGIC = 0x00e44648; // part of magic constant
static const uint32_t FLOAT_MASK = 0x00e44564; // mask for mantissa bits
static const uint32_t FLOAT_ROUND = 0x00e2b1a4; // rounding constant

// Forward declarations for helper functions (addresses)
int reportError(int vmContext, int numArgs, const char* fmt); // FUN_00627a20
void reportErrorSimple(const char* msg); // FUN_00627bd0
void updateRandomSeed(); // FUN_00628080

int ScriptVirtualMachine::executeRandomInt(int vmContext)
{
    // vmContext is pointer to VM state structure
    // Offsets: +0x08 = current output pointer (to be advanced)
    //          +0x0c = end of output buffer
    int randVal = rand();
    uint32_t* outPtr = *(uint32_t**)(vmContext + 0x08);
    uint32_t* outEnd = *(uint32_t**)(vmContext + 0x0c);
    int numFreeSlots = (int)(outPtr - outEnd) >> 3; // number of 8-byte slots available

    // Convert rand() % 0x7fff to a normalized float in [0,1)
    float randFloat = (float)(randVal % 0x7fff) * RAND_SCALE;

    if (numFreeSlots != 0) {
        if (numFreeSlots == 1) {
            // Single argument case: generates random int in [0, something]
            float tempFloat = randFloat;
            updateRandomSeed();
            int tempInt = (int)tempFloat;
            if (tempInt < 1) {
                reportError(vmContext, 1, "interval is empty");
                tempInt = *(int*)&randFloat; // maybe restore? but extraout_ECX is used
            }
            outPtr = *(uint32_t**)(vmContext + 0x08);
            randFloat = (float)tempInt * randFloat;
            // Float-to-int conversion using magic constants
            uint32_t bits = *(uint32_t*)&randFloat;
            float magic = *(float*)(&FLOAT_TO_INT_MAGIC | (FLOAT_MASK & bits));
            float adjusted = (randFloat + magic) - magic;
            float correction = (float)(-(uint32_t)((float)(FLOAT_MASK & bits) < adjusted - randFloat) & FLOAT_ROUND);
            *outPtr = 3; // opcode for integer constant
            outPtr[1] = *(uint32_t*)(&((int)(adjusted - correction) + 1));
            *(int*)(vmContext + 0x08) += 8;
            return 1;
        }
        float tempFloat = randFloat;
        if (numFreeSlots == 2) {
            updateRandomSeed();
            int lower = (int)tempFloat;
            updateRandomSeed();
            int upper = (int)tempFloat;
            if (upper < lower) {
                reportError(vmContext, 2, "interval is empty");
            }
            outPtr = *(uint32_t**)(vmContext + 0x08);
            float range = (float)((upper - lower) + 1) * randFloat;
            uint32_t bits = *(uint32_t*)&range;
            float magic = *(float*)(&FLOAT_TO_INT_MAGIC | (FLOAT_MASK & bits));
            float adjusted = (range + magic) - magic;
            float correction = (float)(-(uint32_t)((float)(FLOAT_MASK & bits) < adjusted - range) & FLOAT_ROUND);
            int result = (int)(adjusted - correction) + lower;
            *outPtr = 3;
            outPtr[1] = result;
            *(int*)(vmContext + 0x08) += 8;
            return 1;
        }
        reportErrorSimple("wrong number of arguments");
    }
    // Default case (numFreeSlots == 0 or other): write random float? Actually writes same as above?
    *outPtr = 3;
    outPtr[1] = randFloat; // note: could be int cast, but original is float
    *(int*)(vmContext + 0x08) += 8;
    return 1;
}