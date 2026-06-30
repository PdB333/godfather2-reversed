// FUNC_NAME: InstallManager::sendInstallReport
// Address: 0x006a2e80
// Role: Sends an XML manifest of installed content IDs to a remote server.
//   Iterates a linked list of content IDs (sentinel at param_2), builds
//   <InstallItems> XML, then POSTs it via virtual function at vtable+0xa4.
//   Returns error codes: 5=no items, 1=not allowed, 3=send failed, 0=success.

typedef bool (__thiscall *IsInstallAllowedFn)(void* self);           // vtable+0x9c
typedef bool (__thiscall *SendPostFn)(void* self, LPCWSTR url, LPCWSTR xmlPostData, void* outStatus, DWORD processId, LPCWSTR cmdLine); // vtable+0xa4

class InstallManager {
public:
    // Returns error code (0=success, 1=skipped, 3=failed, 5=empty list)
    unsigned int __thiscall sendInstallReport(int* itemListSentinel, char includeCmdLine);
};

unsigned int __thiscall InstallManager::sendInstallReport(int* itemListSentinel, char includeCmdLine)
{
    char canProceed;
    int* currentNode;
    unsigned int result;
    errno_t ncatResult;
    LPWSTR cmdLine;
    DWORD processId;
    int count;
    char statusBuffer[4];        // +0x00: returned status (0 or 3?)
    wchar_t xmlBuffer[512];      // buffer for the XML string

    currentNode = (int*)*itemListSentinel;
    count = 0;
    if (currentNode != itemListSentinel) {
        do {
            currentNode = (int*)*currentNode;
            count = count + 1;
        } while (currentNode != itemListSentinel);
        if (count != 0) {
            canProceed = FUN_006a2950();     // unknown check (e.g., online availability?)
            if (canProceed == '\0') {
                return 1;   // cannot proceed
            }
            canProceed = ((IsInstallAllowedFn)(*(int*)(this + 0x9c)))();   // vtable+0x9c: check if installation report is allowed
            if ((canProceed == '\0') && (result = FUN_006a2b50(), result != 0)) {
                return result;   // secondary check failed => return its error
            }
            _wcsncpy_s(xmlBuffer, 0x200, L"<InstallItems>", 0x200);
            for (currentNode = (int*)*itemListSentinel; currentNode != itemListSentinel; currentNode = (int*)*currentNode) {
                _wcsncat_s(xmlBuffer, 0x200, L"<InstallItem ContentId=\"", 0x200);
                _wcsncat_s(xmlBuffer, 0x200, (wchar_t*)(currentNode + 2), 0x200);  // +0x08: content ID string
                _wcsncat_s(xmlBuffer, 0x200, L"\"/>", 0x200);
            }
            ncatResult = _wcsncat_s(xmlBuffer, 0x200, L"</InstallItems>", 0x200);
            if (ncatResult == 0) {
                if (includeCmdLine == '\0') {
                    cmdLine = L"";
                } else {
                    cmdLine = GetCommandLineW();
                }
                processId = GetCurrentProcessId();
                canProceed = ((SendPostFn)(*(int*)(this + 0xa4)))(&DAT_00d5d584, xmlBuffer, statusBuffer, processId, cmdLine);
                if (canProceed != '\0') {
                    // statusBuffer[0] == 3 means success, otherwise failure
                    return -(unsigned int)(statusBuffer != (char*)0x3) & 3;
                }
            }
            return 3;   // XML concat or send failed
        }
    }
    return 5;   // empty list
}