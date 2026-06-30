// FUNC_NAME: initializeState
void __fastcall initializeState(int* param1)
{
    // +0x00: active (int) - set to 1 (enabled)
    // +0x04: counter1 (int) - set to 0
    // +0x08: counter2 (int) - set to 0
    // +0x0C: stateFlag (byte) - set to 0
    param1[0] = 1;
    param1[1] = 0;
    param1[2] = 0;
    *(char*)(param1 + 3) = 0;  // writes only the low byte of the fourth int (offset 0x0C)
}