// Xbox PDB: EARS_Modules_ViolenceTracking_RegisterEventListeners
// FUNC_NAME: ViolenceTracking::releaseViolenceMessages

// Function at 0x008d7040: Releases violence-related messages (including "iMsgViolenceComputed") via a message manager.
// Called during cleanup/shutdown (caller at 0x008d7aa0).

// Global message pointers (likely set by other initialization functions)
extern void* g_pMsgViolenceUnknown;          // DAT_012069d4
extern void* g_pMsgViolenceComputed;         // DAT_0112f9dc
extern void* g_pMsgViolenceOther;            // DAT_0112b36c

// External functions from message system
// Retrieves a message pointer by name and stores it in the given location.
extern void getMessagePtr(void** outPtr, const char* messageName);
// Releases/destroys a message. Third parameter is a flag (e.g., MSG_RELEASE = 0x8000).
extern void releaseMessage(void* thisPtr, void** msgPtr, int flags);

// Constant for message release operation
const int MSG_RELEASE = 0x8000;

void __thiscall ViolenceTracking::releaseViolenceMessages()
{
    // Release the first message if it exists
    if (g_pMsgViolenceUnknown != 0) {
        releaseMessage(this, &g_pMsgViolenceUnknown, MSG_RELEASE);
    }

    // Look up the "iMsgViolenceComputed" message and release it if present
    getMessagePtr(&g_pMsgViolenceComputed, "iMsgViolenceComputed");
    if (g_pMsgViolenceComputed != 0) {
        releaseMessage(this, &g_pMsgViolenceComputed, MSG_RELEASE);
    }

    // Release the third message if it exists
    if (g_pMsgViolenceOther != 0) {
        releaseMessage(this, &g_pMsgViolenceOther, MSG_RELEASE);
    }
}