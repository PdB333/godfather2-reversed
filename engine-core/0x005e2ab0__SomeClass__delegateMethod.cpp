// FUNC_NAME: SomeClass::delegateMethod
// Address: 0x005e2ab0 - Simple wrapper that delegates to the actual implementation at 0x005e1fd0
void SomeClass::delegateMethod(void)
{
    actualImplementation();
    return;
}