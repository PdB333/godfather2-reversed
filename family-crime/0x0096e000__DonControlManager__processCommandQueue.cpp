// FUNC_NAME: DonControlManager::processCommandQueue
// Address: 0x0096e000
// This function processes a queue of commands (0x114 bytes each) protected by a critical section.
// It reads commands from a circular buffer and dispatches based on command type.
// The command types (1-0xD) handle various multiplayer/Don Control actions.

#include <windows.h>

// Forward declarations for called functions (assumed to be members or globals)
void FUN_00968cc0(void* commandEntry); // Reads command data into local/global state
void FUN_008b5c30(int index); // Returns some value (maybe a player ID)
void FUN_008b5c50(int index);
void FUN_00982c90();
void FUN_00965a30(int a, int b);
void FUN_0096a3f0(int a, int b);
void FUN_00962f90(int a, int b);
void FUN_00962f70();
void FUN_008a2d90();
int FUN_008a3010(void** table, int index);
void FUN_00969bd0(int a, void* buffer);
void FUN_00969ca0(int a);
void FUN_00964640(void* buffer, int a);
void FUN_009646b0(int a);
void FUN_0095ecd0();
void FUN_008a30d0();
void FUN_008a3790(void** table);
void FUN_00962e80(void* buffer);
int FUN_009c8e50(int size);
int FUN_00982280(int a);
void FUN_00981eb0(const char* string);
void FUN_00982e10();
int FUN_0096a2c0();
void FUN_00964580(int a);
void FUN_009645f0();
void FUN_00983190();
void FUN_00965b20(int a, int b, int c);
void FUN_00965ba0(int a, int b, int c);
void FUN_0096dad0();
void FUN_00967f10();
void FUN_00967f50();

// Global data references
extern int* DAT_01223484; // Pointer to some manager structure
extern CRITICAL_SECTION DAT_011308c0; // Critical section for queue access
extern int DAT_011307f0; // Some global flag
extern float* DAT_01129908; // Pointer to a float array (e.g., time values)
extern void* PTR_LAB_00d79770; // Pointer to a string table or similar

class DonControlManager {
public:
    // Member offsets (based on param_1 usage)
    // +0x48: char m_bSomeFlag
    // +0xB0: void* m_pCommandBuffer
    // +0xB4: int m_commandBufferCapacity
    // +0xB8: int m_commandReadIndex
    // +0xBC: int m_commandCount
    // +0x1E0: int m_someLimit
    // +0x1E8: int m_someValue
    // +0x221: char m_bAnotherFlag
    // +0x338: int** m_pArrayOfPointers
    // +0x33C: int m_arrayCount
    // +0x500: char m_bFlagAt500
    // +0x6F1: bool m_bFlagAt6F1
    // +0x6F4: uint m_flags

