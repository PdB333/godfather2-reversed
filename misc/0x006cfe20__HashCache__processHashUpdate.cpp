// FUNC_NAME: HashCache::processHashUpdate
// Function at 0x006cfe20 - Compares and updates a stored hash from a 4-int identifier.
// If the new hash (computed via polynomial: (((id[0]*0x21+id[1])*0x21+id[2])*0x21+id[3])) differs from the cached one (at this+0xCC),
// it processes the new identifier (converts to string, calls virtual methods) and stores the new hash.
// Input: this = pointer to HashCache object, param_2 = pointer to 4 ints (e.g., a GUID or hash tuple)

// Known offsets:
// this+0x32 (int) - flag/version? (checked before processing)
// this+0x33 (int) - cached hash value (offset 0xCC)
// this+0x00 (vtable) - virtual methods at offsets 0x24 (buildStringFromHash?), 0x3c (release?)

#include <cstdint>

class HashCache {
public:
    // Virtual table at offset 0
    virtual void buildStringFromHash(void* buffer) = 0;   // vtable+0x24
    virtual void releaseString(void* param) = 0;          // vtable+0x3c
private:
    int field_0x32;   // +0x32 (0xC8) - used as flag before processing
    int cachedHash;   // +0x33 (0xCC) - stored hash
    // ... other fields
};

// Forward declaration of external functions
uint32_t FUN_00410540(uint32_t val);  // Some hash/version resolver
void FUN_004df600();                  // Reset/cleanup function
uint32_t FUN_004df270(int* outPtr, int* inputInts, char* buffer, int maxLen, int unknown, uint* pFlag);  // Convert hashes to string
void FUN_00414db0(uint32_t val);      // Debug output / print

void __fastcall HashCache::processHashUpdate(HashCache* this, void* /*edx*/, int* param_2) {
    // Early: check some global object's vtable
    uint32_t** pGlobalObj = *(uint32_t***)(DAT_012233a0 + 4); // global pointer dereference
    uint32_t local_6c = 0; // byte buffer? used later
    if (pGlobalObj != nullptr && pGlobalObj != (uint32_t**)0x1f30) {
        uint32_t uVar2 = (*(code**)(*pGlobalObj + 8))(); // call vtable+8 (some version method)
        int iVar3 = FUN_00410540(uVar2);  // likely converts to version/flag
        local_6c = (local_6c & 0xFFFFFF00) | (*(uint8_t*)(iVar3 + 0x11));
    }

    // Compute new hash using polynomial: (((id[0]*0x21 + id[1])*0x21 + id[2])*0x21 + id[3])
    int newHash = (((param_2[0] * 0x21 + param_2[1]) * 0x21 + param_2[2]) * 0x21 + param_2[3];

    if (this->cachedHash != newHash) {
        // If the flag at +0x32 is non-zero, call a reset function first
        if (this->field_0x32 != 0) {
            FUN_004df600();
        }

        // Check if the new identifier matches a known "null" or "invalid" hash
        // Special sentinel values: { -0x45245246, -0x41104111, -0x153ea5ab, -0x6eeff6ef } or all zeros
        bool isSpecialHash = (param_2[0] == -0x45245246 && param_2[1] == -0x41104111 && 
                              param_2[2] == -0x153ea5ab && param_2[3] == -0x6eeff6ef);
        bool isZeroHash = (param_2[0] == 0 && param_2[1] == 0 && param_2[2] == 0 && param_2[3] == 0);

        // Only process if it's not special and not zero
        if (!isSpecialHash && !isZeroHash) {
            // Initialize a stack buffer for string representation of the 4 ints
            // This looks like a 4x4-byte block structure (possibly 4 rows of 16 bytes)
            // Observed initialization: first row: [_DAT_00d5780c, 0,0,0], second: similar, etc.
            // We'll define it as an array of 4 uint32_t[4] but the code uses separate variables.
            uint32_t row1[4] = { _DAT_00d5780c, 0, 0, 0 };
            uint32_t row2[4] = { _DAT_00d5780c, 0, 0, 0 };
            uint32_t row3[4] = { _DAT_00d5780c, 0, 0, 0 };
            uint32_t row4[4] = { _DAT_00d5780c, 0, 0, 0 };
            // Actually the decompiler had them interleaved; we keep logical structure.
            uint32_t* bufferPtr = row3; // the address passed to vtable+0x24 (pointing to row3)

            // Call virtual method at +0x24 to fill the buffer with string representation
            this->buildStringFromHash(bufferPtr);

            // Prepare input ints for conversion
            int inputCopy[4];
            inputCopy[0] = param_2[0];
            inputCopy[1] = param_2[1];
            inputCopy[2] = param_2[2];
            inputCopy[3] = param_2[3];

            int resultPtr = 0;
            char stringBuffer[0x200]; // 512 bytes, but max length 0x1ff
            local_6c = 0; // reset flag byte (used in conversion)

            uint32_t convResult = FUN_004df270(&resultPtr, inputCopy, stringBuffer, 0x1ff, 0, &local_6c);
            FUN_00414db0(convResult); // Likely print the string

            // If the conversion returned a non-null pointer, clear a field at offset +8
            if (resultPtr != 0) {
                *(int*)(resultPtr + 8) = 0;
            }

            // Call virtual method at +0x3c with the original buffer (from earlier? the call uses uStack_70 which is uninitialized? Actually uStack_70 is on the stack but not assigned)
            // The decompiler shows: (**(code**)(*param_1 + 0x3c))(uStack_70); 
            // uStack_70 is likely a variable left from an earlier call, but in the decompiler it's not assigned.
            // Likely the release method takes the same buffer pointer or something.
            // We'll call it with the buffer pointer passed to buildStringFromHash (row3)
            this->releaseString(bufferPtr);
        }

        // Update cached hash
        this->cachedHash = newHash;
    }
    return;
}