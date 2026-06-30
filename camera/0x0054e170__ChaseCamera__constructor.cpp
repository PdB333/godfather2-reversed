// FUNC_NAME: ChaseCamera::constructor
// Address: 0x0054e170
// Role: Constructs a ChaseCamera object, allocating internal buffers and initializing fields from parameters.
// Uses a thread-local allocator (TlsGetValue) and custom memory pools.

#include <windows.h> // For TlsGetValue

// Forward declarations of called functions (assumed engine internals)
extern float g_baseSpeed;           // _DAT_01126040
extern int g_TlsIndex;              // DAT_01139810
extern void* g_globalData;          // DAT_00e2b1a4 (some constant pointer)
extern void* g_someSingleton;       // DAT_011397d0

// These are internal allocation/factory functions in the EARS engine
void* allocateMemory(int size, int tag);          // FUN_00aa2680
void initializePart1(void* buffer, int* data);    // FUN_00a66df0 (takes reference to stack data)
void initializePart2(void* buffer, void* data);   // FUN_00a6be50
void registerWithSystem(void* obj, void* singleton, int param5); // FUN_009f0c70
void sendMessage(int msgId, void* sender, int flags); // FUN_009f01f0
void onCameraCreated();                            // FUN_0045cbe0

// vtable for ChaseCamera (extern)
extern void* PTR_FUN_00e39ec0;

struct ChaseCamera
{
    void* vtable;           // +0x00
    // Size: 0x170 bytes total
    // Fields at known offsets
    int unk0x04;            // +0x04 (set to 0x30 in first allocation)
    char pad0x08[0x158];    // padding to reach offset 0x160
    void* parent;           // +0x160 (puVar3[0x58])
    int sourceObject;       // +0x164 (puVar3[0x59])
};

// The main factory function
ChaseCamera* FUN_0054e170(int param_1, unsigned int param_2, float param_3,
                           unsigned int param_4, unsigned int param_5)
{
    // Local data for initializations
    unsigned int stackData1;    // local_70 (overlaps param_2)
    float stackFloat;           // local_6c (overlaps param_3)
    unsigned int stackData2;    // local_68 (overlaps param_4)
    unsigned int globalConst;   // local_64 = g_globalData

    unsigned int initializer[5]; // local_50 array
    unsigned int otherData;      // local_3c
    unsigned int moreData;       // local_28
    unsigned int zeroData;       // local_20
    float speedValue;            // local_1c
    unsigned int zero2;          // local_18
    unsigned int zero3;          // local_14

    // Store incoming parameters into local variables for later use
    stackData1 = param_2;
    stackFloat = param_3;
    stackData2 = param_4;
    globalConst = (unsigned int)g_globalData;

    // Get thread-local storage (allocator context)
    TlsGetValue(g_TlsIndex);

    // Allocate first temporary buffer (size 0x30, tag 0x27)
    void* tempBuffer1 = allocateMemory(0x30, 0x27);
    *(unsigned short*)((char*)tempBuffer1 + 4) = 0x30; // store size

    // Initialize first buffer with data from the stack
    unsigned int result = initializePart1(&stackData1, (unsigned int)tempBuffer1);

    // Compute camera speed: read offset 0x84 from param_1 (parent object velocity?), multiply by param_3, add global base speed
    float parentSpeed = *(float*)((char*)param_1 + 0x84);
    float adjustedSpeed = parentSpeed * param_3 + g_baseSpeed;

    // Notify that camera is being created (maybe update timing)
    onCameraCreated();

    // Set up initializer array for second allocation
    initializer[0] = (unsigned int)g_globalData;
    otherData = (unsigned int)g_globalData;
    moreData = (unsigned int)g_globalData;
    zeroData = 0;
    speedValue = adjustedSpeed;
    zero2 = 0;
    zero3 = 0;

    // Get TLS again (potential reuse)
    TlsGetValue(g_TlsIndex);

    // Allocate second temporary buffer (size 0x70, tag 0x27)
    void* tempBuffer2 = allocateMemory(0x70, 0x27);
    *(unsigned short*)((char*)tempBuffer2 + 4) = 0x70; // store size

    // Initialize second buffer with the local array
    unsigned int result2 = initializePart2((unsigned int)tempBuffer2, initializer);

    // Get TLS one more time (likely for final allocation)
    TlsGetValue(g_TlsIndex);

    // Allocate the final ChaseCamera object (size 0x170, tag 0x31)
    ChaseCamera* cameraObj = (ChaseCamera*)allocateMemory(0x170, 0x31);
    *(unsigned short*)((char*)cameraObj + 4) = 0x170; // store size of this allocation

    // Register the camera with the engine's singleton (e.g., camera manager)
    registerWithSystem((void*)result2, g_someSingleton, param_5);

    // Set up vtable and fields
    cameraObj->vtable = &PTR_FUN_00e39ec0;
    cameraObj->parent = (void*)param_1;   // +0x160
    cameraObj->sourceObject = param_1;    // +0x164 (note: param_1 again, maybe a different meaning)

    // Send a message (0x2001) to signal creation, with the camera pointer
    sendMessage(0x2001, (void*)cameraObj, 0);

    return cameraObj;
}