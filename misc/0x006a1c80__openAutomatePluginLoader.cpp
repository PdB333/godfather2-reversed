// FUNC_NAME: openAutomatePluginLoader
undefined4 openAutomatePluginLoader(void)

{
  char cVar1;
  LPCSTR pCVar2;
  int iVar3;
  DWORD DVar4;
  char *_Format;
  char *pcVar5;
  WCHAR widePluginPath [2046];  // Wide char buffer for plugin path
  undefined4 uStack_4;
  
  uStack_4 = 0x6a1c8a;
  pCVar2 = DAT_0112a0d0;  // OpenAutomatePluginPath global string (likely UTF-8)
  
  // Calculate length of plugin path string
  do {
    cVar1 = *pCVar2;
    pCVar2 = pCVar2 + 1;
  } while (cVar1 != '\0');
  
  // Convert multi-byte (UTF-8) plugin path to wide char for Windows API
  iVar3 = MultiByteToWideChar(0xfde9,  // CP_UTF8
                               0,      // No flags
                               DAT_0112a0d0,  // Source string
                               (int)(pCVar2 + (1 - (int)(DAT_0112a0d0 + 1))),  // Source length
                               widePluginPath,  // Destination buffer
                               0x800);  // Buffer size in wide chars (2048)
  
  if (iVar3 != 0) {
    // Load the plugin DLL
    _DAT_0112a0d8 = LoadLibraryW(widePluginPath);
    if (_DAT_0112a0d8 == (HMODULE)0x0) {
      _Format = "OpenAutomate Failed loading: '%s'\n";
      pcVar5 = DAT_0112a0d0;
    }
    else {
      // Get the plugin entry point function
      _DAT_0112a0c8 = GetProcAddress(_DAT_0112a0d8, "oaPluginInit");
      if (_DAT_0112a0c8 != (FARPROC)0x0) {
        return 1;  // Successfully loaded and found entry point
      }
      pcVar5 = "Plugin does not have the correct entry point.";
      _Format = "ERROR: %s\n";
      _DAT_0112a0c8 = (FARPROC)0x0;
    }
    iVar3 = FUN_00b995f7(_Format, pcVar5);  // Get FILE* for error output
    _fprintf((FILE *)(iVar3 + 0x40), _Format);  // Print error message
    return 0;
  }
  
  // Handle MultiByteToWideChar errors
  DVar4 = GetLastError();
  if (DVar4 == 0x7a) {  // ERROR_INSUFFICIENT_BUFFER
    pcVar5 = "OpenAutomate MultiByteToWideChar returned error: ERROR_INSUFFICIENT_BUFFER\n";
  }
  else if (DVar4 == 0x3ec) {  // ERROR_INVALID_FLAGS
    pcVar5 = "OpenAutomate MultiByteToWideChar returned error: ERROR_INVALID_FLAGS\n";
  }
  else if (DVar4 == 0x57) {  // ERROR_INVALID_PARAMETER
    pcVar5 = "OpenAutomate MultiByteToWideChar returned error: ERROR_INVALID_PARAMETER\n";
  }
  else {
    if (DVar4 != 0x459) goto LAB_006a1d0b;  // Skip if not ERROR_NO_UNICODE_TRANSLATION
    pcVar5 = "OpenAutomate MultiByteToWideChar returned error: ERROR_NO_UNICODE_TRANSLATION\n";
  }
  iVar3 = FUN_00b995f7();  // Get FILE* for error output
  _fprintf((FILE *)(iVar3 + 0x40), pcVar5);  // Print error message

LAB_006a1d0b:
  // Check if plugin path was defined
  pcVar5 = DAT_0112a0d0;
  do {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  
  // If path was empty string (only null terminator)
  if (pcVar5 == DAT_0112a0d0 + 1) {
    pcVar5 = "OpenAutomate PluginPath was undefined\n";
    iVar3 = FUN_00b995f7();  // Get FILE* for error output
    _fprintf((FILE *)(iVar3 + 0x40), pcVar5);  // Print error message
  }
  
  return 0;  // Failed to load plugin
}