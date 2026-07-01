// Xbox PDB: EARS_Apt_UIPlayerFamilyTree_ShowPromotionConfirmationPopup
// FUNC_NAME: PauseMenuCrewPromotion::showPromotionDialog

void __fastcall PauseMenuCrewPromotion::showPromotionDialog(int this)
{
    int dialogHandle;
    int rankIndex;
    int globalRankId;
    void* nameTextStruct;
    int nameTextVal;
    int nameTextSize;
    code* nameTextRelease;
    void* promptTextStruct;
    int promptTextVal;
    int promptTextSize;
    code* promptTextRelease;
    char formattedString[4112];
    int dummyRet;

    dummyRet = 0x9814aa; // likely stack cookie or unused return address

    dialogHandle = FUN_009c8e50(0xf0);
    if (dialogHandle == 0) {
        dialogHandle = 0;
    } else {
        dialogHandle = FUN_00982280(0); // create dialog widget with id=0
    }

    FUN_00604be0(); // push UI context or begin dialog construction

    int localeHandle = DAT_012234a4; // global UI locale manager

    // Initialize name text struct
    nameTextStruct = 0;
    nameTextVal = 0;
    nameTextSize = 0;
    nameTextRelease = 0;

    // Get localized string for the crew member's name from offset 0x100
    FUN_00603330(*(undefined4 *)(this + 0x100), &nameTextStruct);
    void* nameStr = nameTextStruct;
    if (nameTextStruct == 0) {
        nameStr = &DAT_0120546e; // fallback empty string
    }
    // Set control id 0x6e to the crew member's name
    FUN_00604c10(0x6e, nameStr);

    // Determine rank string from global data
    rankIndex = *(int *)(DAT_0112989c + *(int *)(this + 0x6c) * 0x24 + 0x1c);
    if (rankIndex == 3) {
        FUN_00604c10(0x72, "{$rank_capo}");
    } else if (rankIndex == 4) {
        FUN_00604c10(0x72, "{$rank_underboss}");
    } // else no rank set (skip)

    // Initialize prompt text struct
    promptTextStruct = 0;
    promptTextVal = 0;
    promptTextSize = 0;
    promptTextRelease = 0;

    // Format the promotion prompt string
    FUN_006038a0(localeHandle, formattedString, &promptTextStruct, "$pause_promote_pick");
    void* promptStr = promptTextStruct;
    if (promptTextStruct == 0) {
        promptStr = &DAT_0120546e;
    }
    // Show dialog with the prompt
    FUN_00981eb0(promptStr);

    // Add specialty options based on flag bits at offset 0x10c
    if ((*(byte *)(this + 0x10c) & 4) == 0) {
        FUN_00981e70("$crew_specialty_demolition", 0, 4);
    }
    if ((*(byte *)(this + 0x10c) & 8) == 0) {
        FUN_00981e70("$crew_specialty_arsonist", 0, 8);
    }
    if ((*(byte *)(this + 0x10c) & 0x10) == 0) {
        FUN_00981e70("$crew_specialty_safe_cracker", 0, 0x10);
    }
    if ((*(byte *)(this + 0x10c) & 0x20) == 0) {
        FUN_00981e70("$crew_specialty_engineer", 0, 0x20);
    }
    if ((*(byte *)(this + 0x10c) & 0x40) == 0) {
        FUN_00981e70("$crew_specialty_medic", 0, 0x40);
    }
    if ((*(byte *)(this + 0x10c) & 0x80) == 0) {
        FUN_00981e70("$crew_specialty_bruiser", 0, 0x80);
    }

    // Set dialog callback (likely for handling selection)
    *(code**)(dialogHandle + 0x14) = &LAB_009809c0;

    // Finalize and display the dialog
    FUN_00982e10();

    // Release allocated text structs
    if (promptTextStruct != 0) {
        (*promptTextRelease)(promptTextStruct);
    }
    if (nameTextStruct != 0) {
        (*nameTextRelease)(nameTextStruct);
    }

    FUN_00604c00(); // pop UI context or end dialog construction
    return;
}