// FUNC_NAME: LocaleManager::initializeLocale
void LocaleManager::initializeLocale(void)
{
  int languageIndex;
  int regionIndex;
  char *localeString;
  uint refCount;
  code *destructor;
  int configResult[3];
  code *callbackFunc;

  // Lock some global mutex or resource
  lockGlobalResource(&DAT_00e2f044);

  // Read "Locale" from configuration system
  readConfigString(&localeString, "Locale", configResult);

  // If config result indicates success, call a callback function (likely a cleanup or notification)
  if (configResult[0] != 0) {
    (*callbackFunc)(configResult[0]); // callbackFunc might be set by readConfigString? Unclear.
  }

  // Handle reference counting or error checking
  if (refCount != 0) {
    if (2 < refCount) {
      logError(2, 0);
    }
    // Check if a certain global flag is set
    int flag = checkGlobalFlag(&DAT_00d5ce2c);
    if (flag == 0) {
      clearGlobalFlag(&DAT_00d5ce28);
    }
  }

  // Get the locale string (use default if null)
  char *effectiveLocale = localeString;
  if (localeString == (char *)0x0) {
    effectiveLocale = &DAT_0120546e; // Default locale string "en" or similar
  }

  // Extract language and region codes from the locale string
  languageIndex = getLanguageCodeIndex(effectiveLocale);
  regionIndex = getRegionCodeIndex(effectiveLocale);

  // If language index is valid, set language
  if (-1 < languageIndex) {
    setLanguage(languageIndex);
  }

  // If region index is -1 (not found), reinitialize some managers
  if (regionIndex == -1) {
    // Call virtual function at offset 0x28 on two global objects (e.g., AudioManager, InputManager)
    (**(code **)(*DAT_01129a74 + 0x28))();
    (**(code **)(*DAT_01130594 + 0x28))();
  }
  else {
    // Set language code via a different mechanism
    setLanguageCode("SetLanguageCode", 0, &DAT_00d8963c, 1, effectiveLocale2); // Note: effectiveLocale2? Might be a copy.
    if (regionIndex < 0) {
      DAT_00e5672c = 3; // Language type: e.g., LANG_UNKNOWN
    }
    else {
      setRegion(regionIndex);
      DAT_00e5672c = 2; // Language type: e.g., LANG_LOCALIZED
    }

    // Reset some state in a global object
    int *globalObj = DAT_01129928;
    *(undefined4 *)(globalObj + 0x60) = 0;

    // Register a callback for locale changes (if not already registered)
    if ((DAT_01130590 & 1) == 0) {
      registerCallback(globalObj + 0x14, &localeChangeCallback, 0);
      DAT_01130590 |= 1;
    }
  }

  // Free the locale string if it was allocated
  if (localeString != (char *)0x0) {
    (*destructor)(localeStringapsed); // destructor likely points to a free function
  }

  return;
}