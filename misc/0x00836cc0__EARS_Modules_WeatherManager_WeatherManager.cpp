// Xbox PDB: EARS_Modules_WeatherManager_WeatherManager
// FUNC_NAME: WeatherManager::WeatherManager
// Address: 0x00836cc0
// Role: Constructor for WeatherManager, initializes rain message handling and listener registration

typedef void* (*BaseConstructorFunc)(void* param);
typedef void (*RegisterMessageFunc)(void* buffer, const char* message);
typedef void (*AddListenerFunc)(void* listener, void* eventSource, int flags);

// Global instance pointer
extern WeatherManager* gWeatherManager;

int* __thiscall WeatherManager::WeatherManager(int* this, int param2)
{
    int* puVar1;
    int uVar2;

    // Set vtable for base class (likely MultiBase or SimManager)
    *this = &g_vtable_WeatherManager_base1; // PTR_LAB_00d73c38
    gWeatherManager = this;

    // Call base constructor
    ((BaseConstructorFunc)0x0046c590)(param2);

    // Set secondary vtable (for derived class)
    this[1] = &g_vtable_WeatherManager_base2; // PTR_LAB_00d73c54
    // Override primary vtable to derived class's vtable
    *this = &g_vtable_WeatherManager_derived; // PTR_FUN_00d73c50

    // Set vtable pointers for embedded Observer/Listener objects
    this[0x10] = &g_vtable_WeatherManager_listener1; // PTR_LAB_00d73c40
    this[0x13] = &g_vtable_WeatherManager_listener2; // PTR_LAB_00d73c3c

    // Initialize rain fade state array (6 entries of 8 bytes each)
    // Each entry: int32_t field0, int16_t field4, int16_t field6
    this[0x15] = 0;    // +0x54
    *(short*)(this + 0x16) = 0; // +0x58
    *(short*)((int)this + 0x5a) = 0; // +0x5a

    this[0x17] = 0;    // +0x5c
    *(short*)(this + 0x18) = 0; // +0x60
    *(short*)((int)this + 0x62) = 0; // +0x62

    this[0x19] = 0;    // +0x64
    *(short*)(this + 0x1a) = 0; // +0x68
    *(short*)((int)this + 0x6a) = 0; // +0x6a

    this[0x1b] = 0;    // +0x6c
    *(short*)(this + 0x1c) = 0; // +0x70
    *(short*)((int)this + 0x72) = 0; // +0x72

    this[0x1d] = 0;    // +0x74
    *(short*)(this + 0x1e) = 0; // +0x78
    *(short*)((int)this + 0x7a) = 0; // +0x7a

    this[0x1f] = 0;    // +0x7c
    *(short*)(this + 0x20) = 0; // +0x80
    *(short*)((int)this + 0x82) = 0; // +0x82

    // Additional fields after the array
    *(short*)(this + 0x21) = 0; // +0x84, 2-byte field (e.g., mRainFadeState)
    uVar2 = _DAT_00d5780c; // Some global constant (maybe initial rain intensity or time)
    this[0x22] = uVar2;    // +0x88, 4-byte field (e.g., mRainTimer)

    // Zero out remaining fields (up to offset 0xDC)
    this[0x26] = 0; // +0x98
    this[0x27] = 0; // +0x9c
    this[0x28] = 0; // +0xa0
    this[0x2b] = 0; // +0xac
    this[0x2c] = 0; // +0xb0
    this[0x2d] = 0; // +0xb4
    this[0x2e] = 0; // +0xb8
    this[0x2f] = 0; // +0xbc
    this[0x30] = 0; // +0xc0
    this[0x31] = 0; // +0xc4
    this[0x32] = 0; // +0xc8
    this[0x33] = 0; // +0xcc
    this[0x34] = 0; // +0xd0
    this[0x35] = 0; // +0xd4
    this[0x36] = 0; // +0xd8
    this[0x37] = 0; // +0xdc

    // Register rain fade message strings
    ((RegisterMessageFunc)0x00408240)(&g_MessageBuffer1, "iMsgStartRainFadeIn");
    ((RegisterMessageFunc)0x00408240)(&g_MessageBuffer2, "iMsgStartRainFadeOut");
    ((RegisterMessageFunc)0x00408240)(&g_MessageBuffer3, "iMsgStartRainFadeInTOD");
    ((RegisterMessageFunc)0x00408240)(&g_MessageBuffer4, "iMsgStartRainFadeOutTOD");

    // Zero more fields (likely message-related counters or flags)
    this[0x25] = 0; // +0x94
    this[0x24] = 0; // +0x90
    this[0x23] = 0; // +0x8c

    // Register as listener for rain events if the event sources exist
    puVar1 = this + 0x10; // Pointer to the listener object
    if (g_RainEventSource1 != 0) {
        ((AddListenerFunc)0x00408900)(puVar1, &g_RainEventSource1, 0x8000);
    }
    if (g_RainEventSource2 != 0) {
        ((AddListenerFunc)0x00408900)(puVar1, &g_RainEventSource2, 0x8000);
    }
    if (g_RainEventSource3 != 0) {
        ((AddListenerFunc)0x00408900)(puVar1, &g_RainEventSource3, 0x8000);
    }

    return this;
}