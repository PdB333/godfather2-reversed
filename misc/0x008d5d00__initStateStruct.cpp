// FUNC_NAME: initStateStruct

void __fastcall initStateStruct(StateStruct* state)
{
    // Initialize struct members (offsets: +0x00, +0x04, +0x08, +0x0C, +0x10, +0x14)
    state->field_0 = 0;
    state->field_4 = 0;
    state->field_8 = 0;
    state->field_10 = 0;
    state->field_12 = g_globalValue1;   // +0x0C, from _DAT_00d5c458
    state->field_20 = g_globalValue2;   // +0x14, from _DAT_00d5780c
}