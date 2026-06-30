// FUNC_NAME: BaseObject::initializeComponents
void __thiscall BaseObject::initializeComponents(void)
{
    // This function is a constructor helper that calls two initialization subroutines.
    // The this pointer (passed in ECX, stored in EDI in the caller frame) is forwarded to both.
    this->initComponentA(); // FUN_00573fd0 - likely initializes first subsystem (e.g., base class part)
    this->initComponentB(); // FUN_00574080 - likely initializes second subsystem (e.g., derived class part)
    return;
}