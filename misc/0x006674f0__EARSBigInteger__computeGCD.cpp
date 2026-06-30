// FUNC_NAME: EARSBigInteger::computeGCD
// Purpose: Computes greatest common divisor (GCD) of two big integers using a binary GCD-like algorithm.
// Assumes big integer structures with opaque handles (64-bit packed values storing pointer + offset).

#include <cstdint>
#include <cstring>
#include <cstdlib>

// Forward declarations of internal big integer operations (assumed to be in game engine)
namespace BigInt {
    // Initialize a big integer handle from external data (modifies global state?)
    int Initialize();

    // Allocate a new big integer buffer and return handle via first argument
    int AllocateFrom(uint64_t &handle);

    // Get number of significant bits in the big integer
    int GetNumBits(uint64_t handle);

    // Shift right by n bits (in-place): handle = handle >> n
    int ShiftRight(uint64_t &handle, int nBits, uint64_t &out, int unknown);

    // Compare two handles: returns 1 if a > b, 0 if a <= b (or maybe other values?)
    int Compare();

    // Compute modulus (handleA % handleB) with result stored in handleA
    int Mod(uint64_t &handleA, uint64_t handleB);

    // Final validation: returns 0 if result is normalized/valid
    int CheckNormalized(int maxBits);

    // Free/destroy a big integer handle
    void Destroy(uint64_t handle);

    // Possibly another shift function for positive offset
    // (not used explicitly but implied)
}

// Main GCD function
int EARSBigInteger::computeGCD(int *a, int *b) {
    uint64_t handleA; // packed handle for first operand (a)
    uint64_t handleB; // packed handle for second operand (b)
    uint64_t tempA;   // temporary for swapped values
    uint64_t tempB;
    int result = 0;

    // 'this' contains a flag (first member) indicating mode
    if (*((int*)this) == 0) {
        // Fast path: use existing data
        if (*a == 0) {
            // Both a and b zero? Clear output
            b[2] = 0;
            *b = 0;
            memset((void*)b[3], 0, b[1] * 4);
            return 0;
        }
        if (a == b) goto setZero;
    } else {
        if (*a != 0) {
            if (*((int*)this) != 0) {
                // Allocate working buffers
                void *buffer = calloc(4, 0x40); // 0x40 = 64 * 4 = 256 bytes
                if (buffer == nullptr) return -2;

                // Pack pointer into handle (high 32 bits of 64-bit handle)
                handleA = 0; // will be set later
                handleB = 0;
                // Actually in the asm: local_18 = 0x4000000000, local_10 = ptr << 32
                handleA = 0x4000000000ULL; // presumably flags
                handleB = reinterpret_cast<uint64_t>(buffer) << 32;

                // Initialize big integer system
                result = BigInt::Initialize();
                if (result != 0) return result;

                // Allocate internal representations for a and b
                result = BigInt::AllocateFrom(handleA);
                if (result == 0) {
                    // Clear lower 32 bits of handles (part of protocol)
                    handleA &= 0xFFFFFFFF00000000ULL;
                    handleB &= 0xFFFFFFFF00000000ULL;

                    int bitsA = BigInt::GetNumBits();
                    int bitsB = BigInt::GetNumBits();
                    int minBits = (bitsA < bitsB) ? bitsA : bitsB;

                    if (minBits >= 1) {
                        // Shift both numbers right by minBits to normalize
                        result = BigInt::ShiftRight(handleA, minBits, handleA, 0);
                        if (result == 0) {
                            result = BigInt::ShiftRight(handleB, minBits, handleB, 0);
                            if (result == 0) {
                                // If one number had more bits, shift it more
                                if (bitsA != minBits) {
                                    result = BigInt::ShiftRight(handleA, bitsA - minBits, handleA, 0);
                                    if (result != 0) goto cleanup;
                                }
                                if (bitsB != minBits) {
                                    result = BigInt::ShiftRight(handleB, bitsB - minBits, handleB, 0);
                                    if (result != 0) goto cleanup;
                                }

                                // Binary GCD main loop
                                while (true) {
                                    // Break if handleB is zero
                                    uint64_t lowB = handleB & 0xFFFFFFFF;
                                    if (lowB == 0) break;

                                    // Compare the two numbers (implementation detail: uses global register)
                                    int cmp = BigInt::Compare(); // returns 1 if handleA > handleB
                                    if (cmp == 1) {
                                        // Swap handles (simulate extended Euclid step)
                                        tempA = handleA;
                                        tempB = handleB & 0xFFFFFFFF00000000ULL; // keep high part?
                                        // Actually the swap is of the whole 64-bit values
                                        handleA = (handleB & 0xFFFFFFFF00000000ULL) | (tempB & 0xFFFFFFFF);
                                        // This is messy; we simplify as full swap
                                        uint64_t swap = handleA;
                                        handleA = handleB;
                                        handleB = swap;
                                    }

                                    // Compute modulus: handleB = handleA % handleB
                                    result = BigInt::Mod(handleB, handleA);
                                    if (result != 0) break;

                                    // Right-shift handleB by some amount (extract quotient bits)
                                    int shiftAmt = BigInt::GetNumBits();
                                    result = BigInt::ShiftRight(handleB, shiftAmt, handleB, 0);
                                    if (result != 0) break;
                                }

                                if (result == 0) {
                                    // Final check on result (could be checking if GCD is 1)
                                    result = BigInt::CheckNormalized(minBits);
                                    if (result == 0) {
                                        b[2] = 0; // indicate success
                                    }
                                }
                                // Cleanup
                                BigInt::Destroy(handleA);
                                BigInt::Destroy(handleB);
                            }
                        }
                    }
                }
                // Free temporary buffer
                free(buffer);
                return result;
            } else {
                goto clearOutput;
            }
        } else {
            if (this == b) goto setZero;
        }
    }

    // Fallback: initialize and set output to zero
    result = BigInt::Initialize();
    if (result != 0) return result;

setZero:
    b[2] = 0;
    return 0;

clearOutput:
    b[2] = 0;
    *b = 0;
    memset((void*)b[3], 0, b[1] * 4);
    return 0;
}