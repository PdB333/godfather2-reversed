// FUNC_NAME: ControllerManager::scaleAnalogInput
// Address: 0x00592630
// Purpose: Scales analog stick input by a constant factor and applies offset conversion.
// Parameters:
//   this: pointer to a controller state structure (byte array at offsets 0 and 2 store raw 8-bit values)
//   param_2: unknown parameter (likely a float or int, passed to FUN_0056d040)
// Notes:
//   - Reads two ushorts from the 'this' pointer as the base analog values (at offsets 0 and 4? or from global register)
//   - Computes scaled differences using a constant DAT_00e44820
//   - Calls FUN_0056d040 (likely a vector/polar conversion or output function)
// TODO: Exact field offsets and register usage need further analysis

void __thiscall ControllerManager::scaleAnalogInput(byte* this, undefined4 param_2)
{
    ushort* baseAnalogValues; // EAX - points to analog values within the controller struct
    float scaleFactor = DAT_00e44820; // global sensitivity/deadzone scale

    // Read ushort values from the struct (likely left/right analog stick or X/Y components)
    float rawX = (float)baseAnalogValues[0];          // first ushort at offset 0
    float rawY = (float)baseAnalogValues[2];          // third ushort at offset 4

    // Convert byte values at this[0] and this[2] (8-bit to 12-bit shift) into float
    float byteX = (float)((unsigned int)this[0] << 4);
    float byteY = (float)((unsigned int)this[2] << 4);

    // Compute scaled and negated delta: result = scale * (byte - raw)
    float deltaX = -(rawX * scaleFactor - byteX * scaleFactor);
    float deltaY = -(rawY * scaleFactor - byteY * scaleFactor);
    // Equivalent: deltaX = scaleFactor * (byteX - rawX)
    //             deltaY = scaleFactor * (byteY - rawY)

    // Call external function with the two computed deltas and the original param_2
    FUN_0056d040(deltaX, deltaY, param_2);
}