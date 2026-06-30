// FUNC_NAME: VehicleBrain::checkAndProcess
#include <cstdint>

// Identified role: Check flag at offset +0x5c (bit 0) and call processing
// if the flag is clear. Usually used to avoid redundant update calls.
// Called function (0x0053f930) is likely VehicleBrain::processAction.

class VehicleBrain {
public:
    void __thiscall checkAndProcess();
private:
    void __thiscall processAction(); // internal processing function // +0x5c byte flags
};

void VehicleBrain::checkAndProcess() {
    // +0x5c: byte containing various flags; bit 0 indicates whether processing is already done or pending
    if ((*(uint8_t*)((uintptr_t)this + 0x5c) & 1) == 0) {
        // If bit 0 is clear, perform the action
        processAction();
    }
    // Otherwise, skip (already processed or not needed)
}