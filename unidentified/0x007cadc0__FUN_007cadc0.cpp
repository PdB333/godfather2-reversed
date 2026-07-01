// FUNC_NAME: UnknownClass::getFloatDefault
float UnknownClass::getFloatDefault() // __fastcall, this in ecx
{
    // +0x10 : float* m_pDynamicFloat; if non-null, dereference to get value
    if (*(float**)((int)this + 0x10) != (float*)0x0) {
        return (float)**(float**)((int)this + 0x10); // return *m_pDynamicFloat
    }
    // Fallback to global default value
    return s_defaultFloatValue; // DAT_00d5779c
}