// FUNC_NAME: SomeClass::SetTwoFields
void __thiscall SomeClass::SetTwoFields(int param_2, int param_3)
{
    // +0xDC: field_0xDC
    *(int *)(this + 0xDC) = param_2;
    // +0xE0: field_0xE0
    *(int *)(this + 0xE0) = param_3;
}