// Xbox PDB: EARS_Modules_TrafficLightManager_TrafficLightManager
// FUNC_NAME: TrafficSystem::initializeTrafficSystem
// Address: 0x0083a5f0
// Class: TrafficSystem (EA EARS engine, Godfather 2 traffic light system)
// Initializes traffic light message IDs and registers broadcast handlers.

#include <Windows.h> // For DWORD

// Global singleton pointer
void* g_pTrafficSystem = nullptr; // 0x0112dbfc

// Message system functions (hypothetical)
extern DWORD MessageSystem_RegisterString(const char* name); // FUN_00408240
extern void MessageSystem_RegisterHandler(DWORD* msgId, DWORD flags); // FUN_00408900 (second param is address of DWORD, 0x8000 = rebroadcast flag?)

// Vtable pointers (from .rdata)
extern void* vtable_TrafficSystem;     // &PTR_FUN_00d74124
extern void* vtable_TrafficSystemInner; // &PTR_LAB_00d74114, initially &PTR_FUN_00e2f19c

// TrafficSystem internal structure (size unknown, at least 0x28 bytes)
class TrafficSystem {
public:
    void* vtable;            // +0x00
    void* innerVtable;       // +0x04 (points to inner object vtable)
    DWORD field_0x08;        // +0x08 (initialized to 1)
    DWORD field_0x0C;        // +0x0C (initialized to 0)
    // +0x10 through +0x24 are fields set later

    // Message IDs (global DAT_ variables, stored elsewhere)
    // These are likely static DWORDs updated by RegisterString
    static DWORD s_msgReBroadcastState;      // 0x0112dc14
    static DWORD s_msgTrafficGroup1_Green;   // 0x0112dc24
    static DWORD s_msgTrafficGroup1_Yellow;  // 0x0112dc2c
    static DWORD s_msgTrafficGroup1_Red;     // 0x0112dc0c
    static DWORD s_msgTrafficGroup2_Green;   // 0x0112dc34
    static DWORD s_msgTrafficGroup2_Yellow;  // 0x0112dc00
    static DWORD s_msgTrafficGroup2_Red;     // 0x0112dc1c
    static DWORD s_msgSomething;             // 0x012069c4 (unknown)

    // Inner class (handles registered messages?) at this+4
    class InnerTrafficHandler {
    public:
        void* vtable; // points to vtable_TrafficSystemInner
        // ...
    };

    // Actual initialization function (constructor or init)
    void __fastcall initialize()
    {
        g_pTrafficSystem = this; // Store singleton

        // Setup inner handler vtable (first set to something, then overridden)
        innerVtable = &vtable_TrafficSystemInner; // originally &PTR_FUN_00e2f19c

        field_0x08 = 1;
        field_0x0C = 0;

        vtable = &vtable_TrafficSystem; // +0x00

        // Override inner vtable (confirmed final)
        innerVtable = &vtable_TrafficSystemInner;

        // Register message strings
        s_msgReBroadcastState = MessageSystem_RegisterString("iMsgTrafficReBroadcastState");
        if (s_msgReBroadcastState != 0) {
            // Register handler for rebroadcast state with 0x8000 flag
            MessageSystem_RegisterHandler(&s_msgReBroadcastState, 0x8000);
        }

        // Register group 1 light state strings
        s_msgTrafficGroup1_Green  = MessageSystem_RegisterString("iMsgTrafficGroup1_Green");
        s_msgTrafficGroup1_Yellow = MessageSystem_RegisterString("iMsgTrafficGroup1_Yellow");
        s_msgTrafficGroup1_Red    = MessageSystem_RegisterString("iMsgTrafficGroup1_Red");

        // Register group 2 light state strings
        s_msgTrafficGroup2_Green  = MessageSystem_RegisterString("iMsgTrafficGroup2_Green");
        s_msgTrafficGroup2_Yellow = MessageSystem_RegisterString("iMsgTrafficGroup2_Yellow");
        s_msgTrafficGroup2_Red    = MessageSystem_RegisterString("iMsgTrafficGroup2_Red");

        // Possibly register another group/message?
        if (s_msgSomething != 0) {
            MessageSystem_RegisterHandler(&s_msgSomething, 0x8000);
        }

        // Set additional fields (likely state timers or mode flags)
        field_0x18 = 0;   // param_1[6] = 0
        field_0x10 = 0;   // param_1[4] = 0
        field_0x14 = 0;   // param_1[5] = 0
        field_0x24 = 1;   // param_1[9] = 1   (default mode?)
        field_0x1C = 2;   // param_1[7] = 2   (some count?)
        field_0x20 = 0;   // param_1[8] = 0
    }
};