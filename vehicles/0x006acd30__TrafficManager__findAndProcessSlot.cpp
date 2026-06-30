// FUNC_NAME: TrafficManager::findAndProcessSlot
#include <cstdint>

// Forward declaration for the callee at 0x00894c90
extern void __fastcall processVehicleSlotData(void* vehicleData);

class TrafficManager {
public:
    // +0x2C: Size 0x30 each, 20 slots = 0x3C0 bytes total? Actually slot array starts at offset 0x2C? Let's verify:
    // The loop accesses param_1 + 0x2C + i*0x30 for flags, param_1 + 0x34 + i*0x30 for type, param_1 + 0x38 + i*0x30 for data.
    // So base of slot i is offset param_1 + 0x2C + i*0x30.
    struct VehicleSlot {
        int flags;     // +0x00 (relative to slot base)
        int type;      // +0x08
        void* data;    // +0x0C
        // remaining 0x18 bytes ignored here
    };
    // Assume slots are stored contiguously starting at offset 0x2C from this pointer.
    // This is an array of 20 elements, each 0x30 bytes.
    // The exact offset is not directly declared but is known from code; we'll model it as an array.
};

// Reconstructed method
void __fastcall TrafficManager::findAndProcessSlot() {
    // Iterate over 20 vehicle slots (index 0..19)
    for (int i = 0; i < 20; i++) {
        // Calculate pointer to current slot's type field (we need flags and data as well)
        int* typePtr = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x34 + i * 0x30);
        int* flagsPtr = typePtr - 2;  // flags at typePtr - 2 ints = offset 0x2C + i*0x30
        // Check if bit 1 (value 2) is set in flags and type equals 3 (e.g., active car slot)
        if (((*flagsPtr >> 1) & 1) != 0 && *typePtr == 3) {
            // Found matching slot; retrieve data pointer stored at typePtr[1] (offset 0x38 + i*0x30)
            void* dataPtr = reinterpret_cast<void*>(typePtr[1]);
            // Call processing function on this slot's data
            processVehicleSlotData(dataPtr);
            return;
        }
    }
    // No matching slot found; function returns without action
}