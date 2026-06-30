// FUNC_NAME: StreamReader::readData
// Address: 0x005f38d0
// Reads data from a stream buffer, handles allocation and state transitions.
// The object (this) has fields:
// +0x14 ptr to a stream descriptor (or NULL)
// +0xa0 some state (negative means error?)
// +0xa4 state enum (2 = ready)
// +0xf8 source stream handle?
// +0xfc byte counter
// +0x104 total size
// +0x11c destination buffer
// +0x128 destination size
// +0x300 internal flag

#include <cstdint>

// Forward declarations of external functions
int32_t __cdecl lockStream(uint32_t* mutex); // FUN_00ab4db0
int32_t __cdecl unlockStream(uint32_t* mutex); // FUN_00ab4e70
int64_t __cdecl getCurrentSampleFrame(); // FUN_00ac28e0
void* __cdecl allocateBuffer(uint32_t size, uint32_t* alignmentInfo); // via vtable+0x0? actually from global+0x55c
void __cdecl copyStreamData(void* dest, void* src, uint32_t size, int32_t, uint32_t, int32_t, void*, int32_t, int32_t); // FUN_00ac4290
void __cdecl scheduleAsyncRead(void* streamHandle, void* callback, int32_t param, int32_t); // FUN_00ac3b80

extern uint32_t g_streamMutex; // DAT_00e2aea0
extern uint32_t* g_streamSystem; // DAT_01223510

void StreamReader::readData() {
    int32_t streamDesc = *(int32_t*)(this + 0x14);
    if (streamDesc == 0) {
        return;
    }

    lockStream(&g_streamMutex);

    int32_t state = *(int32_t*)(streamDesc + 0xa0);
    if (state < 0) {
        goto exit;
    }

    int32_t internalState = *(int32_t*)(streamDesc + 0xa4);
    if (internalState == 2) {
        // Already in ready state, schedule next read
        int32_t streamHandle = *(int32_t*)(streamDesc + 0xf8);
        if (streamHandle == 0) {
            goto exit;
        }
        void* callback = (void*)0x005f3c50; // LAB_005f3c50
        scheduleAsyncRead(streamHandle, callback, this, 0);
    } else {
        int64_t sampleFrame = getCurrentSampleFrame();
        uint32_t* sys = g_streamSystem;
        if (sampleFrame == 0x20) { // 32 sample frames elapsed
            uint8_t byteCounter = *(uint8_t*)(streamDesc + 0xfc);
            if (byteCounter < 4) {
                uint32_t totalSize = *(uint32_t*)(streamDesc + 0x104);
                uint32_t remaining = totalSize - 0x20;
                if (remaining != 0) {
                    if (*(int32_t*)(streamDesc + 0x300) == 0) {
                        uint32_t currentSize = *(uint32_t*)(streamDesc + 0x128);
                        if (currentSize < remaining) {
                            // Need to allocate larger buffer
                            void* oldBuffer = *(void**)(streamDesc + 0x11c);
                            if (oldBuffer != 0) {
                                // Free old buffer? Actually calls something in vtable+4
                                // (**(code **)(**(int **)(sys + 0x55c) + 4))(oldBuffer, currentSize);
                                // Omitted for clarity - assume proper deallocation
                            }
                            uint32_t alignmentInfo[3] = {2, 0x10, 0}; // local_14, local_10, local_c
                            // Allocate via system allocator
                            void* newBuffer = (void*)((*(int32_t**)(sys + 0x55c))[0])(remaining, &alignmentInfo);
                            *(void**)(streamDesc + 0x11c) = newBuffer;
                            *(uint32_t*)(streamDesc + 0x128) = remaining;
                            *(int32_t*)(streamDesc + 0x300) = 0;
                        }
                    }
                    copyStreamData(
                        *(void**)(streamDesc + 0xf8), // source handle?
                        *(void**)(streamDesc + 0x11c), // destination
                        0x20, // block size
                        0,    // some flag
                        *(int32_t*)(streamDesc + 0x104) - 0x20, // remaining bytes
                        0,    // another flag
                        (void*)0x005f3af0, // callback LAB_005f3af0
                        this,
                        0
                    );
                    unlockStream(&g_streamMutex);
                    return;
                }
                // No remaining bytes - transition to ready state
                int32_t streamHandle = *(int32_t*)(streamDesc + 0xf8);
                void* callback = (void*)0x005f3cb0; // LAB_005f3cb0
                *(int32_t*)(streamDesc + 0xa4) = 2;
                scheduleAsyncRead(streamHandle, callback, this, 0);
                goto exit;
            }
            // byteCounter >= 4 falls through to same state transition
            int32_t streamHandle = *(int32_t*)(streamDesc + 0xf8);
            *(int32_t*)(streamDesc + 0xa4) = 2;
            void* callback = (void*)0x005f3c50;
            scheduleAsyncRead(streamHandle, callback, this, 0);
        } else {
            // sampleFrame != 0x20
            int32_t streamHandle = *(int32_t*)(streamDesc + 0xf8);
            *(int32_t*)(streamDesc + 0xa4) = 2;
            void* callback = (void*)0x005f3c50;
            scheduleAsyncRead(streamHandle, callback, this, 0);
        }
    }

exit:
    unlockStream(&g_streamMutex);
    return;
}