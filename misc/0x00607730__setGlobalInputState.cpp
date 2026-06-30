// FUNC_NAME: setGlobalInputState
void __thiscall setGlobalInputState(short inputValue1, undefined2 inputFlags, undefined1 inputByte1, undefined1 inputByte2)
{
    // Compare with previous state: if either the primary value (0x0120587c) or the secondary value (0x01205880) changed,
    // set the dirty flag (0x01205764) to 1, otherwise clear it.
    if ((DAT_0120587c != inputValue1) || (DAT_01205764 = 0, DAT_01205880 != inputValue2)) {
        DAT_01205764 = 1;
    }

    // Store the new input values into global state
    DAT_011a0f24 = inputValue1;   // +0x?? primary value
    DAT_0119da5c = inputValue2;   // +0x?? secondary value
    DAT_0119474a = inputByte1;    // +0x?? byte 1
    DAT_011d97e8 = inputFlags;    // +0x?? flags (16-bit)
    DAT_0119474b = inputByte2;    // +0x?? byte 2

    // Mark that input state is updated
    DAT_01205763 = 1;
}