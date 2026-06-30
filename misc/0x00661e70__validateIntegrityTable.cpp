// FUNC_NAME: validateIntegrityTable
// Address: 0x00661e70
// Role: Iterates over a table of integrity-check entries (0x44 bytes each) and performs hash-based validation.
// Each entry contains: [size at offset -4?], then 0x20-byte expected hash?, then 0x10-byte input? Actually:
//   entry points to &DAT_00e4386c, then offset -4 used as size parameter.
//   entry+0x20 holds some expected value, entry+0x30 holds another expected value.
// The function computes a hash then checks it matches, also verifies that after 1000 rounds the hash zeroes.

#include <string.h> // for memset

// Forward declarations of callees (addressed in executable)
extern int decryptData(void* dataPtr, int size, int key, unsigned char* output);
extern void hashRound1(const unsigned char* input, unsigned char* state, const unsigned char* key);
extern void hashRound2(const unsigned char* state, unsigned char* output, const unsigned char* key);

// External table of integrity entries (each 0x44 bytes)
extern unsigned char gIntegrityTableStart[];
// The loop ends when ptr reaches gIntegrityTableEnd (0x00e43937)
const unsigned char* gIntegrityTableEnd = (unsigned char*)0x00e43937;

int validateIntegrityTable(void)
{
    int result;
    unsigned int i;
    int cmpResult;
    unsigned char* entryPtr;
    unsigned char state[16]; // local_10d0
    unsigned char buffer[4284]; // local_10c0

    // Place a signature at the end of the buffer: address of this function + 0x10? (0x00661e80)
    buffer[0x10ac] = 0x80;
    buffer[0x10ad] = 0x1e;
    buffer[0x10ae] = 0x66;
    buffer[0x10af] = 0x00;

    entryPtr = gIntegrityTableStart;

    do {
        // Clear the work area (except the signature at the end)
        memset(buffer + 0x10, 0, 0x10a0);

        // Decrypt or process entry data
        // First param: entryPtr, second: 4-byte size stored just before entry (offset -4), third: key=0, output=buffer+0x10
        result = decryptData(entryPtr, *(int*)(entryPtr - 4), 0, buffer + 0x10);
        if (result != 0) {
            return result;
        }

        // Compute first hash: from entry+0x20 and buffer+0x10 -> state
        hashRound1(entryPtr + 0x20, state, buffer + 0x10);
        // Compute second hash: from state and buffer+0x10 -> something? Actually output to buffer[0..15]
        hashRound2(state, buffer, buffer + 0x10);

        // Compare state with expected value at entry+0x30 (16 bytes)
        cmpResult = 0;
        for (i = 0; i < 16; i++) {
            if (state[i] != entryPtr[0x30 + i]) {
                // Flag set based on signed comparison (must be equal)
                if (state[i] < entryPtr[0x30 + i]) {
                    cmpResult = -1;
                } else {
                    cmpResult = 1;
                }
                break;
            }
        }
        if (cmpResult != 0) {
            return 5;
        }

        // Compare the first 16 bytes of buffer with entry+0x20 (must match)
        cmpResult = 0;
        for (i = 0; i < 16; i++) {
            if (buffer[i] != entryPtr[0x20 + i]) {
                if (buffer[i] < entryPtr[0x20 + i]) {
                    cmpResult = -1;
                } else {
                    cmpResult = 1;
                }
                break;
            }
        }
        if (cmpResult != 0) {
            return 5;
        }

        // Zero state and run 1000 rounds of hashRound1 and hashRound2
        // If state not all zero after that, return 5
        memset(state, 0, 16);
        for (int x = 0; x < 1000; x++) {
            hashRound1(state, state, buffer + 0x10);
        }
        for (int x = 0; x < 1000; x++) {
            hashRound2(state, state, buffer + 0x10);
        }
        for (i = 0; i < 16; i++) {
            if (state[i] != 0) {
                return 5;
            }
        }

        // Advance to next entry (0x44 bytes per entry)
        entryPtr += 0x44;
    } while (entryPtr <= gIntegrityTableEnd);

    return 0; // All entries validated
}