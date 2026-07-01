// FUNC_NAME: CGameCityChangedHandler::CGameCityChangedHandler
// Constructor for a city-change event handler (0x00849910)
// This class monitors city state changes and registers a message callback.

// Forward declarations for external functions
void __fastcall MessageManager_RegisterMessage(MessageManager* mgr, const char* msgName);
void __fastcall EventManager_RegisterListener(uint32_t eventHash, void* listener, int unk);

// Global pointer stored during construction
extern MessageManager* g_pMessageManager; // DAT_0112dcf4
extern CGameCityChangedHandler* g_pCityChangedHandler; // DAT_0112a66c

class CGameCityChangedHandler {
public:
    // VTable pointers (multiple inheritance, two interfaces)
    void* m_vtable0;  // +0x00 : first vtable (e.g., IMessageTarget)
    void* m_vtable1;  // +0x04 : second vtable (e.g., IEventSubscriber)
    int m_field2;     // +0x08 : unknown, zeroed
    int m_field3;     // +0x0C : unknown, zeroed
    int m_field4;     // +0x10 : unknown, zeroed
    int m_field5;     // +0x14 : unknown, zeroed
    int m_field6;     // +0x18 : unknown, zeroed

    // Constructor (__fastcall, this in ECX)
    __fastcall CGameCityChangedHandler() {
        g_pCityChangedHandler = this;

        // Set vtable pointers (order as per initialization)
        m_vtable0 = &__vtable_CGameCityChangedHandler_0; // 0x00d74d10 (virtual function table)
        m_vtable1 = &__vtable_CGameCityChangedHandler_1; // 0x00d74d00 (second interface vtable)

        // Clear remaining fields
        m_field2 = 0;
        m_field3 = 0;
        m_field4 = 0;
        m_field5 = 0;
        m_field6 = 0;

        // Register the "iMsgCityChanged" message with the global message manager
        MessageManager_RegisterMessage(g_pMessageManager, "iMsgCityChanged");

        // Register this object as a listener for event hash 0x874f7077 (probably "CityChanged")
        // The listener is the second vtable pointer (first field of the second base subobject)
        EventManager_RegisterListener(0x874f7077, &m_vtable1, 1);
    }
};