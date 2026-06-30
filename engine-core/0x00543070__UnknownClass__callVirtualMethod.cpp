//FUNC_NAME: UnknownClass::callVirtualMethod
void __thiscall UnknownClass::callVirtualMethod(int param_2, int* outParam)
{
    int local_8 = 0; // Output buffer, initialized to 0
    int local_4 = 0; // Unused local

    // Call virtual function at vtable offset 0x1f8 (likely a getter or query)
    // The function takes param_2 and a pointer to local_8 as output
    (this->vtable[0x1f8])(param_2, &local_8);
}