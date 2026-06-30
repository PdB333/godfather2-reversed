// FUNC_NAME: Application::validateSystemRequirements
void __cdecl Application::validateSystemRequirements(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine)
{
    int languageIndex = detectSystemLanguage(); // FUN_006986e0
    if (languageIndex == 9) // Language unknown or unsupported
    {
        languageIndex = getDefaultLanguage(); // FUN_0069d8a0
    }
    g_language = languageIndex; // DAT_00e50b74

    // Check CPU capability flags
    uint cpuRequiredFeatures = getCPUMandatoryFeatures();  // FUN_0049bc10
    uint cpuAvailableFeatures = getCPUAvailableFeatures(); // FUN_0049bc40
    if ((cpuAvailableFeatures & cpuRequiredFeatures) == 0)
    {
        // CPU does not meet minimum requirements – show localized error
        wchar_t* errorTitles[4]; // Reused as message array with overflow for additional languages
        // Language 0: English
        // Language 1: Czech
        // Language 2: French
        // Language 3: German
        // Language 4: Italian
        // Language 5: Spanish
        errorTitles[0] = L"Error";
        errorTitles[1] = L"Chyba";
        errorTitles[2] = L"Erreur";
        errorTitles[3] = L"Fehler";
        wchar_t* italianTitle = L"Errore";
        wchar_t* spanishTitle = L"Error";
        // The following are actually part of the message array; in memory they follow errorTitles
        wchar_t* englishMsg = L"Your CPU does not meet The Godfather\u2122 II minimum requirements.";
        wchar_t* czechMsg = L"Va\u0161e CPU nespl\u0148uje minim\u00e1ln\u00ed po\u017eadavky pro hru Kmotr\u00ae II.";
        wchar_t* frenchMsg = L"Votre processeur est insuffisant pour permettre le bon fonctionnement du jeu le Parrain\u00ae II.";
        wchar_t* germanMsg = L"Ihre CPU erf\u00fcllt nicht die Mindestvoraussetzungen von Der Pate\u00ae II.";
        wchar_t* italianMsg = L"La tua CPU non rispetta i requisiti minimi de Il Padrino\u00ae II.";
        wchar_t* spanishMsg = L"Tu equipo no cumple los requisitos m\u00ednimos de El Padrino\u00ae II.";

        // The message box uses the same buffer for title and message (stack layout trick)
        wchar_t* pMsg = (wchar_t*)&errorTitles;
        // Overwrite the title array with the actual messages
        errorTitles[0] = englishMsg;
        errorTitles[1] = czechMsg;
        errorTitles[2] = frenchMsg;
        errorTitles[3] = germanMsg;
        // Languages 4 and 5 are accessed by memory overflow into subsequent variables
        *(wchar_t**)(&italianTitle) = italianMsg;   // corresponds to language 4
        *(wchar_t**)(&spanishTitle) = spanishMsg;   // corresponds to language 5
        // Show message box with language-specific message as both title and content
        MessageBoxW(NULL, pMsg[languageIndex], pMsg[languageIndex], MB_OK | MB_ICONSTOP);
        exit(0);
    }

    // CPU is sufficient - proceed with startup
    initializeSubsystem();       // FUN_0069d7c0
    g_commandLine = lpCmdLine;   // DAT_00e50b70
    setApplicationInstance(0,0); // FUN_0068aeb0(0,0)
}