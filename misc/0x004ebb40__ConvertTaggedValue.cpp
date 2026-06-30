// FUNC_NAME: ConvertTaggedValue
// Address: 0x004ebb40
// Role: Converts a tagged value (pointed by EAX) into a pair (type, value) stored at ESI.
// The input is a pointer to a structure with at least two dwords: first is a type tag, second is the value.
// The output is a two-dword structure: first is an enum (0,1,2), second is the resolved value.
// Constants: 0xE1E2E3E4 and 0xF1F2F3F4 are magic tags for specific types.
// Global g_someThreshold (DAT_010c2328) controls fallback behavior.

#define TAG_TYPE_A 0xE1E2E3E4  // -0x1e1d1c1c
#define TAG_TYPE_B 0xF1F2F3F4  // -0xe0d0c0c

extern int g_someThreshold; // DAT_010c2328
extern int FUN_004eb950(int arg); // conversion helper

// Called with EAX = input pointer, ESI = output pointer
void ConvertTaggedValue(void)
{
    int* inputPtr;   // in_EAX
    int* outputPtr;  // unaff_ESI
    int threshold;   // iVar1
    int converted;   // uVar2

    threshold = g_someThreshold;
    if (*inputPtr == TAG_TYPE_A) {
        // Type A: output type 0, value = second dword of input
        outputPtr[0] = 0;
        outputPtr[1] = inputPtr[1];
        return;
    }
    if (*inputPtr != TAG_TYPE_B) {
        // Default type: output type 1
        outputPtr[0] = 1;
        if (threshold > 18) {
            outputPtr[1] = 0;
            return;
        }
        converted = FUN_004eb950(0);
        outputPtr[1] = converted;
        return;
    }
    // Type B: output type 2, value = second dword of input
    outputPtr[0] = 2;
    outputPtr[1] = inputPtr[1];
    return;
}