// FUNC_NAME: GenericFlagChecker::getMaskedFlag
uint GenericFlagChecker::getMaskedFlag(uint flag)
{
    uint unusedOut;
    unusedOut = 0;
    char result = this->vtable->checkFlag(flag, &unusedOut); // vtable offset 0x10
    return -(result != '\0') & flag; // if checkFlag returns true, return flag; else 0
}