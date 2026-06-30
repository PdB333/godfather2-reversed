// FUNC_NAME: SimManager::updateActions
// Address: 0x005f1d60
// Role: Iterates the global list of pending action events and processes them based on state (1=pending, 2=executing, 4=completed, 5=cancelled).

struct ActionEvent {
    int field_0;                        // +0x00 (unused)
    ActionEvent* pNext;                 // +0x04
    void* pObject;                      // +0x08
    int state;                          // +0x68 (enum: 1=pending, 2=executing, 4=done, 5=cancelled)
    unsigned short flags;               // +0x6c (bit 1 = 0x2)
    int completionParam;                // +0x5c (parameter passed to result callback)
    char completionFlag;                // +0x64 (100 decimal) (boolean?)
};

extern ActionEvent* g_pActionListHead;  // DAT_011a0ef0

// Forward declarations of helper functions (these are also members of SimManager or static)
void executeAction(SimManager* pThis);      // FUN_005f2280
void processAction(ActionEvent* pEvent);    // FUN_005f3080
void destroyAction(ActionEvent* pEvent);    // FUN_005f1ef0
void onActionResult(char flag, int param);  // FUN_005dbc10

void SimManager::updateActions(SimManager* pThis)
{
    ActionEvent* pEvent = g_pActionListHead;
    while (pEvent != 0) {
        if (pEvent->pObject != 0) {
            int state = pEvent->state;
            if (state == 2 || state == 4) {
                // Executing or completed – run the action and finish processing
                executeAction(pThis);
                processAction(pEvent);
            }
            else if (state == 5) {
                // Cancelled – remove the action
                destroyAction(pEvent);
            }
            else if (state == 1) {
                // Pending – if not already started, set started flag
                if ((pEvent->flags & 2) == 0) {
                    pEvent->flags |= 2;
                } else {
                    // Already started – complete and remove
                    onActionResult(pEvent->completionFlag, pEvent->completionParam);
                    destroyAction(pEvent);
                }
            }
        }
        pEvent = pEvent->pNext;
    }
}