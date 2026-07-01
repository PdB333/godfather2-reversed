// Xbox PDB: EARS_Apt_UIMoneyPopup_OnShow
// FUNC_NAME: BettingUI::updateBetAmountDisplay
void __fastcall BettingUI::updateBetAmountDisplay(int this)
{
    int* pBetPreviousAmount; // pointer to bet previous amount at +0x50
    int iStringLength;
    char* pcStringBuffer;
    undefined1* puFreeString;
    int uLoop;
    undefined1* puStack_50;
    undefined4 uStack_4c;
    undefined4 uStack_48;
    code* pcStack_44;
    undefined1 auStack_40[32];
    undefined1 auStack_20[32];

    // +0x50: previous bet amount pointer (allocated string)
    pBetPreviousAmount = (int*)(this + 0x50);
    if (*(int*)(this + 0x50) != 0) {
        (**(code**)(this + 0x5c))(*(int*)(this + 0x50)); // free previous string
    }
    *pBetPreviousAmount = 0;
    *(undefined4*)(this + 0x58) = 0; // +0x58: max digits
    *(undefined4*)(this + 0x54) = 0; // +0x54: current digit count

    // Copy bet amount string from game state (strings at +0x100, +0x110, +0x120)
    // These are likely the same bet amount in different locales/formats
    FUN_00603330(0x93efa6cd, (undefined4*)(this + 0x100)); // hash for "betAmount"
    FUN_00603330(0xbae5ffbf, (undefined4*)(this + 0x110)); // hash for "betAmount2"
    FUN_00603330(0xf7b7113e, this + 0x120);                 // hash for "betAmount3"

    // Strip brackets [ ] from strings if present (e.g. for negative numbers?)
    if (1 < *(uint*)(this + 0x104)) {
        iStringLength = *(uint*)(this + 0x104) - 1;
        pcStringBuffer = *(char**)(this + 0x100);
        if ((*pcStringBuffer == '[') && (pcStringBuffer[iStringLength] == ']')) {
            FUN_004d45e0(iStringLength, 1); // remove trailing ]
            FUN_004d45e0(0, 1);             // remove leading [
        }
    }
    if (1 < *(uint*)(this + 0x114)) {
        iStringLength = *(uint*)(this + 0x114) - 1;
        pcStringBuffer = *(char**)(this + 0x110);
        if ((*pcStringBuffer == '[') && (pcStringBuffer[iStringLength] == ']')) {
            FUN_004d45e0(iStringLength, 1);
            FUN_004d45e0(0, 1);
        }
    }
    if (1 < *(uint*)(this + 0x124)) {
        iStringLength = *(uint*)(this + 0x124) - 1;
        if ((**(char**)(this + 0x120) == '[') && ((*(char**)(this + 0x120))[iStringLength] == ']')) {
            FUN_004d45e0(iStringLength, 1);
            FUN_004d45e0(0, 1);
        }
    }

    // +0xFC: flag indicating if amount is non-zero
    *(bool*)(this + 0xfc) = *(int*)(this + 0x104) != 0;

    // Initialize the betting UI element (5 digits max)
    FUN_004d3fe0(5); // UI element: set max digits
    FUN_004d4ad0(pBetPreviousAmount, &DAT_00d8c9c0, 5, *(undefined4*)(this + 0x60)); // format string

    // Clear the display
    FUN_005a04a0("ClearAmount", 0, &DAT_00d88e60, 0); // GFx method call

    // Set each digit from the amount string at +0x130 (likely pointer to digit array)
    uLoop = 0;
    if (*(int*)(this + 0x54) != 0) {
        do {
            **(undefined1**)(this + 0x130) = *(undefined1*)(uLoop + *pBetPreviousAmount);
            FUN_005a04a0("SetDigit", 0, &DAT_00d88e60, 0); // GFx method call
            uLoop = uLoop + 1;
        } while (uLoop < *(uint*)(this + 0x54));
    }

    // Get localized string for confirmation message
    puStack_50 = (undefined1*)0x0;
    uStack_4c = 0;
    uStack_48 = 0;
    pcStack_44 = (code*)0x0;
    FUN_00604000(*(undefined4*)(this + 100), &puStack_50, 1); // +0x64: localization ID
    puFreeString = puStack_50;
    if (puStack_50 == (undefined1*)0x0) {
        puFreeString = &DAT_0120546e; // empty string
    }

    // Format confirmation message: "{%s} {%s}: %s" using localized strings
    FUN_004d4ad0((undefined4*)(this + 0xec), "{%s} {%s}: %s", "$mp_online_menu_confirm_bet",
                 "$mp_online_max_bet", puFreeString);

    // Generate color codes for the display (using hash functions)
    FUN_005c4630(auStack_20, 0x20, &PTR_LAB_00d78708, 0x510c352b); // color1
    FUN_005c4630(auStack_40, 0x20, &PTR_LAB_00d78708, 0xb45419ab); // color2

    puFreeString = *(undefined1**)(this + 0xec);
    if (puFreeString == (undefined1*)0x0) {
        puFreeString = &DAT_0120546e; // empty string
    }

    // Show the amount display with confirmation message and colors
    FUN_005a04a0("ShowAmount", 0, &DAT_00d88e60, 3, puFreeString, auStack_20, auStack_40);

    // Free localized string if allocated
    if (puStack_50 != (undefined1*)0x0) {
        (*pcStack_44)(puStack_50);
    }
    return;
}