// FUNC_NAME: Entity::setFlagAndProcess
void __thiscall Entity::setFlagAndProcess(Entity* this, uint flag)
{
    // Set a flag at offset +0x14 (bitfield flags)
    this->flags |= flag;

    // Yield/process messages multiple times (likely to allow pending events to be handled)
    // FUN_004df710 is a common yield/process function in the EARS engine
    processMessages(); // FUN_004df710
    processMessages();
    processMessages();
    processMessages();
}