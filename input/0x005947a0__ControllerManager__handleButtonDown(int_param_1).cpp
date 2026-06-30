// FUNC_NAME: ControllerManager::handleButtonDown(int param_1)
void ControllerManager::handleButtonDown(int param_1)
{
    // EDI holds the button index (16-bit value, possibly from a previous operation)
    int buttonIndex = unaff_EDI;

    if (buttonIndex > 0xFFFF) {
        // Invalid index – call global error handler via vtable at DAT_01205590
        (*(code **)(*DAT_01205590 + 4))();
    }

    if ((short)buttonIndex != 0) {
        // Populate controller slot state (each slot is 0x44 bytes, but these offsets go beyond)
        *(int*)(this + 0x100) = 0;               // +0x100: event type (e.g., button down)
        *(short*)(this + 0x104) = 1;             // +0x104: flag (active?)
        *(short*)(this + 0x106) = (short)buttonIndex; // +0x106: actual button code
        *(int*)(this + 0x10C) = param_1;         // +0x10C: parameter (pressure/analog)
        *(short*)(this + 0x108) = 1;             // +0x108: additional flag
    }

    // Clear bit 8 (0x100) in a state field at +0x7C
    *(int*)(this + 0x7C) &= 0xFFFFFEFF;

    // Call virtual dispatch method (vtable slot 1, after destructor)
    (*(void (**)())(*(int*)this + 4))();
}