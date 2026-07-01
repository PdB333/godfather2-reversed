// FUNC_NAME: ActionHandler::handleAction
// Address: 0x00872ff0
// This function handles various action IDs (10-17) for an entity/player state machine.
// It accesses fields at offsets +0x64 (this[0x19]) and +0x74 (this[0x1d]) from 'this'.
// Calls virtual method at vtable+0x2c (likely applyForce or setState).

undefined1 __thiscall ActionHandler::handleAction(int *this, undefined4 arg2, float arg3, undefined4 arg4, int actionId, undefined4 arg6)
{
    undefined1 result;
    int somePtr;
    int basePtr;
    undefined8 *someStructPtr;

    result = 1;
    switch (actionId) {
    case 10: // e.g., ACTION_START
        handleAction10(); // FUN_00872a30
        return 1;
    case 11: // e.g., ACTION_STOP
        handleAction11(); // FUN_00872af0
        return 1;
    case 12: // e.g., ACTION_PAUSE
        handleAction12(); // FUN_00872aa0
        return 1;
    case 13: // e.g., ACTION_SPECIAL
        // Check if this[0x19] (offset +0x64) is non-zero and not 0x48 (sentinel?)
        if ((this[0x19] != 0) && (this[0x19] != 0x48)) {
            somePtr = getSomePointer(); // FUN_00724ce0
            if (somePtr != 0) {
                // Call virtual method at vtable offset 0x2c (11th entry)
                (**(code **)(*this + 0x2c))(somePtr, 1, 1, 0, 0x3f800000, 0x3f800000); // applyForce? setState?
                return 1;
            }
        }
        break;
    case 14: // e.g., ACTION_RESET
        handleAction14(); // FUN_00872cd0
        return 1;
    case 15: // e.g., ACTION_UPDATE
        if ((this[0x19] != 0) && (this[0x19] != 0x48)) {
            somePtr = getSomePointer(); // FUN_00724ce0
            // Compute base pointer: if this[0x19] is non-zero, subtract 0x48 (offset to data?)
            if (this[0x19] == 0) {
                basePtr = 0;
            } else {
                basePtr = this[0x19] + -0x48; // treat this[0x19] as pointer minus 0x48
            }
            // Check field at offset 0x11c from basePtr
            if (*(int *)(basePtr + 0x11c) == 2) {
                someStructPtr = (undefined8 *)getSomeStruct(); // FUN_007254f0
                *(undefined8 *)(this + 0x1d) = *someStructPtr; // copy 8 bytes to this[0x1d] (offset +0x74)
                this[0x1f] = *(int *)(someStructPtr + 1); // copy next 4 bytes to this[0x1f] (offset +0x7c)
            } else {
                someStructPtr = (undefined8 *)getSomeStruct(); // FUN_007254f0
                *(undefined8 *)(this + 0x1d) = *someStructPtr;
                this[0x1f] = *(int *)(someStructPtr + 1);
            }
            if (somePtr != 0) {
                (**(code **)(*this + 0x2c))(somePtr, 1, 1, 0, 0x3f800000, 0x3f800000);
                return 1;
            }
        }
        break;
    case 16: // e.g., ACTION_SCALE
        // Scale vector at this+0x1d by arg3 * globalTimeDelta
        scaleVector(this + 0x1d, arg3 * _DAT_00d761e4, 0); // FUN_00470130
        return 1;
    case 17: // e.g., ACTION_FINALIZE
        if ((this[0x19] != 0) && (this[0x19] != 0x48)) {
            if (this[0x19] != 0) {
                setSomeFlag(1); // FUN_007251a0
                doSomething(); // FUN_00624d00
                return 1;
            }
            setSomeFlag(1); // FUN_007251a0
        }
        doSomething(); // FUN_00624d00
        return 1;
    default:
        // Fallback to base class handler
        result = baseHandler(arg2, arg3, arg4, actionId, arg6); // FUN_004ac700
    }
    return result;
}