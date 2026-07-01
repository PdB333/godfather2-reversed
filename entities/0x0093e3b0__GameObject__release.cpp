// FUNC_NAME: GameObject::release
void __thiscall GameObject::release(int thisPtr, int param_2)
{
    // Call cleanup function with the parameter (likely a context or reason)
    FUN_00939980(param_2);

    // Check if the object's destroyed flag (at offset +0x12) is zero (meaning not yet destroyed)
    if (*(short *)(thisPtr + 0x12) == 0) {
        // Perform additional destruction steps
        FUN_004d3bc0(param_2);
        FUN_00938890();
    }
}