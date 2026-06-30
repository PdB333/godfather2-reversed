// FUNC_NAME: InputManager::disconnectControllerSlot
// Function at 0x00415970 - Deactivates and clears a controller slot's state, notifies disconnection

// External function called during disconnect notification
extern void __cdecl notifyControllerDisconnect(void);

// Controller slot structure (size likely 0x44 bytes)
struct ControllerSlot {
    void* listener;      // +0x08 - Pointer to a listener object or callback
    uint32 flags;        // +0x0C - State flags (bits: 0x1=active, 0x20000=disconnecting, 0x40000=connected)
    // ... other fields follow
};

// InputManager class (this pointer in ECX)
class InputManager {
public:
    // +0x80 - Pointer to the current active controller slot
    ControllerSlot* m_currentSlot;

    // Disconnects and resets the current controller slot
    void __thiscall disconnectControllerSlot(void) {
        ControllerSlot* slot = this->m_currentSlot;
        if (slot != nullptr) {
            // Clear the active (bit 0) and connected (bit 31) flags
            slot->flags &= 0x7FFFFFFE;

            // If not already flagged as disconnecting, set the flag and notify
            if ((slot->flags & 0x20000) == 0) {
                slot->flags |= 0x20000;            // Mark disconnecting
                notifyControllerDisconnect();      // Notify game systems
            }

            // Clear the connected flag (bit 0x40000)
            slot->flags &= 0xFFFBFFFF;

            // If a listener callback is registered, zero it out and clear the pointer
            if (slot->listener != nullptr) {
                *(uint32*)(slot->listener) = 0;    // Nullify the first field of the listener target
                slot->listener = nullptr;          // Clear reference to listener
            }
        }
    }
};