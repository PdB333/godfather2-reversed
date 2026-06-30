// FUNC_NAME: UnknownClass::setFloatParam (0x007222f0)

void __thiscall setFloatParam(float newValue)
{
    // +0x0C: some float member (e.g., m_floatValue)
    // +0x28: dirty flag (byte)
    if (newValue != *(float *)(this + 0x0C)) {
        *(unsigned char *)(this + 0x28) = 1;  // mark as changed
        *(float *)(this + 0x0C) = newValue;   // update the value
    }
}