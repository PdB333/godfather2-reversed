// FUNC_NAME: resetInputGlobalState

void resetInputGlobalState(void)
{
    // Set three pointer fields to the same value (likely a shared function pointer or data)
    g_inputGlobals.pField1 = g_somePointer;       // DAT_01219200 = DAT_00e2b1a4
    g_inputGlobals.pField2 = g_somePointer;       // DAT_01219204 = DAT_00e2b1a4
    g_inputGlobals.pField3 = g_somePointer;       // DAT_01219208 = DAT_00e2b1a4

    // Zero a block of 7 fields (0x12191e0–0x12191ec and 0x12191f0–0x12191fc)
    g_inputGlobals.intFieldA = 0;                 // _DAT_012191ec
    g_inputGlobals.intFieldB = 0;                 // _DAT_012191e8
    g_inputGlobals.intFieldC = 0;                 // _DAT_012191e4
    g_inputGlobals.intFieldD = 0;                 // _DAT_012191e0
    g_inputGlobals.intFieldE = 0;                 // _DAT_012191fc
    g_inputGlobals.intFieldF = 0;                 // _DAT_012191f8
    g_inputGlobals.intFieldG = 0;                 // _DAT_012191f4
    g_inputGlobals.intFieldH = 0;                 // _DAT_012191f0

    // Zero additional fields
    g_inputGlobals.intFieldI = 0;                 // _DAT_0121920c
    g_inputGlobals.intFieldJ = 0;                 // _DAT_0121921c
    g_inputGlobals.intFieldK = 0;                 // DAT_01219218
    g_inputGlobals.intFieldL = 0;                 // DAT_01219214
    g_inputGlobals.intFieldM = 0;                 // DAT_01219210
    g_inputGlobals.intFieldN = 0;                 // DAT_01219220
    g_inputGlobals.intFieldO = 0;                 // DAT_0121922c

    // Set two more pointer fields to a different shared value
    g_inputGlobals.pField4 = g_anotherPointer;    // DAT_01219224 = DAT_00e2eb58
    g_inputGlobals.pField5 = g_anotherPointer;    // DAT_01219228 = DAT_00e2eb58

    // Zero remaining fields
    g_inputGlobals.intFieldP = 0;                 // DAT_01219230
    g_inputGlobals.intFieldQ = 0;                 // DAT_01219240

    return;
}