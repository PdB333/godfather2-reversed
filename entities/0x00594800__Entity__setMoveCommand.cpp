// FUNC_NAME: Entity::setMoveCommand
void __thiscall Entity::setMoveCommand(float duration, short commandId, int param1)
{
    // +0x158: float - possibly timer or distance
    *(float *)(this + 0x158) = duration;

    // If commandId is very large ( > 0xFFFF ), call a global handler
    if (commandId > 0xFFFF) {
        // DAT_01205590 points to a global function table
        (**(code **)(*(int *)0x01205590 + 4))(); // indirect call to some handler
    }

    // If commandId is non-zero, set up a command structure at +0xF0
    if ((short)commandId != 0) {
        *(int *)(this + 0xF0) = 0;          // +0xF0: int - timer/counter
        *(short *)(this + 0xF4) = 1;        // +0xF4: short - state? size=2
        *(short *)(this + 0xF6) = commandId;// +0xF6: short - command type/ID
        *(int *)(this + 0xFC) = param1;     // +0xFC: int/ptr - extra parameter
        *(short *)(this + 0xF8) = 0;        // +0xF8: short - padding/flag
    }

    // Clear bit 9 (0x200) at offset +0x7C (some flag)
    *(unsigned int *)(this + 0x7C) &= 0xFFFFFDFF;
}