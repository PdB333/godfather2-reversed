// FUNC_NAME: Entity::constructor
void Entity::constructor(int* thisPtr, int someParam)
{
    // unaff_EDI is a local register variable pointing to a stack location that holds thisPtr
    int* localThis = thisPtr; // *unaff_EDI = param_1

    // Call virtual init function at vtable+0x8
    (thisPtr->vtable[2])();

    if (someParam != 0)
    {
        // Call external function to create/attach a resource
        int resourceHandle = FUN_004265d0(someParam, thisPtr); // +0x4 member
        thisPtr[1] = resourceHandle; // unaff_EDI[1] = uVar1

        // Call virtual setData function at vtable+0x4
        (thisPtr->vtable[1])(someParam, 0);

        // Call virtual postConstruct function at vtable+0xc
        (thisPtr->vtable[3])();
    }
    else
    {
        thisPtr[1] = 0; // unaff_EDI[1] = 0
        // Call virtual postConstruct function at vtable+0xc
        (thisPtr->vtable[3])();
    }
}