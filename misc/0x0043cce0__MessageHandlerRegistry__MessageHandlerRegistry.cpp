// FUNC_NAME: MessageHandlerRegistry::MessageHandlerRegistry

#include <cstdint>

// Forward declarations (based on global variables)
extern void* g_pRegistryInstance; // DAT_01223418
extern uint32_t* g_pManager; // DAT_01223410 (pointer to a manager struct)
extern uint32_t* g_pHandlerMap; // DAT_0122341c (pointer to a dynamic map structure)
extern uint32_t g_StoreEntityMsgId; // DAT_0120e924
extern uint32_t g_RestoreEntityMsgId; // DAT_0120e91c
extern uint32_t g_TempFlag; // DAT_0110ab98

// System functions
extern void* Alloc(uint32_t size); // FUN_009c8e80 (likely operator new)
extern uint32_t StringToMsgId(const char* str); // FUN_004dafd0 (hash string to message ID)
extern void RegisterMsgHandler(uint32_t msgId, void* handler); // FUN_00408260
extern void GrowHandlerMap(uint32_t newCapacity); // FUN_00463b90 (resize the global map)

struct HandlerPair {
    uint32_t msgId;
    void* handlerObject; // some object with a virtual function table
};

struct MapEntry {
    uint32_t msgId;
    MessageHandlerRegistry* registry;
    void* handlerObject;
};

// The default handler class used for initialization
class DefaultHandler {
public:
    virtual void OnInitialize() = 0; // assumed virtual function at offset +8
};

class MessageHandlerRegistry {
public:
    // Vtable pointers (multiple inheritance)
    void* vtable1;      // +0x00
    void* vtable2;      // +0x04
    void* vtable3;      // +0x08
    DefaultHandler* m_pDefaultHandler;  // +0x0C
    void* m_pEntryData;                 // +0x10 (allocated array of unknown struct size 0x1c)
    uint32_t m_nEntryCount;             // +0x14 (initially 0)
    uint32_t m_nMaxCount;               // +0x18 (parameter count)
    uint32_t m_nFlags;                  // +0x1C (parameter flags)
    HandlerPair* m_pHandlerTable;       // +0x20 (pointer to an array of (msgId, handler) pairs)
    bool m_bInitialized;                // +0x24 (set to true by constructor)

    MessageHandlerRegistry(int count, DefaultHandler* pDefaultHandler, uint32_t flags, HandlerPair* pTable);
};

MessageHandlerRegistry::MessageHandlerRegistry(int count, DefaultHandler* pDefaultHandler, uint32_t flags, HandlerPair* pTable) {
    // Set vtable pointers (specific addresses from the binary)
    this->vtable1 = &VTable1_Base;   // PTR_FUN_00e30ff0
    this->vtable2 = &VTable2_Base;   // PTR_LAB_00e31000
    this->vtable3 = &VTable3_Base;   // PTR_LAB_00e31004

    this->m_pDefaultHandler = pDefaultHandler;
    this->m_pEntryData = Alloc(count * 0x1c); // allocate array of 28-byte entries
    this->m_nEntryCount = 0;
    this->m_nMaxCount = count;
    this->m_nFlags = flags;
    this->m_pHandlerTable = pTable;
    this->m_bInitialized = true;

    // Register this instance globally (singleton)
    g_pRegistryInstance = this;

    // Insert this registry into a global manager list if the manager has space (less than 2 entries)
    uint32_t* pManagerCount = reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(g_pManager) + 0x20);
    if (*pManagerCount < 2) {
        void** pList = reinterpret_cast<void**>(reinterpret_cast<char*>(g_pManager) + 0x18);
        pList[*pManagerCount] = &this->vtable1; // actually stores pointer to offset 4? The code stores param_1+1
        (*pManagerCount)++;
    }

    // Register standard message handlers
    uint32_t storeMsgId = StringToMsgId("iMsgStoreEntity");
    RegisterMsgHandler(g_StoreEntityMsgId, storeMsgId); // note: second param is likely a hash, but original stores ID
    uint32_t restoreMsgId = StringToMsgId("iMsgRestoreEntity");
    RegisterMsgHandler(g_RestoreEntityMsgId, restoreMsgId);

    // Process the handler table (array of (msgId, handlerObject) pairs)
    HandlerPair* pCurrent = this->m_pHandlerTable;
    while (true) {
        if (pCurrent->msgId == 0) {
            // End of table (null terminator)
            // Update the global temp flag with the handler object of the first zero message?
            g_TempFlag = 0;
            HandlerPair* pScan = this->m_pHandlerTable;
            do {
                if (pScan->msgId == 0) {
                    g_TempFlag = reinterpret_cast<uint32_t>(pScan->handlerObject);
                }
                pScan++;
            } while (g_TempFlag == 0);
            return;
        }

        uint32_t currentMsgId = pCurrent->msgId;
        uint32_t currentHandler = reinterpret_cast<uint32_t>(pCurrent->handlerObject);
        bool foundExisting = false;

        uint32_t mapSize = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(g_pHandlerMap) + 0x10); // offset +0x10: current count
        uint32_t mapCapacity = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(g_pHandlerMap) + 0x14); // offset +0x14: capacity
        uint32_t* mapArray = *reinterpret_cast<uint32_t**>(reinterpret_cast<char*>(g_pHandlerMap) + 0x0c); // offset +0x0c: pointer to array of MapEntry

        // Linear scan the map to see if currentMsgId already exists
        for (uint32_t i = 0; i < mapSize; i++) {
            MapEntry* entry = reinterpret_cast<MapEntry*>(reinterpret_cast<char*>(mapArray) + i * sizeof(MapEntry));
            if (entry->msgId == currentMsgId) {
                foundExisting = true;
                // If found, the code updates map entry's registry pointer? It sets piVar4[1] = (int)this
                entry->registry = this;
                break;
            }
        }

        // If not found and the map is not full, insert a new entry
        if (!foundExisting) {
            if (mapSize >= mapCapacity) {
                // Need to grow the map
                uint32_t newCapacity;
                if (mapCapacity == 0) {
                    newCapacity = 1;
                } else {
                    newCapacity = mapCapacity * 2;
                }
                GrowHandlerMap(newCapacity);
                // Refresh pointers after resize
                mapArray = *reinterpret_cast<uint32_t**>(reinterpret_cast<char*>(g_pHandlerMap) + 0x0c);
            }

            // Insert new entry at the end
            uint32_t index = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(g_pHandlerMap) + 0x10);
            MapEntry* newEntry = reinterpret_cast<MapEntry*>(reinterpret_cast<char*>(mapArray) + index * sizeof(MapEntry));
            newEntry->msgId = currentMsgId;
            newEntry->registry = this;
            newEntry->handlerObject = reinterpret_cast<void*>(currentHandler);
            // Increment count
            *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(g_pHandlerMap) + 0x10) = index + 1;
        }

        // Move to next pair (each pair is 8 bytes: two uint32_t)
        pCurrent++;
    }
}