// FUNC_NAME: SomeGameObject::checkActiveAndUpdate
void __thiscall SomeGameObject::checkActiveAndUpdate(void)
{
    // Check if the active flag at offset 0x80 is false (0)
    if ( !*(bool *)((int)this + 0x80) )
    {
        // If not active, call the reset/stop function at 0x6be020
        SomeGameObject::resetOrStop(); // TODO: rename actual function
    }
    // Otherwise do nothing
}