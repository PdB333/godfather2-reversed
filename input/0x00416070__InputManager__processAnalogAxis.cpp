// FUNC_NAME: InputManager::processAnalogAxis
void __thiscall InputManager::processAnalogAxis(uint actionId, float *axisValues, uint param_3)
{
    // In EAX: this pointer
    // ESI: output event struct pointer (unaff_ESI)
    float deltaX = axisValues[0] - *(float *)(this + 0xC);  // subtract deadzone/center offset for X
    float deltaZ = axisValues[2] - *(float *)(this + 0x10); // subtract deadzone/center offset for Z (axisValues[1] unused?)

    if (deltaX < 0.0f) {
        deltaX = 0.0f;
    }
    if (deltaZ < 0.0f) {
        deltaZ = 0.0f;
    }

    // Scale using global analog scaling factor (DAT_0110b15c) to 12-bit range [0..4095]
    int scaledX = (int)(DAT_0110b15c * deltaX);
    int scaledZ = (int)(DAT_0110b15c * deltaZ);

    if (scaledX > 0xFFF) {
        scaledX = 0xFFF;
    }
    if (scaledZ > 0xFFF) {
        scaledZ = 0xFFF;
    }

    // Create an input event record (type 2 = analog axis?)
    FUN_00415ea0(this,                // this
                 *(uint *)(this + 8), // device/controller ID?
                 scaledX,
                 scaledZ,
                 2,                   // event type (analog)
                 (InputEvent *)unaff_ESI); // output event struct (passed in ESI from caller)

    // Dispatch or queue the event
    FUN_00414aa0();

    // Fill in the output event struct fields
    ((InputEvent *)unaff_ESI)->field_0x10 = scaledX;  // +0x10
    ((InputEvent *)unaff_ESI)->field_0x14 = scaledZ;  // +0x14
    ((InputEvent *)unaff_ESI)->field_0x0C = param_3;   // +0x0C
    ((InputEvent *)unaff_ESI)->field_0x20 = actionId;  // +0x20
}