// FUNC_NAME: Debug::setFlag
void Debug::setFlag(uint flag, uint value)
{
    // Calls internal debug flag setter with constant flag type 0x80 (likely a specific debug category)
    internalSetFlag(0x80, value);
}