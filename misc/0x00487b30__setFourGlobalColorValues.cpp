// FUNC_NAME: setFourGlobalColorValues
void __cdecl setFourGlobalColorValues(const uint8_t* color)
{
    // Global color slots (3 bytes each, probably RGB)
    DAT_01163d98[0] = color[0];
    DAT_01163d98[1] = color[1];
    DAT_01163d98[2] = color[2];
    DAT_01163d9c[0] = color[0];
    DAT_01163d9c[1] = color[1];
    DAT_01163d9c[2] = color[2];
    DAT_01163da0[0] = color[0];
    DAT_01163da0[1] = color[1];
    DAT_01163da0[2] = color[2];
    DAT_01163da4[0] = color[0];
    DAT_01163da4[1] = color[1];
    DAT_01163da4[2] = color[2];
}