// FUNC_NAME: Entity::getFlagIfAvailable
uint Entity::getFlagIfAvailable(uint flagMask)
{
    // local_4: output value from virtual method
    uint outValue = 0;
    // Call virtual method at vtable offset 0x10 (likely some property getter)
    // The method returns a boolean indicating success; if true, outValue is set to some value
    bool success = (**(code (__thiscall **)(Entity*, uint, uint*))(this->vtable + 0x10))(this, flagMask, &outValue);
    return success ? flagMask : 0;
}