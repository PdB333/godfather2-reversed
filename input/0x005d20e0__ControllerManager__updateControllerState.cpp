// FUNC_NAME: ControllerManager::updateControllerState

#include <cstdint>

// Global input/controller state variables (from .data section)
extern uint32_t g_prevControllerState;      // 0x01127214
extern uint32_t g_activeControllerIndex;    // 0x01127310
extern uint32_t g_controllerAxis1[4];       // 0x011272e0
extern uint32_t g_controllerAxis2[4];       // 0x011272f0
extern uint32_t g_controllerHandle;         // 0x01127210
extern uint32_t g_axisHandle1;             // 0x011272a8
extern uint32_t g_axisHandle2;             // 0x011272ac
extern uint32_t g_axisHandle3;             // 0x01127384
extern uint32_t g_axisHandle4;             // 0x01127380
extern void* g_pEngineObject;              // 0x01205750 (pointer with vtable)
extern uint32_t g_controllerConnected;     // 0x011da7f0
extern uint32_t g_controllerRumble;        // 0x011da7f4
extern void* g_ptrCheck;                   // 0x012058e8 (compared to &PTR_PTR_01127200)
extern void* g_ptrCompare;                 // PTR_PTR_01127200

// Forward declarations of engine helper functions
extern void setActiveController(uint32_t state);
extern void beginFrame();
extern void updateAxis(uint32_t handle, uint32_t axisHandle, uint32_t* axisData);
extern void submitForceFeedback(uint32_t feedback);
extern void endFrame();
extern void pollInput(uint32_t device, uint32_t* buffer, uint32_t size,
                       uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7);
extern void processInput();
extern uint32_t getTimestamp();

// Virtual method call helpers
typedef void (__thiscall* VFunc3)(void*, uint32_t, uint32_t, uint32_t);
typedef void (__thiscall* VFunc2)(void*, uint32_t, uint32_t);
typedef void (__thiscall* VFunc5)(void*, uint32_t, uint32_t, uint32_t, uint32_t);

void __thiscall ControllerManager::updateControllerState(
    uint32_t controllerIndex,      // in_EAX (0,1,2)
    uint32_t* pRawBuffer,          // param_2 (buffer for pollInput, size 8)
    uint32_t unused,               // param_3 (not used)
    uint32_t forceFeedback,        // param_4 (rumble/force feedback data)
    uint32_t* pExtraAxis1,         // param_5
    uint32_t* pExtraAxis2)         // param_6
{
    uint32_t prevState = g_prevControllerState;
    uint32_t newState;

    // Determine new controller state based on index
    if (controllerIndex == 0) {
        newState = /* DAT_01127304 */ 0;  // placeholder constant
    } else if (controllerIndex == 1) {
        newState = /* DAT_01127308 */ 0;
    } else if (controllerIndex == 2) {
        newState = /* DAT_0112730c */ 0;
    }

    g_prevControllerState = newState;
    g_activeControllerIndex = controllerIndex;

    // If the engine pointer condition holds and state changed, update active controller
    if ((g_ptrCheck == &g_ptrCompare) && (prevState != g_prevControllerState)) {
        setActiveController(g_prevControllerState);
    }

    beginFrame();

    // Copy first 4 axis values from this object (e.g., left stick + right trigger)
    g_controllerAxis1[0] = this->axisData0; // +0x00
    g_controllerAxis1[1] = this->axisData1; // +0x04
    g_controllerAxis1[2] = this->axisData2; // +0x08
    g_controllerAxis1[3] = this->axisData3; // +0x0C
    updateAxis(g_controllerHandle, g_axisHandle1, g_controllerAxis1);

    // Copy next 4 axis values (e.g., right stick + left trigger)
    g_controllerAxis2[0] = this->axisData4; // +0x10
    g_controllerAxis2[1] = this->axisData5; // +0x14
    g_controllerAxis2[2] = this->axisData6; // +0x18
    g_controllerAxis2[3] = this->axisData7; // +0x1C
    updateAxis(g_controllerHandle, g_axisHandle2, g_controllerAxis2);

    // Update with extra axis data passed as parameters
    updateAxis(g_controllerHandle, g_axisHandle3, pExtraAxis1);
    updateAxis(g_controllerHandle, g_axisHandle4, pExtraAxis2);

    submitForceFeedback(forceFeedback);
    endFrame();

    // Poll raw input data into the buffer provided
    pollInput(0, pRawBuffer, 8, 0, 0, 0, 1);
    processInput();

    uint32_t timestamp = getTimestamp();

    // Call vtable method at offset 0x144 (engine object notification)
    VFunc3 vfunc144 = (VFunc3)(*(uint32_t*)(*(uint32_t*)g_pEngineObject + 0x144));
    vfunc144(g_pEngineObject, 5, 0, timestamp);

    // Set controller connected flag if not already
    if (g_controllerConnected != 1) {
        VFunc2 vfunc198 = (VFunc2)(*(uint32_t*)(*(uint32_t*)g_pEngineObject + 0x198));
        vfunc198(g_pEngineObject, 0, 1);
        g_controllerConnected = 1;
    }

    // Stop rumble if still active
    if (g_controllerRumble != 0) {
        VFunc5 vfunc400 = (VFunc5)(*(uint32_t*)(*(uint32_t*)g_pEngineObject + 400)); // 0x190
        vfunc400(g_pEngineObject, 0, 0, 0, 0);
        g_controllerRumble = 0;
    }
}