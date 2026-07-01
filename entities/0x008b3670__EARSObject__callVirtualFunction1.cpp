// FUNC_NAME: EARSObject::callVirtualFunction1
// Function address: 0x008b3670
// Calls the second virtual function (vtable offset 4) and returns this pointer.
int* EARSObject::callVirtualFunction1() {
    (**(code**)(*this + 4))();
    return this;
}