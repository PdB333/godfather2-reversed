// Xbox PDB: EARS_Persist_AutoSave_Start
// FUNC_NAME: SaveManager::handleAutosaveDisabledCardRemoval
#include <cstdint>

// External singleton pointer
extern SaveManager* g_pSaveManager; // 0x01129828

// External string constant for autosave disabled card message
extern const char* g_autosaveDisabledCardMessage; // 0x0112ddf8

// Known class layout (partial)
class SaveManager {
public:
    // vtable offset +0x24 - checks if autosave disabled card is supported on this platform
    virtual bool isAutosaveDisabledCardSupported() = 0; 
    // vtable offset +0x18 - register a callback to be invoked when card is removed
    virtual void registerAutosaveDisabledCallback(void (*callback)(void*), void* context) = 0; 
    // Other members...
    uint32_t flags; // offset 0x10 (piVar1[4] in decompiled)
    // +0x14: probably other fields
};

// Forward declarations of helper functions (renamed for clarity)
extern "C" {
    void* __fastcall AllocateNotificationObject(uint32_t size); // FUN_009c8e50
    void* __fastcall InitializeNotificationObject(void* obj); // FUN_00982280, returns obj or 0
    const char* __fastcall GetLocalizedString(const char* key); // FUN_00981eb0
    void __fastcall SetNotificationActive(bool active); // FUN_00982400
    void __fastcall DispatchNotifications(); // FUN_00982e10
    void __fastcall BuildNotificationBuffer(const char* msg, int param); // FUN_00408a00, uses stack buffer
}

// Callback function pointed to by FUN_008f10c0 - handling card removal
extern void __fastcall AutosaveDisabledCardRemovedHandler(void* context); // assumed

bool __fastcall SaveManager::handleAutosaveDisabledCardRemoval(void* context) // param_1
{
    // Check if the autosave disabled card is still supported on this platform
    bool supported = g_pSaveManager->isAutosaveDisabledCardSupported();
    if (supported) {
        // Platform supports it, so register the removal callback with the given context
        g_pSaveManager->registerAutosaveDisabledCallback(&AutosaveDisabledCardRemovedHandler, context);
        // Process any pending events (probably UI updates)
        FUN_00911b00(); // likely ProcessEvents or similar
        return 1; // success: handled as supported
    }

    // Check if the autosave disabled card is currently being displayed (bit 10 of flags)
    if ((g_pSaveManager->flags >> 10) & 1) {
        // Clear the flag to indicate card is no longer displayed
        g_pSaveManager->flags &= ~(1 << 10);

        // Build a notification buffer from the card message string
        char buffer[16]; // uStack_c, uStack_8, uStack_4
        BuildNotificationBuffer(g_autosaveDisabledCardMessage, 0);

        // Allocate and initialize a new notification object (size 0xf0 = 240 bytes)
        void* notifObj = AllocateNotificationObject(0xf0);
        if (notifObj) {
            notifObj = InitializeNotificationObject(notifObj); // returns the object or 0
        }

        // Get the localized string for the "autosave disabled card removed" message
        GetLocalizedString("$autosave_disabled_card_removed");

        // Set the notification type to 0x0b (11) - likely indicates card removal
        *(uint32_t*)((uint8_t*)notifObj + 0xC) = 0xB;

        // Activate the notification system
        SetNotificationActive(1);

        // Set the callback for handling the removal event
        *(void**)((uint8_t*)notifObj + 0x14) = &AutosaveDisabledCardRemovedHandler;

        // Dispatch/process notifications
        DispatchNotifications();
    }

    return 0; // not handled as supported, but card removal might be triggered
}