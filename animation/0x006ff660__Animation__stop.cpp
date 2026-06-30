// FUNC_NAME: Animation::stop
// Function at 0x006ff660: Stops the animation if playing, resets state.
// Assumes this points to Animation structure with fields:
// +0x00: field_0 (first int, cleared on stop)
// +0x04: field_4
// +0x08: field_8
// +0x0C: field_C
// +0x1C: pendingHandle (offset 28, param_1[7]) - handle to release
// +0x20: state (offset 32, param_1[8]) - 0=stopped, 1=playing, 2/3=paused/buffering
// Returns 1 on success.

int __thiscall Animation::stop(void) {
    if (this->state != 1) {
        // If state is not "playing", check if it's greater than 3 (invalid range)
        if (this->state > 3) {
            return 1;
        }
        // If state is 2 or 3 (paused/buffering) and there is a pending handle
        if (this->pendingHandle != 0) {
            // Release current resource/stream
            Animation::releaseResource(); // FUN_005e3260
            // Retrieve default resource (output discarded)
            int defaultResource; // local_10
            Animation::getDefaultResource(&defaultResource); // FUN_006fdaf0
        }
    }
    // Reset to idle state
    this->state = 0;
    this->pendingHandle = 0;
    // Clear first four ints (position/rotation or similar)
    this->field_0 = 0;
    this->field_4 = 0;
    this->field_8 = 0;
    this->field_C = 0;
    return 1;
}