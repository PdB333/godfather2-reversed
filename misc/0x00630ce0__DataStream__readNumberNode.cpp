// FUNC_NAME: DataStream::readNumberNode
// Function at 0x00630ce0: Reads a number node from a binary data stream (token 3 or 4) and writes token 3 + float to output.
// Handles missing sentinel values by skipping tokens and printing "number" debug messages.
// Structure offsets: +0x8 = m_writePos (output write pointer), +0xc = m_readPos (input read pointer)
// Both pointers point into the same buffer; read is consumed from m_readPos, output is written at m_writePos.
// Token types: 3 = number, 4 = variable reference (resolved via FUN_00636850)
// Returns 1 on success, 0 if no data available.

#include <cstdint>

// Forward declarations for external functions
int __cdecl FUN_00636850(float* outFloat); // Resolves a float from token 4 context
void __cdecl FUN_00627ac0(const char* msg); // Debug print
void __cdecl FUN_00b99fcb(); // Unknown float processing (clamp/round)

// Constants
const float kMissingNumberSentinel = 0.0f; // DAT_00e2b05c likely a sentinel like 0.0 or NaN

struct DataStream {
    uint8_t* m_writePos;  // +0x8 - Current output write position (also end of read region)
    uint8_t* m_readPos;   // +0xc - Current input read position
};

int __thiscall DataStream::readNumberNode(DataStream* thisPtr) {
    float numberValue;
    int* piVar3;
    int iConvResult;
    float localFloat;
    int localToken; // Used for token 4 conversion

    // Read from current read position
    piVar3 = reinterpret_cast<int*>(thisPtr->m_readPos);

    // Check if there's data to read (readPos < writePos)
    if (reinterpret_cast<uint8_t*>(piVar3) >= thisPtr->m_writePos) {
        goto noData;
    }
    if (piVar3 == nullptr) {
        goto noData;
    }

    // Process token type
    if (*piVar3 != 3) { // Not a number token?
        if (*piVar3 != 4) { // Not a reference token either
            goto noData;
        }
        // Token 4: resolve its float value via an external function
        if (FUN_00636850(&numberValue) == 0) {
            goto noData;
        }
        // Convert token 4 into a token 3 with the resolved float
        localToken = 3;
        localFloat = numberValue;
        piVar3 = &localToken; // Point to the temporary token
    }

    // Extract the float value (always at offset +4 from token)
    numberValue = static_cast<float>(piVar3[1]);

    // If the value matches the missing sentinel, try to skip junk tokens
    if (numberValue == kMissingNumberSentinel) {
        // Loop: advance read pointer until we find a valid token with non-sentinel value
        while (true) {
            piVar3 = reinterpret_cast<int*>(thisPtr->m_readPos);
            // Check buffer boundaries and token validity
            if (reinterpret_cast<uint8_t*>(piVar3) >= thisPtr->m_writePos || piVar3 == nullptr) {
                // No valid token found
                FUN_00627ac0("number");
                goto noData;
            }
            if (*piVar3 == 3) {
                // Valid token 3: break with its float value
                numberValue = static_cast<float>(piVar3[1]);
                if (numberValue != kMissingNumberSentinel) {
                    break; // Found a valid non-sentinel number
                }
                // Sentinal again: skip and continue
            } else if (*piVar3 == 4) {
                // Token 4: try to resolve
                if (FUN_00636850(&numberValue) != 0) {
                    // Conversion succeeded; use the resolved float
                    numberValue = static_cast<float>(numberValue);
                    // Check if the resolved value is also a sentinel? The original code doesn't check
                    // but it breaks after assignment.
                    break;
                }
            }
            // Token not valid: print warning and skip it (advance read pointer by 8 bytes?)
            // The original code prints "number" and then goes to noData which sets numberValue=0.
            // But it also loops. We need to track read pointer advancement. The original while loop
            // does not explicitly advance the read pointer; but the condition re-reads from m_readPos.
            // It never advances m_readPos, which would cause an infinite loop.
            // This suggests the loop body should advance the read pointer. Possibly the missing
            // advancement happens inside FUN_00636850 or after the print. But the decompiled code
            // does not show any increment. There might be an implicit increment in FUN_00627ac0?
            // Or the token skip is done by advancing m_readPos by 8 in the loop body.
            // Given the ambiguity, we'll advance m_readPos by 8 (size of token + float) after printing.
            // For a more accurate reconstruction, we'll mimic the original by using a goto that
            // sets numberValue to 0 and then continues the loop? The original structure:
            // while (condition) { FUN_00627ac0; LAB_00630d9b: numberValue=0; }
            // The goto from earlier jumps to noData which sets numberValue=0, then the while
            // condition is re-evaluated (without advancing). That would be infinite.
            // Likely the condition also updates piVar3? Let's assume that the token is consumed
            // by advancing m_readPos by 8 after each iteration (common in such parsers).
            thisPtr->m_readPos += 8;
            FUN_00627ac0("number");
        }
    }

    // Write output: token 3 (number) followed by float value
    uint32_t* outPtr = reinterpret_cast<uint32_t*>(thisPtr->m_writePos);
    *outPtr = 3; // Token type 3
    double dblVal = static_cast<double>(numberValue);
    FUN_00b99fcb(); // Unknown float processing
    outPtr[1] = static_cast<float>(dblVal); // Write possibly clamped/rounded float
    thisPtr->m_writePos += 8; // Advance write pointer by 8 bytes

    return 1;

noData:
    numberValue = 0.0f;
    // Fall through: write the sentinel number? The original code always writes token 3 after the while.
    // But if we goto noData, we skip the write? Actually the goto leads to setting numberValue=0,
    // but then the code continues to the write part? In the original, the goto LAB_00630d9b is inside
    // the while loop, but after setting numberValue=0, it does not exit the loop; it re-evaluates
    // the condition. That would cause an infinite loop with numberValue=0. That's likely a bug in
    // decompilation or the actual control flow is different.
    // For safety, we'll return 0 on noData to indicate failure.
    return 0;
}