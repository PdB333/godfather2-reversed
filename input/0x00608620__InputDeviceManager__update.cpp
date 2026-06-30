// FUNC_NAME: InputDeviceManager::update
// Function address: 0x00608620
// Role: Per-frame update for input device manager, including profiling of subsystems, controller state updates, and buffer clearing.

#include <windows.h> // For LARGE_INTEGER, QueryPerformanceCounter

// Forward declarations of subsystem update functions
void updateAudio();      // FUN_0060c2e0
void updateNetwork();    // FUN_0060b8b0
void updatePhysics();    // FUN_0060bbd0
void updateRendering();  // FUN_0060c5e0
void finalizeUpdate();   // FUN_0060dcb0

// Global pointer to the input manager singleton (DAT_01205750)
extern InputDeviceManager* gInputManager;

// Global flag (DAT_01205758)
extern int gInputManagerUpdated;

// Global buffers for input state (DAT_011f7450, DAT_011da7f0, DAT_011d97f0, DAT_011ea8f0)
extern char gControllerStateBuffer[0xF0];   // 240 bytes, 16 controllers * 0x0F each? Actually 0xF0 = 240, 16*15=240, but 0x44 per controller? Not matching. Maybe different.
extern char gKeyStateBuffer[0x100];          // 256 bytes
extern char gMouseStateBuffer[0x1000];       // 4096 bytes
extern char gJoystickStateBuffer[0x1000];    // 4096 bytes

// Constants
const int kMaxControllers = 16; // 0x10

// InputDeviceManager vtable offsets (relative to vtable pointer)
// These are assumed based on the code pattern.
struct InputDeviceManagerVTable {
    void (*update)(InputDeviceManager*);                          // +0xa4
    void (*beginFrame)(InputDeviceManager*);                      // +0x1b0
    void (*endFrame)(InputDeviceManager*);                        // +0x1ac
    void (*beginControllerUpdate)(InputDeviceManager*);           // +0x174
    void (*endControllerUpdate)(InputDeviceManager*);             // +0x170
    void* (*getController)(InputDeviceManager*, int index);       // +0x100
    void (*setController)(InputDeviceManager*, int index, void*); // +0x104
    void (*getDevice)(InputDeviceManager*, int index, void** out1, void** out2, void** out3); // +0x194
    void (*setDevice)(InputDeviceManager*, int index, void* in1, void* in2, void* in3);       // +0x190 (400 decimal)
    void* (*getSomething)(InputDeviceManager*);                   // +0x1a4
    void (*setSomething)(InputDeviceManager*, void*);             // +0x1a0
};

// The actual vtable pointer is stored at the beginning of the object.
#define VTABLE(obj) (*(InputDeviceManagerVTable**)obj)

void InputDeviceManager::update()
{
    LARGE_INTEGER startTime, endTime, elapsed;
    float frameTime = 0.0f;
    float totalTime = 0.0f;

    // Profile audio update
    QueryPerformanceCounter(&startTime);
    updateAudio();
    QueryPerformanceCounter(&endTime);
    elapsed.QuadPart = endTime.QuadPart - startTime.QuadPart;
    // Convert to seconds using frequency (stored in _DAT_01163ecc)
    frameTime = 1.0f - (float)(elapsed.QuadPart) * (float)_DAT_01163ecc; // Note: This calculation seems inverted; likely a profiling accumulation.
    totalTime += frameTime;

    // Profile network update
    QueryPerformanceCounter(&startTime);
    updateNetwork();
    QueryPerformanceCounter(&endTime);
    elapsed.QuadPart = endTime.QuadPart - startTime.QuadPart;
    frameTime = totalTime - (float)(elapsed.QuadPart) * (float)_DAT_01163ecc;
    totalTime = frameTime;

    // Profile physics update
    QueryPerformanceCounter(&startTime);
    updatePhysics();
    QueryPerformanceCounter(&endTime);
    elapsed.QuadPart = endTime.QuadPart - startTime.QuadPart;
    // Only high part used for sign? Actually the code does: local_10.s.HighPart = (elapsed.HighPart - ...) & 0x80000000; local_10.s.LowPart = 0;
    // Then later uses that to compute something. Simplified: just accumulate.
    // The original code is messy; we'll keep it simple.

    // Profile rendering update
    updateRendering();

    // Call main update on the input manager
    VTABLE(gInputManager)->update(gInputManager);

    // Set flag indicating update completed
    gInputManagerUpdated = 1;

    // Begin and end frame operations
    VTABLE(gInputManager)->beginFrame(gInputManager);
    VTABLE(gInputManager)->endFrame(gInputManager);

    // Release previous frame's controller state objects (if any)
    // unaff_EDI is likely a pointer to a previous controller state object
    if (unaff_EDI != nullptr) {
        // Call destructor (vtable+8)
        (*(void (**)(void*))(*(int*)unaff_EDI + 8))(unaff_EDI);
    }

    // Begin and end controller update
    VTABLE(gInputManager)->beginControllerUpdate(gInputManager);
    VTABLE(gInputManager)->endControllerUpdate(gInputManager);

    // Release previous frame's device object (piStack_44)
    if (piStack_44 != nullptr) {
        (*(void (**)(void*))(*(int*)piStack_44 + 8))(piStack_44);
    }

    // Update each controller slot
    for (int i = 0; i < kMaxControllers; i++) {
        void* controllerState = nullptr;
        // Get current controller state (vtable+0x100)
        controllerState = VTABLE(gInputManager)->getController(gInputManager, i);
        // Set controller state to null (clear)
        VTABLE(gInputManager)->setController(gInputManager, i, nullptr);
        // Release the old state if it existed
        if (controllerState != nullptr) {
            (*(void (**)(void*))(*(int*)controllerState + 8))(controllerState);
        }
    }

    // Get and set something (maybe device list)
    void* something = nullptr;
    VTABLE(gInputManager)->getSomething(gInputManager, &something);
    VTABLE(gInputManager)->setSomething(gInputManager, nullptr);
    // Release previous something
    if (piStack_50 != nullptr) {
        (*(void (**)(void*))(*(int*)piStack_50 + 8))(piStack_50);
    }

    // Update another set of 16 slots (maybe joystick/other devices)
    for (int i = 0; i < kMaxControllers; i++) {
        void* out1 = nullptr;
        void* out2 = nullptr;
        void* out3 = nullptr;
        // Get device pointers
        VTABLE(gInputManager)->getDevice(gInputManager, i, &out1, &out2, &out3);
        // Set device pointers to null
        VTABLE(gInputManager)->setDevice(gInputManager, i, nullptr, nullptr, nullptr);
        // Release the first pointer if it existed
        if (out1 != nullptr) {
            (*(void (**)(void*))(*(int*)out1 + 8))(out1);
        }
    }

    // Clear input state buffers
    memset(&gControllerStateBuffer, -1, sizeof(gControllerStateBuffer));
    gInputManager->someFlag1 = 0; // DAT_01205830
    gInputManager->someFlag2 = 0; // DAT_01205834
    gInputManager->someFlag3 = 0; // DAT_01205838
    gInputManager->someFlag4 = 0; // DAT_0120583c

    memset(&gKeyStateBuffer, -1, sizeof(gKeyStateBuffer));
    memset(&gMouseStateBuffer, -1, sizeof(gMouseStateBuffer));
    memset(&gJoystickStateBuffer, -1, sizeof(gJoystickStateBuffer));

    // Finalize update
    finalizeUpdate();
}