// FUNC_NAME: SomeClass::setValue
void SomeClass::setValue(int newValue)
{
    // Simple setter: assign the provided value to the member variable
    *(int *)this = newValue;
}