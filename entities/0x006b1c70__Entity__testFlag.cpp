// FUNC_NAME: Entity::testFlag
uint Entity::testFlag(uint flagMask)
{
    // local_4 is unused output from the virtual check function
    bool dummy;
    bool result = (this->vtable[4])(flagMask, &dummy);
    // If the flag is set, return the mask; otherwise return 0
    return -(uint)result & flagMask;
}