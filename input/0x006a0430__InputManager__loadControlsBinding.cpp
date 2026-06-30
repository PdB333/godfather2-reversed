// FUNC_NAME: InputManager::loadControlsBinding
// Function address: 0x006a0430
// Role: Load and process input remapping from "controls_rmp" resource. If loading fails, use default data (DAT_00e2df14). Then call processing function and clean up.

#include <cstdint>

// Forward declarations of helper functions (from other modules)
extern void *__cdecl LoadResource(const char *key, int flag, void **outPtr);
extern void __cdecl ProcessControls(void *data);
// The destructor/callback stored in the loaded object (offset 0 as function pointer)
typedef void (__cdecl *DestructorFunc)(void *data);

void InputManager::loadControlsBinding(void) {
    void *loadedData; // local_10[0] originally, but only first element used
    void *dataPtr;    // puVar1
    DestructorFunc destructor; // local_4 (likely filled by LoadResource)

    // Load resource with key "controls_rmp" and flag 1
    LoadResource("controls_rmp", 1, &loadedData);

    // Use loaded data if available, otherwise use default global data
    if (loadedData != nullptr) {
        dataPtr = loadedData;
    } else {
        dataPtr = reinterpret_cast<void*>(0x00e2df14); // DAT_00e2df14 (default controls)
    }

    // Process the controls configuration
    ProcessControls(dataPtr);

    // Free loaded data if it was allocated (destructor stored at the beginning of the object)
    if (loadedData != nullptr) {
        destructor = reinterpret_cast<DestructorFunc*>(loadedData)[0]; // (*local_4) is actually the first field
        destructor(loadedData);
    }
}