// FUNC_NAME: EARSObject::initialize
EARSObject* EARSObject::initialize(unsigned int arg1, unsigned int arg2, unsigned int arg3)
{
    unsigned int resultStatus = 0;  // Output status from internal init
    // Delegate to internal initialization routine with a zero flag (probably false)
    internalInit(this, arg1, arg2, arg3, 0, &resultStatus);
    return this;
}