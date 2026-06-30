// FUNC_NAME: TriggerVolume::checkActivation
#include <cstdint>

// Assuming Vector3 is defined as a simple struct
struct Vector3 {
    float x, y, z;
};

// Forward declarations of external functions
extern float getSquaredDistance(Vector3* out); // 0x004702b0
extern void* getEventSystem(); // 0x00716430
extern int fireEvent(void* buffer, Vector3* pos, uint32_t eventId, uint32_t eventParam, int zero1, int zero2); // 0x00542650
extern int processAction(void* actionBuffer, void* actionData); // 0x009e5ed0

// External globals
extern uint32_t g_globalEventContext; // _DAT_00d5780c
extern void* g_actionTable; // PTR_FUN_00e32a8c

bool __fastcall TriggerVolume::checkActivation(void* thisPtr)
{
    // +0x5c offset: pointer to a sub-structure (likely a placement/radius object)
    int subObj = *(int*)((uint8_t*)thisPtr + 0x5c);
    
    Vector3 distanceVec;
    float squaredDist = getSquaredDistance(&distanceVec); // returns squared distance between player and trigger?
    
    // +0x2670 offset: activation radius (as float)
    float radius = *(float*)((uint8_t*)subObj + 0x2670);
    if (squaredDist <= radius * radius) {
        // Player is within range
        void* eventSystem = getEventSystem();
        // Call virtual function at offset 0x3c (likely some event preparation)
        typedef void (*PrepFunc)(void* self, Vector3* vec, uint8_t* data);
        PrepFunc prep = *(PrepFunc*)(*(uint32_t*)eventSystem + 0x3c);
        uint8_t prepBuffer[12] = {0}; // local_e8
        uint8_t prepData[4] = {0};    // local_dc
        prep(eventSystem, (Vector3*)prepBuffer, prepData);
        
        // Fire a specific event
        uint8_t eventBuffer[4] = {0}; // auStack_f0
        Vector3* posRef = &distanceVec;
        fireEvent(eventBuffer, posRef, 0x40122, &0x01000001, 0, 0);
        
        // Build action data structure
        struct ActionData {
            void* table;           // ppuStack_d8
            uint32_t field_4;      // uStack_d4
            uint32_t field_8;      // uStack_b8
            uint32_t field_C;      // uStack_b4
            uint32_t field_10;     // uStack_a8
            uint32_t field_14;     // uStack_88
            int result;           // iStack_78
        };
        
        ActionData actionData;
        actionData.table = &g_actionTable;
        actionData.field_4 = g_globalEventContext;
        actionData.field_8 = g_globalEventContext;
        actionData.field_C = 0xffffffff;
        actionData.field_10 = 0xffffffff;
        actionData.field_14 = 0;
        actionData.result = 0;
        
        uint8_t actionBuffer[100] = {0}; // auStack_68
        processAction(actionBuffer, &actionData);
        
        if (actionData.result != 0) {
            return true;
        }
    }
    return false;
}