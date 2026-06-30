// FUNC_NAME: EARSObject::update
// Function address: 0x00466860
// Role: Simple delegator to common initialization/update routine at 0x00466090.
// Called by many game subsystems (e.g., FUN_00910d00, FUN_00911630, etc.) suggesting a base class update method.
void EARSObject::update(void)
{
    // Forward to the actual implementation
    FUN_00466090();
    return;
}