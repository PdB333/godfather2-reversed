// FUNC_NAME: NetConnection::buildStreamPacket

#include <windows.h>

extern float DAT_00e2cd54; // some constant
extern float _DAT_01126040; // another constant
extern float DAT_00e44564; // maybe gravity or baseline
extern DWORD DAT_01139810; // TLS index
extern void* DAT_011397d0; // static buffer
extern void* PTR_FUN_00e39ec0; // vtable pointer for returned object

// Allocation functions (likely from memory pool)
void* memPoolAlloc(int size, int type); // FUN_00aa2680

// Math function: takes two vectors and a scale, returns some handle
void* someMathFunction(void* vec, void* vec2, float scale); // FUN_00a65bb0

// Serialization function
void serializePacket(void* src, void* dst, undefined4 param); // FUN_009f0c70

// Other helper functions
void someInit(); // FUN_0043b490
void sendEvent(int eventType, undefined4 id, int flag); // FUN_009f01f0

undefined4* __thiscall NetConnection::buildStreamPacket(int thisPtr, undefined4 param_2, float param_3, float param_4, undefined4 param_5)
{
    float local_18, local_1c, local_2c, local_28;
    undefined4 local_30, local_24, local_20, local_14;
    void* tmpAlloc;
    undefined4 uVar2;
    undefined4* result;

    // Compute intermediate values using thisPtr's scale factors at offsets 0x84 and 0x80
    local_18 = (param_3 * DAT_00e2cd54 - param_4) * (*(float*)(thisPtr + 0x84));
    local_2c = (*(float*)(thisPtr + 0x84)) * param_4 + _DAT_01126040;
    local_28 = DAT_00e44564 - local_18;

    // Zero out local variables for vector construction
    local_30 = 0;
    local_24 = 0;
    local_20 = 0;
    local_14 = 0;
    local_1c = local_2c;

    // Retrieve thread-local storage (likely for current connection)
    TlsGetValue(DAT_01139810);

    // Allocate a temporary buffer (size 0x40, type 0x27)
    tmpAlloc = memPoolAlloc(0x40, 0x27);
    *(short*)((char*)tmpAlloc + 4) = 0x40; // set size field

    // Call math function with the constructed vectors and scale factor
    uVar2 = someMathFunction(&local_20, &local_30, *(float*)(thisPtr + 0x80) * param_4);

    // Another TLS call (possibly redundant)
    TlsGetValue(DAT_01139810);

    // Allocate main packet object (size 0x170, type 0x31)
    result = (undefined4*)memPoolAlloc(0x170, 0x31);
    *(short*)(result + 1) = 0x170; // set size field at byte offset 4

    // Serialize the packet data using uVar2, static buffer, and param_5
    serializePacket(uVar2, &DAT_011397d0, param_5);

    // Set vtable pointer
    *result = (undefined4)&PTR_FUN_00e39ec0;

    // Store parameters in the object at offsets 0x58 and 0x59 (in units of 4 bytes)
    result[0x58] = param_2; // byte offset 0x160
    result[0x59] = thisPtr; // byte offset 0x164

    // Perform additional initialization
    someInit();

    // Send a network event with type 0x2001
    sendEvent(0x2001, param_2, 0);

    return result;
}