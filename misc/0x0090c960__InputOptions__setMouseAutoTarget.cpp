// FUNC_NAME: InputOptions::setMouseAutoTarget
void __thiscall InputOptions::setMouseAutoTarget(int value)
{
    // Store the flag locally (+0x34)
    this->mouseAutoTarget = value;
    // Persist to configuration system
    SetConfigInt("Mouse.AutoTarget", value);
}