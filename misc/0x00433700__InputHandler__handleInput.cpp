// FUNC_NAME: InputHandler::handleInput
#include <cstdint>

// Global data declarations (based on analysis)
extern uint32_t g_deviceMap[];                    // DAT_0112864c - array of 32-bit ints
extern int32_t g_tlsCheckedValue;                 // DAT_00f15a4c (used as array index from TLS)
extern int32_t DAT_0110abf0[];                    // remap table for device index
extern int32_t DAT_0110abf4;                      // constant value
extern uint32_t DAT_0110ab30;                     // type constant
extern uint32_t g_inputProcessingGuard;           // DAT_0120546c
extern uint32_t g_inputStatePtr;                  // DAT_012233a8 - pointer to something (offset 4 used)
extern void* g_postProcessCallback;               // DAT_012058e8 (vtable pointer)

// Forward declaration of the internal dispatch function
uint32_t processInputDispatch(int32_t inputState, InputHandler* handler, uint32_t unkParam2,
                              uint32_t trimmedValue, int32_t remappedDevice,
                              uint32_t unkParam5, uint32_t unkParam6);

// Structure for the 'this' object (InputHandler)
// Offsets deduced from decompiled code:
// +0x30: uint32_t typeID (compared to DAT_0110ab30)
// +0x34: uint32_t maxInputCount
// +0x98: InputHandler* child
struct InputHandler {
    uint8_t pad0[0x30];
    uint32_t typeID;                // +0x30
    uint32_t maxInputCount;         // +0x34
    uint8_t pad1[0x98 - 0x38];
    InputHandler* child;            // +0x98
};

uint32_t InputHandler::handleInput(uint32_t unkParam2, uint32_t deviceIndex,
                                   uint32_t inputValue, uint32_t unkParam5,
                                   uint32_t unkParam6)
{
    // ---- Step 1: Map the device index through global table ----
    int32_t remappedDevice = g_deviceMap[deviceIndex];   // iVar4

    bool isDeviceOne = (deviceIndex == 1);                // bVar5

    // Thread-local check: use TLS array pointer (FS:[0x2C]) and offset 0x34
    // This likely tests whether the current thread is the main thread.
    int32_t* tlsArray = (int32_t*)__readfsdword(0x2C);   // FS segment
    int32_t tlsValue = *(int32_t*)(tlsArray[0] + 0x34);
    bool isMainThread = (tlsValue != 0);                 // iVar1 = (tlsValue == 0)? Actually iVar1 set from array index (0 or 1) based on zero check
    // The original: iVar1 = (&DAT_00f15a4c)[*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x34) == 0];
    // This indexes an array with 0 or 1 depending on equality. We'll approximate:
    uint32_t mainThreadFlag = (tlsValue == 0) ? 0 : 1;   // 0 if main? Actually the check is ==0 -> index? Let's compute:
    // The expression: (tlsValue == 0) yields 0 or 1, used as index into DAT_00f15a4c.
    // So iVar1 = DAT_00f15a4c[ (tlsValue == 0) ? 0 : 1 ].
    // But we only use iVar1 as boolean (check against zero). We'll call it isSpecialFlag.
    int32_t iVar1 = DAT_00f15a4c[ (tlsValue == 0) ? 0 : 1 ];

    // If the special flag is zero OR device is 1, remap again using a different table
    if ((iVar1 == 0) || (isDeviceOne)) {
        remappedDevice = DAT_0110abf0[remappedDevice];   // second remap
    }

    // ---- Step 2: Clamp inputValue to maxInputCount ----
    uint32_t maxCount = this->maxInputCount;              // uVar3 initially
    uint32_t trimmedValue = 0;                            // param_3 reused
    if (inputValue < maxCount) {
        trimmedValue = inputValue;
        maxCount = inputValue + 1;                        // uVar3 updated but not used later
    }

    // ---- Step 3: Obtain the global input state object ----
    int32_t* inputState = *(int32_t**)(g_inputStatePtr + 4); // iVar2 = pointer at +4

    // ---- Step 4: Adjust remappedDevice based on input state flags ----
    // inputState has two byte flags at +0x84 and +0x85
    if (*(char*)(inputState + 0x84) == '\0') {
        // flag1 is false
        if ( (*(char*)(inputState + 0x85) != '\0') && (iVar1 != 0) && (!isDeviceOne) ) {
            remappedDevice = 0;
        }
    } else {
        // flag1 is true
        remappedDevice = DAT_0110abf4;
        if ((iVar1 != 0) && (!isDeviceOne)) {
            remappedDevice = 1;
        }
    }

    // ---- Step 5: Check if we should actually forward the event ----
    // Condition: child is null OR this->typeID equals constant OR child->typeID not equals constant
    // This prevents forwarding if child exists and types mismatch.
    bool shouldForward = (this->child == nullptr)
                         || (this->typeID == DAT_0110ab30)
                         || (this->child->typeID != DAT_0110ab30);

    // Set the processing guard
    g_inputProcessingGuard = 1;

    uint32_t result = 0;
    if (shouldForward) {
        result = processInputDispatch(inputState, this, unkParam2, trimmedValue,
                                      remappedDevice, unkParam5, unkParam6);
    }

    // Clear the guard
    g_inputProcessingGuard = 0;

    // Post-processing callback (virtual call)
    if (g_postProcessCallback != nullptr) {
        result = (*(uint32_t (**)(void))(*(uint32_t*)g_postProcessCallback + 0x20))();
    }

    return result;
}