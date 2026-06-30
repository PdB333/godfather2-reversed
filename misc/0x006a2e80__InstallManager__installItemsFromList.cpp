// FUNC_NAME: InstallManager::installItemsFromList
// Function address: 0x006a2e80
// Role: Writes an XML manifest for a list of install items, then calls a virtual method to register the installation.
// The list is a circular linked list with a dummy head node (param_2).
// Returns 0 on success (if output buffer is set to 3), 3 on failure, 5 if list is empty.

#include <windows.h> // For LPWSTR, DWORD, GetCurrentProcessId, GetCommandLineW

// Forward declarations of unknown helper functions
bool isInstallationPossible();          // 0x006a2950
uint checkInstallationStatus();         // 0x006a2b50

// Represents a node in the install item linked list
struct InstallItemNode {
    InstallItemNode* pNext;             // +0x00: next node
    wchar_t* pContentId;                // +0x08: wide string of content ID
};

class InstallManager {
public:
    // vtable offsets used:
    // +0x9c: virtual bool canInstall()
    // +0xa4: virtual bool writeInstallManifest(const wchar_t* keyPath, const wchar_t* xmlData, DWORD* pResult, DWORD processId, const wchar_t* commandLine)

    uint __thiscall installItemsFromList(InstallItemNode* nodeList, char bIncludeCommandLine)
    {
        int count = 0;
        InstallItemNode* pCur = nodeList->pNext;

        // Count nodes (excluding dummy head)
        while (pCur != nodeList) {
            pCur = pCur->pNext;
            count++;
        }

        if (count == 0) {
            return 5;   // No items to install
        }

        // Check if installation is possible (e.g., system requirements)
        if (!isInstallationPossible()) {
            return 1;
        }

        // Virtual: can we install now?
        bool canInstall = (this->*((bool(__thiscall*)(InstallManager*)) (*(uint*)(this + 0x9c))))();
        if (!canInstall) {
            uint status = checkInstallationStatus();
            if (status != 0) {
                return status;   // Return failure from helper
            }
        }

        // Build XML string representing the install items
        wchar_t xmlBuffer[512]; // awStack_400
        _wcsncpy_s(xmlBuffer, 0x200, L"<InstallItems>", 0x200);

        pCur = nodeList->pNext;
        while (pCur != nodeList) {
            _wcsncat_s(xmlBuffer, 0x200, L"<InstallItem ContentId=\"", 0x200);
            _wcsncat_s(xmlBuffer, 0x200, pCur->pContentId, 0x200);
            _wcsncat_s(xmlBuffer, 0x200, L"\"/>", 0x200);
            pCur = pCur->pNext;
        }

        errno_t concatResult = _wcsncat_s(xmlBuffer, 0x200, L"</InstallItems>", 0x200);
        if (concatResult != 0) {
            return 3;   // Buffer overflow
        }

        // Determine command line to pass (if bIncludeCommandLine is true)
        const wchar_t* cmdLine = (bIncludeCommandLine != 0) ? GetCommandLineW() : L"";
        DWORD processId = GetCurrentProcessId();

        DWORD resultBuffer;     // auStack_404
        // Call virtual method to actually write the manifest (to registry or file)
        bool success = (this->*((bool(__thiscall*)(InstallManager*, const wchar_t*, const wchar_t*, DWORD*, DWORD, const wchar_t*)) (*(uint*)(this + 0xa4))))(
            L"Software\\Electronic Arts\\The Godfather 2\\InstallManifest", // DAT_00d5d584 (likely registry key)
            xmlBuffer,
            &resultBuffer,
            processId,
            cmdLine
        );

        if (success) {
            // Return 0 if resultBuffer == 3, otherwise 3
            return (resultBuffer == 3) ? 0 : 3;
        }

        return 3;   // Write operation failed
    }
};