// FUNC_NAME: StreamManager::loadStreamFromFile
// Function address: 0x0075AC30
// This function handles asynchronous loading of a stream (likely a file or network packet) and processes it.
// It uses a resource ID (0x18645CD9) for validation, waits for the async read to complete, then processes the data and sends it.

#include <cstdint>

// Forward declarations for helper functions (from EARS engine)
int __fastcall FUN_007FFDF0();                                      // getStreamAllocator()
int __fastcall FUN_009A4380(int arg1, int arg2, int arg3, int arg4, int arg5); // allocateStreamBuffer
void __fastcall FUN_005FCF80(void* dest, void* src, int size);       // memcpy or buffer init
int __fastcall FUN_009A3D70();                                      // getStackAllocator()
void __fastcall FUN_004DAF90(int* ptr);                              // freeMemory
int __fastcall FUN_005F7700(int* allocator, void* buffer, int size, int timeout, int flags, int unk1, int unk2); // asyncReadFile
char __fastcall FUN_005F6820(int param);                             // isAsyncOperationComplete
void __fastcall FUN_005F7920(int ms);                                // sleepMs
char __fastcall FUN_005F67F0();                                      // isProcessingReady
int __fastcall FUN_009C8E50(int size);                               // malloc
int __fastcall FUN_009A1A80();                                       // createDataHandle
void __fastcall FUN_00757350(int handle);                            // processReceivedData
char __fastcall FUN_005F7CE0(int fileHandle, int* buffer);           // completeRead
int __fastcall FUN_00471610();                                       // getNetworkContext
void __fastcall FUN_00601050(int* buffer, int unk1, uint64_t* timestamp, int unk2, int unk3); // sendDataPacket
void __fastcall FUN_005FEA00(int globalEvent, int param);            // dispatchEvent
void __fastcall FUN_005F7860(int fileHandle);                        // closeFile
void __fastcall FUN_009A4440();                                      // cleanupStackAllocator

class StreamManager {
public:
    // Offsets in class (relative to this):
    // +0x48: Pointer to containing object (base class)
    // +0x50: Some context (offset 0x5f0 within)
    // +0x5C: Buffer for temporary data
    // +0x6C: Resource ID or file descriptor
    // +0x70: Async file handle
    // +0x74: Currently allocated buffer (released before new load)
    // +0x8C: Result data

    void __fastcall loadStreamFromFile(int param_1) {
        char cVar1;
        char cVar2;
        int* piVar3;
        int* piVar4;
        int iVar5;
        int uVar6;
        int uStack_84; // likely the resource validation result
        int local_7c; // buffer for virtual call
        uint64_t uStack_78; // timestamp/network data
        int uStack_70;
        char auStack_6c[108]; // temporary buffer on stack

        // Resolve base class pointer (offset -0x48)
        if (*(int*)(param_1 + 0x48) == 0) {
            piVar3 = (int*)0;
        } else {
            piVar3 = (int*)(*(int*)(param_1 + 0x48) - 0x48);
        }

        local_7c = 0;
        // Virtual call on base class to validate resource ID (0x18645CD9)
        cVar1 = (**(char (__thiscall**)(int*, int*))(*(int*)piVar3 + 0x10))(0x18645cd9, &local_7c);

        piVar3 = (int*)FUN_007FFDF0(); // get stream allocator
        FUN_009A4380(*(int*)(param_1 + 0x6c), *(int*)(*(int*)(param_1 + 0x50) + 0x5f0), 0x40102, 0, 0); // allocate stream buffer

        FUN_005FCF80((void*)(param_1 + 0x5c), auStack_6c, (int)DAT_00d92d14); // init temporary buffer (global size)

        piVar4 = (int*)FUN_009A3D70(); // get stack allocator
        iVar7 = 0;
        // Build a linked list node on stack using allocator
        if ((((int*)&stack0xffffff6c != piVar4) && (iVar5 = *piVar4, iVar5 != 0)) &&
            (iVar7 = iVar5, iVar5 != 0)) {
            *(char**)(iVar5 + 4) = &stack0xffffff6c; // link node
        }

        // Check if allocators are valid
        if ((*piVar3 != 0) && (piVar3[2] != 0) && (iVar7 != 0 && (piVar4[2] != 0))) {
            int* pBuffer = (int*)(param_1 + 0x74);
            // Release previous buffer if exists
            if (*(int**)(param_1 + 0x74) != (int*)0) {
                (**(void (__thiscall**)(int))(**(int**)(param_1 + 0x74) + 0x0))(1); // virtual destructor call
                if (*pBuffer != 0) {
                    FUN_004DAF90(pBuffer);
                    *pBuffer = 0;
                }
            }

            // Start async read: file descriptor, temporary buffer, size 0x800, timeout -1, flags 0, unk 0x9000/0x8000
            iVar5 = FUN_005F7700(piVar3, &stack0xffffff6c, 0x800, -1, 0, 0x9000, 0x8000);
            *(int*)(param_1 + 0x70) = iVar5; // store async handle

            // Wait for async operation to complete
            while ((iVar5 != 0) && (cVar2 = FUN_005F6820(0), cVar2 == '\0')) {
                FUN_005F7920(100); // sleep 100ms
                iVar5 = *(int*)(param_1 + 0x70);
            }

            // If async done and operation ready
            if ((*(int*)(param_1 + 0x70) != 0) && (cVar2 = FUN_005F6820(0), cVar2 != '\0')) {
                cVar2 = FUN_005F67F0(); // check if processing ready
                if (cVar2 != '\0') {
                    iVar5 = FUN_009C8E50(0x18); // allocate 24 bytes for handle
                    if (iVar5 == 0) {
                        uVar6 = 0;
                    } else {
                        uVar6 = FUN_009A1A80(); // create data handle
                    }
                    FUN_00757350(uVar6); // process data with handle

                    // Complete the async read
                    cVar2 = FUN_005F7CE0(*(int*)(param_1 + 0x70), *pBuffer);
                    if ((cVar2 != '\0') && (*pBuffer != 0)) {
                        iVar5 = FUN_00471610(); // get global network context
                        uStack_78 = *(uint64_t*)(iVar5 + 0x30); // timestamp
                        uStack_70 = *(int*)(iVar5 + 0x38); // additional data
                        FUN_00601050(*pBuffer, 0, &uStack_78, 0, 0); // send packet
                        FUN_005FEA00((int)DAT_00d58cbc, 0); // dispatch event
                        // Store result: based on resource validation and local_7c
                        *(int*)(param_1 + 0x8c) = *(int*)((-(int)(cVar1 != 0) & uStack_84) + 0x120);
                    }
                }
                // Cleanup async handle
                if (*(int*)(param_1 + 0x70) != 0) {
                    FUN_005F7860(*(int*)(param_1 + 0x70)); // close async handle
                    *(int*)(param_1 + 0x70) = 0;
                }
                *(int*)(param_1 + 0x70) = 0;
            }
        }

        FUN_009A4440(); // cleanup stack allocator
        // Release linked list node if allocated
        if (iVar7 != 0) {
            FUN_004DAF90(&stack0xffffff6c);
        }
        return;
    }
};