// FUNC_NAME: InputManager::updateControllerSlots
// Function at 0x004b66a0 - processes all controller/device slots, checks state, and flushes pending object
// unknown calling convention: __thiscall assumed (ECX = this)

#include <cstdint>

// Forward declarations of used functions (not provided, but named for clarity)
void someInitializeBuffer(uint8_t* buffer, uint32_t size); // FUN_004af8c0
void flushPendingObject(void* pending); // FUN_009f1b20
void updateEngine(); // FUN_009f01a0
void releaseHandle(uint32_t handle); // FUN_00540700
void someFinalizeFunction(void* param); // FUN_004086d0

// Structure for a controller/device slot (size 0x70)
struct DeviceSlot {
    uint8_t pad0[0x40]; // +0x00 to +0x3F
    uint32_t handle;    // +0x40
    uint8_t pad44[0x2C]; // +0x44 to +0x6F
};

// Main class
class InputManager {
public:
    // +0x08 - pointer to engine singleton or manager (used to get vtable)
    void* engineManager; 

    // +0x18 - pointer to array of DeviceSlot[count]
    DeviceSlot* slots; 

    // +0x1C - number of slots
    uint32_t slotCount; 

    // +0x24 - pending object pointer (cleared after processing)
    void* pendingObject; 

    // +0x28 - flags byte (bit0 = active, bit3 = finalize needed)
    uint8_t flags; 

    void updateControllerSlots() {
        if ((flags & 1) == 0) {
            return; // Not active
        }

        if (slotCount != 0) {
            for (uint32_t i = 0; i < slotCount; i++) {
                DeviceSlot& slot = slots[i];
                uint32_t handle = slot.handle;

                uint8_t buffer[12];
                someInitializeBuffer(buffer, 0x800); // 0x800 likely size/param

                // Check if buffer indicates busy/occupied
                if ((buffer[0] & 1) == 0) {
                    // Get engine object via chain: this->engineManager->vtable[0x20]()
                    void* engineObj = *(void**)(*(uintptr_t*)(*(uintptr_t*)(this->engineManager) + 8) + 0x20);
                    // Call method at vtable+0x40 on that object with handle
                    (*(void(**)(uint32_t))(*(uintptr_t*)engineObj + 0x40))(handle);

                    if (this->pendingObject != nullptr) {
                        flushPendingObject(this->pendingObject);
                        updateEngine();
                        this->pendingObject = nullptr;
                    }

                    releaseHandle(handle);
                }
            }
        }

        // Check bit 3 flag
        if (flags & 8) {
            someFinalizeFunction(&DAT_012069c4); // global or parameter
            flags &= ~8;
        }

        // Clear active flag
        flags &= ~1;
    }
};