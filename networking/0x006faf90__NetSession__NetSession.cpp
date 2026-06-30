// FUNC_NAME: NetSession::NetSession
#pragma once
#include <cstdint>

struct NetSessionVTable {
    void* method0;
    void* method1;
    void* method2; // offset 8
    // ...
};

struct SubObjectVTable {
    void* method0;
    void* method1;
    void* method2; // offset 8
    // ...
};

// External functions (to be linked from binary)
extern void FUN_0049c610(); // Base class constructor (EARSObject)
extern int* FUN_004dddd0(); // Sub-object allocator
extern uint32_t FUN_004265d0(void* localStruct, int* subObj); // Initialize sub-object, returns handle
extern void FUN_006faf00(); // Additional initialization
extern void FUN_0049c6e0(const char* name, int flag); // Register singleton

class NetSession {
public:
    // Member fields (offsets relative to this)
    // +0x00: vtable pointer (NetSessionVTable*)
    // +0x04: ???
    // +0x08: second vtable pointer (sometimes for secondary base)
    // +0x0C: m_pConfig (void*)
    // +0x10: m_field4 (uint32_t)
    // +0x14: m_field5 (uint32_t)
    // +0x18: m_field6 (uint32_t)
    // +0x1C: m_subObjectHandle (uint32_t)
    // +0x20: m_pSubObject (int*)

    static NetSession* s_instance; // DAT_0112996c

    NetSession(void* param2) {
        FUN_0049c610(); // Base class constructor

        // Set vtable pointers
        this->vtable = (NetSessionVTable*)&PTR_FUN_00d60a4c; // Actually *this
        this->secondVtable = (void*)&PTR_LAB_00d60a48;
        // Note: param_1[2] initially set to &PTR_LAB_00d60a40, then later to &PTR_LAB_00d60a48
        // This might be due to multiple inheritance; simplified as above

        s_instance = this;

        // Store configuration pointer
        m_pConfig = param2;

        // Initialize sub-object
        uint32_t local_c = 0;
        uint32_t local_8 = 0;
        uint32_t local_4 = 0;
        int* subObj = FUN_004dddd0();
        m_subObjectHandle = FUN_004265d0(&local_c, subObj);
        m_pSubObject = subObj;

        // Call virtual method at offset 8 on sub-object (likely Initialize)
        ((SubObjectVTable*)*(uint32_t*)subObj)->method2();

        // Zero out fields 4-6
        m_field4 = 0;
        m_field5 = 0;
        m_field6 = 0;

        // Call virtual method at offset 8 on configuration object (param2)
        ((void* (*)(void*))((void*)**(uint32_t**)m_pConfig))[2])(m_pConfig); // method at vtable+8

        // Additional initialization
        FUN_006faf00();

        // Register this session with a string identifier
        FUN_0049c6e0((const char*)(&DAT_00d60a44), 1);
    }

private:
    NetSessionVTable* vtable; // +0x00
    uint32_t m_unknown1;      // +0x04
    void* secondVtable;       // +0x08
    void* m_pConfig;          // +0x0C
    uint32_t m_field4;        // +0x10
    uint32_t m_field5;        // +0x14
    uint32_t m_field6;        // +0x18
    uint32_t m_subObjectHandle; // +0x1C
    int* m_pSubObject;        // +0x20
};

NetSession* NetSession::s_instance = nullptr; // DAT_0112996c

// External symbols (addresses from binary)
extern uint32_t PTR_FUN_00d60a4c;
extern uint32_t PTR_LAB_00d60a48;
extern uint32_t PTR_LAB_00d60a40;
extern uint32_t DAT_00d60a44;