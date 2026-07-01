// FUNC_NAME: UIButton::deactivateAndCheckChild
void __fastcall UIButton::deactivateAndCheckChild(UIButton* thisPtr)
{
    // Deactivate button (ID 0x31) via scripting system
    uint8_t deactivateButtonId = 0x31;
    uint8_t unused = 0;
    FUN_005a04a0("DeactivateButton", 0, &DAT_00d8c174, 1, &deactivateButtonId);

    // Clear some flag field at offset +0x78
    *(uint32_t*)((uint8_t*)thisPtr + 0x78) = 0;

    // If child button pointer (+0x6c) is null, activate a different button
    if (*(uint32_t*)((uint8_t*)thisPtr + 0x6c) == 0) {
        // Set flag at +0x7c to 0
        *(uint8_t*)((uint8_t*)thisPtr + 0x7c) = 0;

        // Activate button (ID 0x30) via scripting
        uint8_t activateButtonId = 0x30;
        FUN_005a04a0("ActivateButton", 0, &DAT_00d8c174, 1, &activateButtonId);
    }

    // Call update on child button (function 0x009574f0)
    FUN_009574f0(*(uint32_t*)((uint8_t*)thisPtr + 0x6c));

    // If some condition flag at +0x50 is set, call additional handler
    if (*(uint8_t*)((uint8_t*)thisPtr + 0x50) != 0) {
        FUN_00957e30();
    }
}