// FUNC_NAME: EARSObject::constructor
// Address: 0x00564b60
// Role: Constructor for EARSObject. Calls internal initialization, then optionally invokes destructor if the exception flag's first bit is set.
// Note: This is a typical EA EARS pattern: a placement-new constructor that can automatically destroy on construction failure.
EARSObject* __thiscall EARSObject::constructor(EARSObject* this, byte exceptionFlag)
{
    EARSObject::constructInternal(this); // Main initialization logic at 0x00564b90
    if ((exceptionFlag & 1) != 0)
    {
        EARSObject::destroy(this); // Destructor at 0x009c8eb0 (e.g., EARSObject::~EARSObject)
    }
    return this;
}