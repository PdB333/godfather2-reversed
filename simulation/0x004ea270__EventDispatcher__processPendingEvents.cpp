// FUNC_NAME: EventDispatcher::processPendingEvents
// Function address: 0x004ea270
// This function processes a list of pending network events or ghost updates.
// It uses thread-local storage to access current thread context and global pointers
// to determine the event dispatch list.

#include <cstdint>

// Global variables (inferred from decompilation)
extern int32_t* g_pServerConnection;     // DAT_0122339c - pointer to server connection object
extern int32_t  g_bNetworkActive;        // DAT_012233a0 - flag indicating network is active
extern int32_t* g_pEventDispatcherPrimary;   // DAT_01206880 - primary event dispatcher
extern int32_t* g_pEventDispatcherSecondary; // DAT_012068e8 - secondary event dispatcher (used on some condition)
extern int32_t* g_pFinalBroadcastPrimary;    // DAT_012054ec - final broadcast target 1
extern int32_t* g_pFinalBroadcastSecondary;  // DAT_012054f0 - final broadcast target 2
extern int32_t* g_pEventDispatchTable;       // PTR_LAB_01124bd0 - static dispatch table

// Forward declarations for called functions
void __thiscall EventDispatcher::init(EventDispatcher* this); // FUN_004ea080
void __thiscall EventDispatcher::notify(EventDispatcher* this, int32_t receiver, int32_t eventType,
                                          int32_t param, int32_t unk1, int32_t unk2, int32_t flags); // FUN_004ea560

void __thiscall EventDispatcher::processPendingEvents(EventDispatcher* this)
{
    int32_t serverConn = g_pServerConnection;
    int32_t netActive = g_bNetworkActive;

    // Call init on this dispatcher
    init(this);

    if ((serverConn == 0) || (netActive == 0)) {
        // No network connection active: process using thread-local storage for current context
        // FS:0x2C typically holds a pointer to the thread's GameContext/SimManager
        int32_t* threadContext = *(int32_t**)(__readfsdword(0x2C) + 0x2C); // unaff_FS_OFFSET + 0x2C -> actually 0x2C from FS base?
        // The original: "**(int **)(unaff_FS_OFFSET + 0x2c)" - read a pointer at TLS offset 0x2C
        int32_t* contextObject = *reinterpret_cast<int32_t**>(__readfsdword(0x2C) + 0x2C);
        int32_t* localReceiver = reinterpret_cast<int32_t*>(contextObject[0x24 / 4]); // offset 0x24 from context

        if (localReceiver != nullptr) {
            // Broadcast to a single receiver with all parameters
            notify(this, reinterpret_cast<int32_t>(localReceiver), 0, 0xFFFFFFFF, 0, 0, 2);
            int32_t* dispatcher = g_pEventDispatcherPrimary;
            // Check if there is a secondary context (some flag)
            int32_t* extraContext = reinterpret_cast<int32_t*>(contextObject[0x34 / 4]);
            if (extraContext != nullptr) {
                dispatcher = g_pEventDispatcherSecondary;
            }
            // Write the dispatch table pointer and the receiver into the dispatcher's array
            *reinterpret_cast<int32_t**>(dispatcher[0x14 / 4]) = &g_pEventDispatchTable;
            dispatcher[0x14 / 4] += 4;
            *reinterpret_cast<int32_t**>(dispatcher[0x14 / 4]) = reinterpret_cast<int32_t>(localReceiver);
            dispatcher[0x14 / 4] += 4;
        }
    }
    else {
        // Network active: iterate through a list of pending events from the connection object
        int32_t* connectionObj = reinterpret_cast<int32_t*>(serverConn);
        int32_t eventCount = connectionObj[0x154 / 4]; // offset 0x154 from connection object
        if (eventCount > 0) {
            int32_t* eventArray = reinterpret_cast<int32_t*>(connectionObj + 0x158 / 4); // offset 0x158
            for (int32_t i = 0; i < eventCount; ++i) {
                int32_t receiver;
                if (connectionObj[0x154 / 4] == 0) { // re-read maybe internal flag? Actually checking serverConn???
                    // Use thread context object
                    int32_t* threadCtx = *reinterpret_cast<int32_t**>(__readfsdword(0x2C) + 0x2C);
                    receiver = threadCtx[0x24 / 4];
                } else {
                    receiver = eventArray[-0x51]; // negative offset from eventArray? Something like eventArray[-81]???
                }
                if ((receiver != 0) && (eventArray[i] != -1)) {
                    notify(this, receiver, 1, eventArray[i], 0, 0, 2);
                }
            }
        }

        // Final broadcast to a global target
        int32_t* threadCtx2 = *reinterpret_cast<int32_t**>(__readfsdword(0x2C) + 0x2C);
        int32_t secondaryFlag = threadCtx2[0x34 / 4]; // offset 0x34 from context
        int32_t* finalTarget;
        if (secondaryFlag != 1) {
            finalTarget = g_pFinalBroadcastSecondary;
        } else {
            finalTarget = g_pFinalBroadcastPrimary;
        }
        if (finalTarget != nullptr) {
            int32_t eventParam = connectionObj[0x158 / 4]; // last event ID?
            if (secondaryFlag != 1) {
                finalTarget = g_pFinalBroadcastSecondary; // re-select???
            } else {
                finalTarget = g_pFinalBroadcastPrimary;
            }
            notify(this, reinterpret_cast<int32_t>(finalTarget), 0, eventParam, 0, 0, 2);
        }
    }
}