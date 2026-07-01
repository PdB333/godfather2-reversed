// FUNC_NAME: BaseComponent::queryInfo
void __thiscall BaseComponent::queryInfo(int *thisPtr, undefined4 param2)
{
    undefined4 outputA = 0;   // local_10
    undefined4 outputB = 0;   // local_14
    undefined4 outputC = 0;   // local_c
    undefined4 *outputPtr = &outputC; // local_18 – pointer to outputC (may be reassigned by virtual call)
    // outputD and outputE are unused in original (local_8, local_4)
    undefined4 outputD = 0;   // local_8
    undefined4 outputE = 0;   // local_4

    // Virtual function at vtable+0x2c (likely an interface method)
    // It receives param2, addresses of outputA, outputB, and pointer to outputPtr
    (**(code **)(*thisPtr + 0x2c))(param2, &outputA, &outputB, &outputPtr);
}