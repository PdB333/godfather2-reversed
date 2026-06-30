// FUNC_NAME: InputDeviceManager::processInputEvent

// Address: 0x006912c0
// Processes an input event from a given device and controller slot.
// When the input mode is not 0x12 (likely a specific game state),
// it dispatches the event to an input handler via its virtual function table.
// If the controller slot is valid (< 15), additional preparatory calls are made.

#include <cstdint>

// Forward declarations based on known EA EARS patterns
class InputHandler; // virtual class with vtable offset 8 = handleEvent

// Global singleton pointer to the input device manager (e.g., InputDeviceManager)  
// This is stored at DAT_012233b4 in the binary.
extern InputDeviceManager* gInputDeviceManager;

// Static map: device index (0..?) to event ID.  
// Located at DAT_01129bd4, accessed as 4-byte values at offset (deviceIndex * 2).
// This likely stores an event code associated with each device.
extern const uint8_t s_deviceEventMap[]; // base address

// Helper functions; addresses from the binary:
// FUN_00411070: Returns a pointer to an InputHandler based on current input mode.
// FUN_004958a0: Prepares the handler (maybe resets state or allocates resources).

InputHandler* getHandlerForMode(uint8_t inputMode);
void prepareHandler(InputHandler* handler);

class InputDeviceManager {
public:
    // Offset 0x564 from the InputDeviceManager base: current input mode (byte)
    // 0x12 might represent a specific mode (e.g., "keyboard only" or "disabled").
    uint8_t m_inputMode;

    // The main processing function for an input event.
    void processInputEvent(int deviceIndex, int slotIndex) {
        if (m_inputMode == 0x12) {
            // Input mode is disabled or in a special state; ignore the event.
            return;
        }

        // If the slot is valid (0..14) and the mode hasn't changed, prepare the handler.
        if (slotIndex < 15 && m_inputMode != 0x12) {
            InputHandler* handler = getHandlerForMode(m_inputMode);
            prepareHandler(handler);
        }

        // Retrieve the event code from the device event map.
        // The map is indexed by deviceIndex*2 (each entry is 4 bytes).
        int eventCode = *(int*)(s_deviceEventMap + (deviceIndex * 2));

        // Get the input handler for the current mode (again) and dispatch the event.
        InputHandler* handler = getHandlerForMode(m_inputMode);
        handler->handleEvent(eventCode); // virtual call at vtable offset 8
    }
};

// Implementation of the global function (C linkage assumed).
// This matches the binary's exported symbol.
void __cdecl FUN_006912c0(int deviceIndex, int slotIndex) {
    gInputDeviceManager->processInputEvent(deviceIndex, slotIndex);
}