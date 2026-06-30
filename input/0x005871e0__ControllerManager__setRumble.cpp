// FUNC_NAME: ControllerManager::setRumble
// Function address: 0x005871e0
// Handles setting rumble/vibration on controller motors based on flags.
// Flags bits 12-14 select which motor channel to update (left, right, center?).
// Returns 1 if handled, 0 if no appropriate flags were set.

int ControllerManager::setRumble(uint flags) {
    int motorLeft;    // local_18
    int motorRight;   // local_14
    int motorCenter;  // local_10
    int outLeft;      // local_c
    int outRight;     // local_8
    int outCenter;    // local_4

    // Check if any of the rumble motor flags are set (bits 12,13,14)
    if ((flags & 0x7000) != 0) {
        // Initialize output to zero
        outLeft = 0;
        outRight = 0;
        outCenter = 0;

        // Read current motor states from the controller object
        // Note: param_1 (this) is a ControllerManager instance
        readMotorStates(this, &motorRight, &motorLeft, &motorCenter);

        // Copy the value for the requested motor(s)
        if ((flags >> 12) & 1) {
            outLeft = motorLeft;
        }
        if ((flags >> 13) & 1) {
            outRight = motorRight;
        }
        if ((flags >> 14) & 1) {
            outCenter = motorCenter;
        }

        // Apply the final motor values to the device
        applyMotorValues(outRight, outLeft, outCenter);
        return 1;
    }

    // No rumble flags set: reset global rumble state to default
    // g_rumbleData is a global pointer to a 4-int structure (RumbleState)
    // +0x00: left motor time
    // +0x04: right motor time
    // +0x08: center motor time
    // +0x0C: default/constant value
    g_rumbleData[0] = 0;      // left motor time
    g_rumbleData[1] = 0;      // right motor time
    g_rumbleData[2] = 0;      // center motor time
    g_rumbleData[3] = 0x00e2b1a4; // some default constant, possibly stored elsewhere
    return 0;
}