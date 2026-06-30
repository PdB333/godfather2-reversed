// FUNC_NAME: StreamProcessor::processFloat
// Function at 0x00631d10: Reads a float from input stream, optionally generates a random float, and writes it to output stream.
// Structure offsets: +0x8 = writePtr, +0xc = readPtr (pointers to 8-byte entries: int type + float value)

#include <cstdint>

// Forward declarations of called functions
int FUN_00636850(float* outFloat); // Possibly random float generator, returns 1 on success
void FUN_00627ac0(const char* msg); // Debug print
void FUN_00b9be2b(); // Unknown, possibly float-to-double conversion helper

// Sentinel value (likely NaN or a special marker)
extern float DAT_00e2b05c;

// Entry types
enum EntryType : int {
    TYPE_3 = 3,
    TYPE_4 = 4
};

struct StreamProcessor {
    // +0x8: write pointer (current position in output buffer)
    int* writePtr;
    // +0xc: read pointer (current position in input buffer)
    int* readPtr;
};

int StreamProcessor::processFloat(void* self) {
    StreamProcessor* sp = (StreamProcessor*)self;
    int* piVar3 = sp->readPtr;
    
    // Check if there is data to read (readPtr < writePtr)
    if (sp->writePtr <= piVar3) goto noData;
    if (piVar3 == nullptr) goto noData;
    
    if (*piVar3 != TYPE_3) {
        if (*piVar3 != TYPE_4) goto noData;
        // Type 4: generate a float from external source (e.g., random)
        float generatedFloat;
        int result = FUN_00636850(&generatedFloat);
        if (result == 0) goto noData;
        
        // Create a temporary entry with type 3 and the generated float
        int tempType = TYPE_3;
        float tempFloat = generatedFloat;
        piVar3 = &tempType; // point to local stack entry
    }
    
    // Read the float from the entry (either original or generated)
    float local_14 = *(float*)(piVar3 + 1); // piVar3[1] is the float
    
    // Check for sentinel value
    if (local_14 == DAT_00e2b05c) {
        // Sentinel found: skip entries until a non-sentinel is found
        while (true) {
            piVar3 = sp->readPtr;
            if (sp->writePtr <= piVar3 || piVar3 == nullptr) break;
            if (*piVar3 == TYPE_3) break;
            if (*piVar3 == TYPE_4) {
                int result = FUN_00636850(&tempType); // Note: tempType is reused, but result ignored? Actually original code uses &local_10
                if (result != 0) break;
            }
            // Debug print and loop again (but readPtr is not advanced - potential infinite loop)
            FUN_00627ac0("number");
        }
        // If we exited the loop without finding a valid entry, set float to 0
        local_14 = 0.0f;
    }
    
    // Write the entry to output buffer
    int* puVar1 = sp->writePtr;
    *puVar1 = TYPE_3; // write type
    double dVar4 = (double)local_14;
    FUN_00b9be2b(); // unknown conversion helper
    *(float*)(puVar1 + 1) = (float)dVar4; // write float
    sp->writePtr = sp->writePtr + 2; // advance by 2 ints (8 bytes)
    
    return 1;

noData:
    local_14 = 0.0f;
    // Fall through to write zero
    int* puVar1 = sp->writePtr;
    *puVar1 = TYPE_3;
    double dVar4 = (double)local_14;
    FUN_00b9be2b();
    *(float*)(puVar1 + 1) = (float)dVar4;
    sp->writePtr = sp->writePtr + 2;
    return 1;
}