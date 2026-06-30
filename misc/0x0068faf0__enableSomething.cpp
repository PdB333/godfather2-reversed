// FUNC_NAME: enableSomething
// Function at 0x0068faf0 - Wrapper that calls internal method with a constant flag (1) and a second parameter.
void __thiscall enableSomething(void* param)
{
    this->setEnabledInternal(1, param);
}