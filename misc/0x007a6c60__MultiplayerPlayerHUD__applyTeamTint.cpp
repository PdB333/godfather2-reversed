// FUNC_NAME: MultiplayerPlayerHUD::applyTeamTint
void __thiscall MultiplayerPlayerHUD::applyTeamTint(int *this, int *pEffectInfo)
{
    char *g_currentColorString = (char *)PTR_s_MultiPlayerBlue_00e5280c; // default blue team string
    if (this[0x7bd] == 0) { // +0x1EF4: team flag (0 = blue, non-zero = red)
        g_currentColorString = (char *)PTR_s_MultiPlayerRed_00e52810;
    }

    int color[3] = {0, 0, 0};          // local_10: for intermediate color operations
    code *deferredCall = (code *)0x0;   // local_4

    if (*pEffectInfo == 0) {
        // Start effect: apply team color globally
        *(char **)(DAT_0112990c + 0xc) = g_currentColorString; // set global tint string
    } else {
        // Stop effect: fade out and clear tint
        FUN_004d3e20(this + 0xac);      // +0x2B0: m_customTextString
        FUN_004d3f10(0, 0, 0);          // clear color
        *(int *)(DAT_0112990c + 0xc) = 0; // clear global tint
    }

    FUN_007a60c0(1); // start fade overlay (1 = fade in)

    if (*pEffectInfo == 0) {
        // Starting: show subtitle/text
        char *text = (char *)this[0xac]; // +0x2B0: m_customTextString
        if (text == (char *)0x0) {
            text = (char *)&DAT_0120546e; // default text
        }
        FUN_009c58c0(0, text); // set subtitle
    } else {
        // Stopping: apply color again and update effect
        *(char **)(DAT_0112990c + 0xc) = g_currentColorString;
        FUN_004d3e20(color);             // set intermediate color
        FUN_009bf340(this, pEffectInfo); // update effect state
        FUN_004d3e20(color);             // clear intermediate
    }

    *(int *)(DAT_0112990c + 0xc) = 0;    // clear global tint

    // Countdown timer at +0x294C
    if ((0 < this[0xa53]) && (int countdown = this[0xa53] - 1, this[0xa53] = countdown, countdown == 0)) {
        this[0x927] |= 2;                // +0x249C: set flag (bit 1)
        if (*(int *)(DAT_01223484 + 0xc) == 0) {
            FUN_009ae900(0);              // unlock or enable something
        }
    }

    (**(code **)(*this + 0x304))();      // virtual call (update)

    int obj = FUN_0043b870(DAT_01130950); // get audio/manager object
    if ((obj != 0) && (*(int *)(obj + 0x20) != 0)) {
        FUN_00998270();                   // play sound
    }

    FUN_007a4250(1);                      // resume fade
    (**(code **)(*this + 0xfc))();        // virtual call (render)
    FUN_00472120();                       // end scene or flush
    (**(code **)(*this + 0x304))();       // virtual call (cleanup)

    if (color[0] != 0) {
        (*deferredCall)(color[0]);        // deferred callback
    }
    return;
}