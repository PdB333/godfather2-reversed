// FUNC_NAME: decompressData
// Role: Core decompression function for EARS engine (likely LZSS/Huffman)
// Address: 0x00662a30
// Parameters:
//   decompContext - pointer to decompression context/state (int*)
//   inputData - source compressed data
//   outputData - destination for decompressed data
//   sizeInfo - pointer to size/offset info

#include <stdlib.h>
#include <string.h>

// Forward declarations of internal helpers (from other functions)
int FUN_00665720(int size);       // allocate or check memory
int FUN_00665d70(int* arg1, int* arg2, int* arg3, int arg4); // setup stream?
void FUN_00665b40();              // error handling?
void* FUN_00667820(void* ptr, int offset, int flag); // initialize structure?
void FUN_00665b80(void* ptr, int offset, int flag); // cleanup structure?
int FUN_006624a0(void* dest, void* src, int* size); // copy/move data
int FUN_006626f0(void* arg1, void* arg2, void* arg3, int* arg4, int* size); // decode step
int FUN_00665ce0();               // random number generator?

int decompressData(int* decompContext, void* inputData, void* outputData, int* sizeInfo) {
    bool flag;
    int ret;
    void* tempBuffer;
    void* tempArray[8]; // array of 8 temporary structures (0x20 bytes each)
    void* extraBlock;   // additional temporary structure
    void* contextBlock; // main context block (0x40 bytes)
    int local_c[3];     // size related array
    uint bits;          // bit buffer
    uint nibble;        // accumulated nibble
    int loopCount;
    int counter;
    uint bitCount;

    // Allocate main context block (0x40 bytes, 4*0x10?)
    contextBlock = calloc(4, 0x40);
    if (contextBlock == NULL) {
        // Fallback error handling using global table at 0x00e2747c and 0x00e27480
        for (int i = 0; i < 3; i++) {
            if (*(short*)(0x00e2747c + i * 2) == -2) {
                return *(int*)(0x00e27480 + i * 8);
            }
        }
        return 1; // error
    }

    // Set up local size array
    local_c[0] = 0;
    local_c[1] = 0x40; // size of 64
    local_c[2] = 0;

    // Perform memory allocation/initialization based on sizeInfo[0] * 0x38
    int memSize = *sizeInfo * 0x38;
    int initResult = FUN_00665720(memSize);
    if (initResult == 0) {
        initResult = FUN_00665d70(local_c, sizeInfo, local_c, 0);
    }

    if (initResult != 0) {
        // Error: check global table
        FUN_00665b40();
        for (int i = 0; i < 3; i++) {
            if (initResult == *(short*)(0x00e2747c + i * 2)) {
                return *(int*)(0x00e27480 + i * 8);
            }
        }
        return 1;
    }

    // Allocate 8 temporary structures (0x20 bytes each)
    for (int i = 0; i < 8; i++) {
        tempArray[i] = malloc(0x20);
        if (tempArray[i] == NULL) {
            // Cleanup previously allocated
            for (int j = 0; j < i; j++) {
                if (tempArray[j] != NULL) {
                    FUN_00665b80(tempArray[j], (int)tempArray[j] + 0x10, 0);
                    free(tempArray[j]);
                }
            }
            free(contextBlock);
            return 0xD; // out of memory error
        }
        // Initialize the structure
        int err = FUN_00667820(tempArray[i], (int)tempArray[i] + 0x10, 0);
        if (err != 0) {
            free(tempArray[i]);
            // fallback: set to NULL
            tempArray[i] = NULL;
            // cleanup previous
            for (int j = 0; j < i; j++) {
                if (tempArray[j] != NULL) {
                    FUN_00665b80(tempArray[j], (int)tempArray[j] + 0x10, 0);
                    free(tempArray[j]);
                }
            }
            free(contextBlock);
            return 0xD;
        }
    }

    // Allocate extra block (0x20 bytes)
    extraBlock = malloc(0x20);
    if (extraBlock == NULL) {
        // Cleanup
        for (int i = 0; i < 8; i++) {
            if (tempArray[i] != NULL) {
                FUN_00665b80(tempArray[i], (int)tempArray[i] + 0x10, 0);
                free(tempArray[i]);
            }
        }
        free(contextBlock);
        return 0xD;
    }
    // Initialize extra block
    int errInit = FUN_00667820(extraBlock, (int)extraBlock + 0x10, 0);
    if (errInit != 0) {
        free(extraBlock);
        extraBlock = NULL;
        // fallthrough
    }

    // Use the first temp structure to decode header?
    ret = FUN_006624a0(inputData, tempArray[0], local_c);
    if (ret == 0) {
        ret = FUN_006624a0(tempArray[0], tempArray[0], local_c);
        if (ret == 0) {
            ret = FUN_006624a0(tempArray[0], tempArray[0], local_c);
        }
    }

    // Iterate with 9+1? from index 9 to 15 (total 8 steps)
    int idx = 9;
    if (ret == 0) {
        for (; idx < 0x10; idx++) {
            ret = FUN_006626f0(tempArray[idx-9], inputData, tempArray[idx-8], sizeInfo, local_c);
            if (ret != 0) break;
        }
    }

    if (ret == 0) {
        // Insert two random calls (maybe for initialization)
        ret = FUN_00665ce0();
        if (ret == 0) {
            ret = FUN_00665ce0();
        }
    }

    if (ret == 0) {
        // Main decompression loop
        int runLength = 1;
        int remainingBits = *decompContext - 1; // initial bit count
        bool firstRun = true;
        uint bitBuffer = 0;
        int state = 0;
        int nibbleCount = 0;
        uint totalNibble = 0;

        do {
            int nibbleBitCount = 0;
            uint nibbleAccum = 0;
            do {
                runLength--;
                if (runLength == 0) {
                    if (remainingBits == -1) {
                        // End of input?
                        if ((state != 2) || (nibbleBitCount < 1)) {
                            // Check if we need to flush extra bits
                            //...
                            goto exit_clean;
                        }
                        // continue?
                    } else {
                        // Read next 32-bit word from context
                        bitBuffer = *(uint*)(decompContext[3] + remainingBits * 4);
                        remainingBits--;
                        runLength = 0x1c; // 28 bits to process
                    }
                }
                uint temp = bitBuffer;
                bitBuffer = bitBuffer * 2; // shift left? Actually multiply by 2, but in binary it's left shift
                uint bit = temp >> 0x1b & 1; // Extract the most significant bit of previous value?
                if (state == 0) {
                    if (bit != 0) {
                        // continue reading
                    } else {
                        goto continue_loop;
                    }
                } else if (state == 1) {
                    if (bit != 0) {
                        goto continue_loop;
                    }
                    // State 1 with bit==0: do something with outputData and local_c
                    int tmp = FUN_006624a0(outputData, outputData, local_c);
                    if (tmp != 0) goto error_clean;
                    goto continue_loop;
                }
                // Accumulate bit for nibble
                nibbleBitCount++;
                nibbleAccum = nibbleAccum | (bit << (4 - nibbleBitCount));
            } while (nibbleBitCount != 4);

            if (firstRun) {
                // Random calls again
                int tmp2 = FUN_00665ce0();
                if (tmp2 != 0 || (tmp2 = FUN_00665ce0()) != 0) goto error_clean;
                firstRun = false;
                state = 1;
                bitBuffer = temp; // restore? actually bitBuffer is already shifted
                // continue outer loop
                continue;
            } else {
                // Process nibble: output 4 copies of some pattern?
                for (int j = 0; j < 4; j++) {
                    int tmp3 = FUN_006624a0(outputData, outputData, local_c);
                    if (tmp3 != 0) goto error_clean;
                }
                // Use the decoded nibble as index into extraBlock?
                int tmp4 = FUN_006626f0(outputData, ((int*)(&runLength))[nibbleAccum], outputData, sizeInfo, local_c);
                if (tmp4 != 0) break;
                state = 1;
                bitBuffer = temp;
                continue;
            }
            continue_loop:
            // Continue reading bits without consuming runLength? Actually the loop structure is tricky
            // The decompiled code has a goto back to the outer loop at 0x00662d2e
            // This is missing some context
        } while (true);
    }

error_clean:
    ret = 0xD; // error code
exit_clean:
    // Cleanup all allocations
    if (extraBlock != NULL) {
        FUN_00665b80(extraBlock, (int)extraBlock + 0x10, 0);
        free(extraBlock);
    }
    for (int i = 0; i < 8; i++) {
        if (tempArray[i] != NULL) {
            FUN_00665b80(tempArray[i], (int)tempArray[i] + 0x10, 0);
            free(tempArray[i]);
        }
    }
    if (contextBlock != NULL) {
        memset(contextBlock, 0, local_c[0] * 4);
        free(contextBlock);
    }
    return ret; // return error code or 0 for success
}