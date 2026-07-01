// Xbox PDB: EARS_Modules_CrimeManager_CrimeManager
// FUNC_NAME: CrimeManager::CrimeManager
// Address: 0x007869d0
// Role: Constructor for CrimeManager - initializes message subscriptions and internal arrays

#include <windows.h> // For DWORD, etc.

// Forward declarations for functions called (assumed from EA EARS engine)
void __cdecl registerMessage(const char* name, DWORD* handle);
void __cdecl subscribeToMessage(DWORD* handle, DWORD flags); // flags like 0x8000
void __cdecl initArray(void* base, int elementCount, int elementSize, int unknown); 
void __cdecl someInit(int val);
void __cdecl initSubObject(void* obj);

class CrimeManager {
public:
    CrimeManager();
    virtual ~CrimeManager(); // assumed

private:
    // Vtable pointers (multiple inheritance)
    DWORD* m_vtable1; // +0x00
    DWORD* m_vtable2; // +0x04
    DWORD m_field08; // +0x08
    DWORD m_field0C; // +0x0C
    DWORD* m_vtable3; // +0x10 (varies)

    // Large buffer for crime scenes or messages (size 0x1900 = 6400 bytes)
    char m_crimeSceneBuffer[0x1900]; // +0x14 (param_1+5)

    DWORD m_field1938; // +0x1938 (offset 0x64e*4)
    DWORD m_field1A3C; // +0x1A3C (offset 0x68f*4)

    // Second large buffer (size 0x1200 = 4608 bytes)
    char m_messageBuffer[0x1200]; // +0x1A40 (param_1+0x690)

    DWORD m_field2C40; // +0x2C40 (offset 0xb10*4)
    DWORD m_field2C44; // +0x2C44
    DWORD m_field2C48; // +0x2C48
    DWORD m_field2C4C; // +0x2C4C
    DWORD m_field2C50; // +0x2C50 (maybe padding)
    // ... up to 0x2C88

    // Message handles
    DWORD m_msgHandleBribeCops; // stored in global DAT_0112af78
    DWORD m_msgHandleDisableCrime;
    DWORD m_msgHandleEnableCrime;
    DWORD m_msgHandlePlayerEnteredSafehouse;

    // Sub-object at offset 0xb1a*4 = 0x2C68
    // We'll treat it as an embedded object
    char m_subObject[0x20]; // size guessed from zeroing up to b22

    // Global pointers
    static DWORD* g_thisInstance; // DAT_0112aa1c
};

DWORD* CrimeManager::g_thisInstance = nullptr;

CrimeManager::CrimeManager() {
    // store 'this' globally
    g_thisInstance = this;

    // Set up multiple vtable pointers
    m_vtable2 = reinterpret_cast<DWORD*>(&PTR_FUN_00e2f19c); // initial vtable
    m_field08 = 1;
    m_field0C = 0;
    m_vtable3 = reinterpret_cast<DWORD*>(&PTR_LAB_00d5e71c);
    m_vtable1 = reinterpret_cast<DWORD*>(&PTR_FUN_00d69864);
    m_vtable2 = reinterpret_cast<DWORD*>(&PTR_LAB_00d69854); // override
    m_vtable3 = reinterpret_cast<DWORD*>(&PTR_LAB_00d69838); // override

    // Set vtable for later region (offset 0x645*4 = 0x1914)
    *(reinterpret_cast<DWORD*>(this) + 0x645) = reinterpret_cast<DWORD>(&PTR_LAB_00e30fc0);

    // Initialize first array (crime scenes or similar)
    // param_1+5 (m_crimeSceneBuffer), size 0x1900, element size 100, count 4? Actually 4 is unknown param
    initArray(&m_crimeSceneBuffer, 0x1900, 100, 4);

    // Set flag at offset 0x64e*4
    m_field1938 = 1;

    // Call some initialization function with 0
    someInit(0);

    // Zero field at 0x68f*4
    m_field1A3C = 0;

    // Set vtable for region at 0xb10*4 = 0x2C40
    m_field2C40 = reinterpret_cast<DWORD>(&PTR_LAB_00e30fc0);

    // Initialize second array (message buffers?)
    initArray(&m_messageBuffer, 0x1200, 0x24, 4);

    // Set flag at 0xb19*4 = 0x2C64
    *(reinterpret_cast<DWORD*>(this) + 0xb19) = 1;

    // Set vtable for sub-object at 0xb1a*4
    *(reinterpret_cast<DWORD*>(this) + 0xb1a) = reinterpret_cast<DWORD>(&PTR_LAB_00d69808);

    // Zero out fields from b1b to b22
    for (int i = 0xb1b; i <= 0xb22; ++i) {
        *(reinterpret_cast<DWORD*>(this) + i) = 0;
    }

    // Subscribe to messages if the global handles are already registered
    if (DAT_0112dcf4 != 0) {
        subscribeToMessage(reinterpret_cast<DWORD*>(&DAT_0112dcf4), 0x8000);
    }

    // Register and subscribe to "iMsgBribeCops"
    registerMessage("iMsgBribeCops", &DAT_0112af78);
    if (DAT_0112af78 != 0) {
        subscribeToMessage(reinterpret_cast<DWORD*>(&DAT_0112af78), 0x8000);
    }

    // Register and subscribe to "iMsgDisableCrimeManager"
    registerMessage("iMsgDisableCrimeManager", &DAT_0112af80);
    if (DAT_0112af80 != 0) {
        subscribeToMessage(reinterpret_cast<DWORD*>(&DAT_0112af80), 0x8000);
    }

    // Register and subscribe to "iMsgEnableCrimeManager"
    registerMessage("iMsgEnableCrimeManager", &DAT_0112af88);
    if (DAT_0112af88 != 0) {
        subscribeToMessage(reinterpret_cast<DWORD*>(&DAT_0112af88), 0x8000);
    }

    // Initialize sub-object at offset b1a
    initSubObject(reinterpret_cast<void*>(this) + 0x2C68);

    // Register and subscribe to "iMsgPlayerHasEnteredSafehouse"
    registerMessage("iMsgPlayerHasEnteredSafehouse", &DAT_0112fc60);
    if (DAT_0112fc60 != 0) {
        subscribeToMessage(reinterpret_cast<DWORD*>(&DAT_0112fc60), 0x8000);
    }
}