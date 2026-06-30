// FUNC_NAME: sendCommandToSystem
void sendCommandToSystem(int param_1)
{
    // Global pointer to engine context (0x012233a8)
    // Offset +4 holds pointer to the target system object
    void* systemObj = *(void**)(DAT_012233a8 + 4);
    // Dispatch command to the system
    FUN_0042e7e0(systemObj, param_1);
    return;
}