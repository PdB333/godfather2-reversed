// FUNC_NAME: SomeManager::getDebugValue
// Function address: 0x00543070
// This is a simple member function that calls a virtual function (vtable offset 0x1f8)
// of the same object to retrieve an integer value via an output parameter.
// The virtual function takes an index (param_2) and a pointer to store the returned value.
// The local variable local_4 is unused.

void __thiscall SomeManager::getDebugValue(int index)
{
    int outValue = 0;
    // Call virtual function at vtable offset 0x1f8 (likely a getter by index)
    (this->*(void (__thiscall SomeManager::*)(int, int*))0x1f8)(index, &outValue);
    // outValue is not further used in this function; the caller probably uses it via stack
}