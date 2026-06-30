// FUNC_NAME: checkCPURequirements
void checkCPURequirements(int languageIndex, undefined4 param_2, undefined4 param_3)
{
  int cpuFeatureLevel;
  int finalFeatureLevel;
  uint cpuFeatureMask;
  uint requiredFeatureMask;
  wchar_t *errorTitle[4];
  wchar_t *errorMessage;
  undefined *local_10;
  undefined *local_c;
  wchar_t *local_8;
  undefined **local_4;
  
  cpuFeatureLevel = getCPUFeatureLevel(); // 0x006986e0 - returns CPU feature level (0-9?)
  finalFeatureLevel = cpuFeatureLevel;
  if (cpuFeatureLevel == 9) {
    finalFeatureLevel = getCPUFeatureLevelAlt(); // 0x0069d8a0 - alternative check for level 9
  }
  g_cpuFeatureLevel = finalFeatureLevel; // DAT_00e50b74 - global CPU feature level
  
  cpuFeatureMask = getCPUCapabilities(); // 0x0049bc10 - returns CPU capabilities bitmask
  requiredFeatureMask = getRequiredCPUCapabilities(); // 0x0049bc40 - returns required capabilities bitmask
  
  if ((requiredFeatureMask & cpuFeatureMask) == 0) {
    // CPU does not meet minimum requirements - show error in appropriate language
    errorTitle[0] = L"Error";
    errorMessage = L"Error";
    errorTitle[1] = L"Chyba"; // Czech
    errorTitle[2] = L"Erreur"; // French
    errorTitle[3] = L"Fehler"; // German
    local_14 = L"Errore"; // Italian
    local_10 = &DAT_00d5c3e0; // Spanish error string
    local_c = &DAT_00d5c3d0; // Japanese? error string
    local_4 = (undefined **)0xd5c3c4; // Korean? error string
    
    errorTitle[0] = L"Your CPU does not meet The Godfather™ II minimum requirements.";
    errorTitle[1] = L"Vaše CPU nesplňuje minimální požadavky pro hru Kmotr® II.";
    errorTitle[2] = L"Votre processeur est insuffisant pour permettre le bon fonctionnement du jeu le Parrain® II.";
    errorTitle[3] = L"Ihre CPU erfüllt nicht die Mindestvoraussetzungen von Der Pate® II.";
    local_14 = L"La tua CPU non rispetta i requisiti minimi de Il Padrino® II.";
    local_10 = &DAT_00d5bd00; // Spanish
    local_c = &DAT_00d5bc30; // Japanese
    local_8 = L"Tu equipo no cumple los requisitos mínimos de El Padrino® II.";
    local_4 = &PTR_DAT_00d5baf8; // Korean
    
    MessageBoxW((HWND)0x0, errorTitle[languageIndex], errorTitle[languageIndex], 0x40010); // MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL
    __exit(0);
  }
  
  initGameSystems(); // 0x0069d7c0
  g_hInstance = param_3; // DAT_00e50b70 - store HINSTANCE
  initApplication(0, 0); // 0x0068aeb0
  return;
}