// Xbox PDB: EARS_Apt_HostGameScreen_ShowDonChallengeReceivedPopup
// FUNC_NAME: OnlineChallengeManager::showChallengeRequestDialog
void OnlineChallengeManager::showChallengeRequestDialog(void* challengeRequest)
{
    int dialogPtr;
    char* formattedString;
    int stringAlloc;  // placeholder for string metadata
    int stringSize;
    void (*stringDeallocator)(char*);
    struct { int id1; int id2; }* userData;

    // Allocate dialog object (size 0xF0)
    dialogPtr = (int)operatorNew(0xF0);
    if (dialogPtr != 0) {
        dialogPtr = (int)objectInitializer(dialogPtr, 0); // likely constructor call
    }

    // Prepare string buffer (local_10, local_c, local_8, local_4)
    formattedString = nullptr;
    stringAlloc = 0;
    stringSize = 0;
    stringDeallocator = nullptr;

    // Format challenge message: "challengerName would like to challenge you..."
    stringFormat(&formattedString, "%s would like to challenge you. Do you accept the challenge?",
                 *(char**)((char*)challengeRequest + 0x9C));

    // Set dialog type to 5 (likely challenge type)
    *(int*)(dialogPtr + 0x0C) = 5;

    // Set dialog title (use formatted string or default)
    char* title = formattedString;
    if (title == nullptr) {
        title = &defaultEmptyString; // DAT_0120546e placeholder
    }
    setDialogTitle(title, dialogPtr); // FUN_00981eb0

    // Add Yes/No options with return values
    addDialogOption("$mp_online_menu_yes", 1, 0, dialogPtr); // FUN_00981e70
    addDialogOption("$mp_online_menu_no",  0, 0, dialogPtr);

    // Set callback function pointer (offset 0x14)
    *(void**)(dialogPtr + 0x14) = &challengeDialogCallback; // LAB_0096c670

    // Allocate user data (two ints from challenge request)
    userData = (struct { int id1; int id2; }*)operatorNew(8);
    if (userData != nullptr) {
        userData->id1 = -1;
        userData->id2 = -1;
    }
    userData->id1 = *(int*)((char*)challengeRequest + 0x100);
    userData->id2 = *(int*)((char*)challengeRequest + 0xFC);
    *(struct { int id1; int id2; }**)(dialogPtr + 0x10) = userData;

    // Display the dialog
    showDialog(); // FUN_00982e10

    // Free formatted string if allocated
    if (formattedString != nullptr) {
        stringDeallocator(formattedString);
    }
}