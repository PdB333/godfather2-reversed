// FUNC_NAME: DonControlManager::createGadget
// Address: 0x00964bf0
// Role: Creates a don control gadget (0xF0 bytes) with a unique name derived from a hash and starts its state machine.

#include <cstdint>

// Forward declarations
struct GadgetObject; // size 0xF0, fields at +0x0c (state), +0x14 (callback)
void* operatorNew(uint32_t size);               // FUN_009c8e50
GadgetObject* constructGadget(void* mem);       // FUN_00982280
void setGadgetName(const char* name);           // FUN_00981eb0
void startGadget();                             // FUN_00982e10
void beginGadgetContext();                      // FUN_00604be0
void endGadgetContext();                        // FUN_00604c00
void setContextType(uint32_t type, int value);  // FUN_00604c10
void formatWithHash(uint32_t handle, char* buffer, const char** out, const char* fmt, uint32_t hash); // FUN_006038a0
void gadgetCallback();                          // FUN_00982b30

void DonControlManager::createGadget() {
    // State check: must be in state 4 with no blocking flag
    if (this->state != 4 || this->blockingFlag != 0) {
        return;
    }

    char localBuffer[4112];    // stack buffer for formatted string
    const char* namePtr = nullptr; // pointer to allocated name (if any)
    void (*freeFunc)(const char*) = nullptr; // cleanup function (may be set by format)

    // Enter allocation context
    beginGadgetContext();

    // Set context type 0x73 with value derived from a pointer chain: (this->dataPtr + 4) + 0x20
    setContextType(0x73, *(int*)(*(int*)(this->dataBlock + 4)) + 0x20);

    // Generate a unique name using fixed hash constant
    // Result: namePtr points to either an allocated string or null
    formatWithHash(someHandle, localBuffer, &namePtr, "{#%u}", 0x533964aa);

    const char* finalName = (namePtr != nullptr) ? namePtr : ""; // fallback empty string

    // Allocate gadget object (0xF0 bytes)
    GadgetObject* gadget = static_cast<GadgetObject*>(operatorNew(0xF0));
    if (gadget != nullptr) {
        gadget = constructGadget(gadget); // placement construct
    }

    if (gadget != nullptr) {
        setGadgetName(finalName);           // associate name with gadget
        gadget->state = 3;                  // +0x0c: initial state (active?)
        gadget->callback = gadgetCallback;  // +0x14: state machine callback
        startGadget();                      // register/activate gadget
    }

    // Exit allocation context
    endGadgetContext();

    // Free the temporary name string if one was allocated
    if (namePtr != nullptr && freeFunc != nullptr) {
        freeFunc(namePtr);
    }
}