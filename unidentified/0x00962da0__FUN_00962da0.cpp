// FUNC_NAME: SomeClass::setActionData
void __thiscall SomeClass::setActionData(int param_1, undefined4 *param_2, undefined4 param_3)
{
    // Copy 0x80 (128) bytes from param_2+8 into the buffer pointed to by this+0xec
    // This buffer is likely a reusable storage for action data (animation, state, etc.)
    memcpy(*(void**)(param_1 + 0xec), param_2 + 8, 0x80);

    // Store first two ints of param_2 into separate fields
    *(undefined4*)(param_1 + 0x164) = param_2[0]; // e.g., action ID or type
    *(undefined4*)(param_1 + 0x2d0) = param_2[1]; // e.g., additional parameter or timestamp
    *(undefined4*)(param_1 + 0x134) = param_3;     // e.g., duration or flag

    // Check the 6th integer (index 5) in param_2: if it's 1 or 2, set a flag to 1; else 0
    // This might indicate whether the action is a specific subtype (e.g., animation blend vs. override)
    if ((param_2[5] != 2) && (param_2[5] != 1)) {
        *(byte*)(param_1 + 0x145) = 0;
        return;
    }
    *(byte*)(param_1 + 0x145) = 1;
}