    void processCommandQueue() {
        int* pManager = DAT_01223484;
        if (pManager == nullptr) {
            return;
        }

        // Loop until command queue is empty
        while (true) {
            if (m_commandCount == 0) {
                break;
            }

            bool bCommandProcessed = false;
            void* pStringTable = &PTR_LAB_00d79770; // Used in some cases
            int commandType = 0; // Will be set by FUN_00968cc0
            int param1 = 0;
            int param2 = 0;
            int param3 = 0;

            EnterCriticalSection(&DAT_011308c0);

            if (m_commandCount != 0) {
                int readIndex = m_commandReadIndex;
                // Calculate pointer to current command entry (each 0x114 bytes)
                void* pCommandEntry = (char*)m_pCommandBuffer + readIndex * 0x114;
                // This function reads the command and likely sets commandType and params
                FUN_00968cc0(pCommandEntry);

                readIndex++;
                m_commandReadIndex = readIndex;
                if (m_commandBufferCapacity <= readIndex) {
                    m_commandReadIndex = 0;
                }
                m_commandCount--;
                bCommandProcessed = true;
            }

            LeaveCriticalSection(&DAT_011308c0);

            if (bCommandProcessed && m_bSomeFlag != 0) {
                switch (commandType) {
                case 1: {
                    int val1 = FUN_008b5c30(0);
                    int val2 = FUN_008b5c50(0);
                    if (pManager[2] == 0) { // pManager[2] is offset 8, likely a flag
                        FUN_00982c90();
                        FUN_00965a30(val2, val1);
                    } else {
                        FUN_0096a3f0(param3, val1);
                    }
                    break;
                }
                case 2: {
                    int val1 = FUN_008b5c30(0);
                    int val2 = FUN_008b5c30(1);
                    if (pManager[2] == 0) {
                        FUN_00962f90(val1, val2);
                    }
                    break;
                }
                case 3: {
                    if (pManager[2] == 0) {
                        FUN_00962f70();
                    }
                    break;
                }
                case 4: {
                    int val = FUN_008b5c30(0);
                    m_flags |= 0x200;
                    m_bFlagAt6F1 = (val == 1);
                    break;
                }
                case 5: {
                    FUN_008a2d90();
                    int index = FUN_008a3010(&pStringTable, 0);
                    FUN_00969bd0(param3, &pStringTable); // Note: auStack_70 is actually pStringTable? Decompiler reused local
                    FUN_00969ca0(param3);
                    FUN_00964640(&pStringTable, param3);
                    break;
                }
                case 6: {
                    FUN_00982c90();
                    uint count = param1;
                    uint i = 0;
                    if (count != 0) {
                        do {
                            int val = FUN_008b5c30(i);
                            FUN_008a2d90();
                            int index = FUN_008a3010(&pStringTable, i + 1);
                            i = i + 1 + index;
                            FUN_00969bd0(val, &pStringTable);
                        } while (i < count);
                    }
                    m_flags |= 4;
                    break;
                }
                case 7: {
                    FUN_009646b0(param3);
                    uint j = 0;
                    if (m_arrayCount != 0) {
                        int** ppArray = m_pArrayOfPointers;
                        do {
                            if ((*ppArray)[0x5c / 4] == param3) { // offset 0x5c
                                int* pEntry = m_pArrayOfPointers[j];
                                if (pEntry != nullptr) {
                                    *(char*)(pEntry + 0x59) = 0; // offset 0x59
                                }
                                break;
                            }
                            j++;
                            ppArray++;
                        } while (j < (uint)m_arrayCount);
                    }
                    break;
                }
                case 8: {
                    DAT_011307f0 = 0;
                    FUN_0095ecd0();
                    FUN_008a30d0();
                    FUN_008a3790(&pStringTable);
                    FUN_00962e80(&pStringTable);
                    if (m_bFlagAt500 != 0 && m_bAnotherFlag != 0) {
                        uint roundedTime = (uint)(int)(*(float*)(DAT_01129908 + 0x14 / 4) + 0.5f);
                        m_someValue = roundedTime;
                        if (roundedTime < (uint)m_someLimit) {
                            m_flags &= 0xFFFFF7FF;
                            // Call virtual function at vtable+0x98
                            (*(void (**)())(*pManager + 0x98))();
                            int result = FUN_009c8e50(0xF0);
                            int ptr = (result != 0) ? FUN_00982280(0) : 0;
                            FUN_00981eb0("$mp_insufficient_funds_play");
                            *(void**)(ptr + 0x14) = (void*)FUN_00982b30; // Note: FUN_00982b30 not listed but assumed
                        } else {
                            if (((m_flags >> 0x14) & 1) == 0 || ((m_flags >> 0x15) & 1) != 0) {
                                goto LAB_0096e3e9;
                            }
                            m_flags |= 0x200000;
                            int result = FUN_009c8e50(0xF0);
                            int ptr = (result != 0) ? FUN_00982280(0) : 0;
                            FUN_00981eb0("$mp_don_changed_settings");
                            *(void**)(ptr + 0x14) = (void*)0x009680d0; // Address of a label
                        }
                        *(int*)(ptr + 0xC) = 3;
                        FUN_00982e10();
                    }
LAB_0096e3e9:
                    if (((m_flags >> 0x14) & 1) == 0) {
                        m_flags |= 0x100000;
                    }
                    break;
                }
                case 9: {
                    int val = FUN_0096a2c0();
                    if (val != 0) {
                        int val2 = FUN_0096a2c0();
                        FUN_00964580(val2);
                        FUN_009645f0();
                        FUN_00983190();
                    }
                    break;
                }
                case 10: {
                    int val1 = FUN_008b5c30(0);
                    int val2 = FUN_008b5c30(1);
                    if (pManager[2] == 0) {
                        FUN_00982c90();
                        int val3 = FUN_008b5c50(0);
                        FUN_00965b20(val3, val1, val2);
                    } else {
                        FUN_00965ba0(param3, val1, val2);
                    }
                    break;
                }
                case 0xB: {
                    FUN_0096dad0();
                    break;
                }
                case 0xC: {
                    FUN_00967f10();
                    break;
                }
                case 0xD: {
                    FUN_00967f50();
                    break;
                }
                default:
                    break;
                }
            }
        }
    }

private:
    // Member variables (inferred offsets)
    char m_bSomeFlag; // +0x48
    void* m_pCommandBuffer; // +0xB0
    int m_commandBufferCapacity; // +0xB4
    int m_commandReadIndex; // +0xB8
    int m_commandCount; // +0xBC
    int m_someLimit; // +0x1E0
    int m_someValue; // +0x1E8
    char m_bAnotherFlag; // +0x221
    int** m_pArrayOfPointers; // +0x338
    int m_arrayCount; // +0x33C
    char m_bFlagAt500; // +0x500
    bool m_bFlagAt6F1; // +0x6F1
    uint m_flags; // +0x6F4
};