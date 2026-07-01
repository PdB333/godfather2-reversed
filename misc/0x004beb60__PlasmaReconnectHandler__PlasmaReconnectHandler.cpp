// FUNC_NAME: PlasmaReconnectHandler::PlasmaReconnectHandler
#pragma once
#include <cstdint>

// Forward declarations of helper functions
extern uint32_t findMessageType(const char* name);
extern void setGlobalMessageType(void* global, uint32_t type);
extern void registerHandler(void* obj, void* globalType);
extern void baseConstructor();   // FUN_005666d0
extern void derivedInit();      // FUN_005668a0

// Global variables
extern uint32_t g_plasmaReconnectMessageType;    // DAT_01218050
extern uint32_t g_plasmaReconnectExtra;          // DAT_01206940

// Vtable pointers (defined in other translation units)
extern void* g_baseVtable;      // PTR_FUN_00e2f19c
extern void* g_derivedVtable;   // PTR_FUN_00e35c7c
extern void* g_extraPtr1;       // PTR_FUN_00e35c90
extern void* g_extraPtr2;       // PTR_LAB_00e35d28

class PlasmaReconnectHandler
{
public:
    // Constructor (called via __fastcall, returns this)
    PlanckReconnectHandler* __fastcall constructor(PlasmaReconnectHandler* this)
    {
        // Set initial vtable (base class)
        this->vtable = &g_baseVtable;
        this->field_4 = 1;
        this->field_8 = 0;

        // Call base class initialization
        baseConstructor();

        // Override vtable to derived class
        this->vtable = &g_derivedVtable;
        this->field_C = &g_extraPtr1;   // +0x0C
        this->field_10 = &g_extraPtr2;  // +0x10
        *(uint8_t*)((uint32_t)this + 0x4C) = 0;   // offset 76 (byte)

        // Register message type
        uint32_t msgType = findMessageType("iMsgPlasmaReconnect");
        setGlobalMessageType(&g_plasmaReconnectMessageType, msgType);
        if (g_plasmaReconnectMessageType != 0) {
            registerHandler(this, &g_plasmaReconnectMessageType);
        }
        if (g_plasmaReconnectExtra != 0) {
            registerHandler(this, &g_plasmaReconnectExtra);
        }

        // Finalize initialization
        derivedInit();

        return this;
    }

private:
    void* vtable;        // +0x00
    uint32_t field_4;    // +0x04
    uint32_t field_8;    // +0x08
    void* field_C;       // +0x0C
    void* field_10;      // +0x10
    // ... more fields up to offset 0x4C (byte)
};