// FUNC_NAME: ProximityDetector::update

/* Function address: 0x0089f160
 * Role: Updates proximity sensor, checking for nearby entities within a radius.
 * Depending on state at +0x180 (0=inactive, 1=active, 2=dead), either iterates over all
 * valid entities to process proximity or performs cleanup (state 2).
 * After proximity checks, allocates and queues an event node for further processing.
 */

#include <cstdint>

class ProximityDetector {
public:
    void update(int ownerEntity); // __thiscall: this = param_1, owner = param_2
};

// Forward declarations (addresses approximate)
extern void* gEntityManager;                     // DAT_012233a0 - pointer to array of entity pointers
extern float gWComponent;                        // DAT_00d5780c - likely 1.0f
extern uint32_t gEventType;                      // DAT_00d5c458 - event type constant
extern float gProximityRadius2;                  // (not global, from param_1+0x184)

// Helper functions (addresses from callees)
float* GetFirstListEntry(float* outPtr, int listHead, int context, int param); // 0x0089d7d0
uint32_t GetEntityCount();                                                      // 0x0043ff40
void ProcessDeadEntity(void* entity, int owner);                                // 0x0089d930
float* GetPlayerTransform();                                                    // 0x00471610 - returns pointer to position
void ProxInactiveAction(int owner, int entity);                                 // 0x0089b970
void ProxActiveAction(int owner, int entity);                                   // 0x00898f80
void* AllocateEventNode(uint32_t size);                                         // 0x009c8e50
void QueueEvent(int eventQueue, int zero, uint32_t eventType, void* node, int param); // 0x00440590

// Vtable for event node
extern uint32_t gEventNodeVtable; // &PTR_FUN_00e31e2c

void ProximityDetector::update(int ownerEntity) {
    int* pEntityList = (int*)*(int*)((char*)gEntityManager + 4); // assume gEntityManager+4 is array pointer
    uint32_t entityCount = GetEntityCount();

    if (*(int*)((char*)this + 0x180) == 2) {
        // State 2: cleanup/expired
        float firstEntry;
        GetFirstListEntry(&firstEntry, (int)this + 0x1ac, (int)this, 0);
        if (firstEntry != 0.0f) {
            *(int*)((int)firstEntry + 8) = 0; // clear some field
        }

        float countFloat = (float)GetEntityCount();
        if (countFloat != 0.0f) {
            for (int idx = 0; (float)idx < countFloat; idx++) {
                int* pEntity = *(int**)(pEntityList + idx);
                if (pEntity != nullptr) {
                    void* entityObj = (char*)pEntity - 0x1f30; // base offset
                    if (entityObj != nullptr) {
                        // virtual call at +0x2CC – likely "IsAlive" or "IsValid"
                        char (*isValid)(void*) = (char(*)(void*))(*(int*)entityObj + 0x2CC);
                        if (isValid(entityObj) == '\0') {
                            ProcessDeadEntity(entityObj, ownerEntity);
                        }
                    }
                }
            }
        }
    } else {
        // State 0 or 1: active proximity detection
        float* playerPos = GetPlayerTransform();
        float playerX = playerPos[0x30 / 4]; // offset 0x30
        float playerY = playerPos[0x34 / 4]; // offset 0x34
        float playerZ = playerPos[0x38 / 4]; // offset 0x38
        float playerW = gWComponent;

        float radius = *(float*)((char*)this + 0x184);
        float radiusSq = radius * radius;

        for (uint32_t i = 0; i < entityCount; i++) {
            int* pEntity = pEntityList[i];
            if (pEntity == nullptr) continue;

            void* entityObj = (char*)pEntity - 0x1f30;
            if (entityObj == nullptr) continue;
            if (entityObj == (void*)ownerEntity) continue; // skip self?

            // Compare team/family ID: owner +0x1EF4 vs entity -0x3C
            if (*(int*)((char*)ownerEntity + 0x1ef4) == *(int*)((char*)pEntity - 0x3c)) {
                continue; // same team – skip
            }

            // Get entity position (assumes GetPlayerTransform returns transform based on current entity?
            // Actually it's called again for each entity – suspicious.
            // Possibly it returns a static pointer that changes per entity? Or it's a global camera position?
            // We'll assume it's the entity's own transform obtained via GetPlayerTransform() which may use a global pointer.
            float* entityPos = GetPlayerTransform();
            float dx = entityPos[0x30 / 4] - playerX;
            float dy = entityPos[0x34 / 4] - playerY;
            float dz = entityPos[0x38 / 4] - playerZ;
            float dw = gWComponent - playerW; // likely ignored

            float distSq = dx*dx + dy*dy + dz*dz;
            if (distSq < radiusSq) {
                int state = *(int*)((char*)this + 0x180);
                if (state == 0) {
                    ProxInactiveAction(ownerEntity, (int)entityObj);
                } else if (state == 1) {
                    ProxActiveAction(ownerEntity, (int)entityObj);
                }
            }
        }
    }

    // Allocate and enqueue an event node for the sensor
    struct EventNode {
        uint32_t vtable;
        void* listPointer; // will point to this+0x48
        uint32_t next;
    };
    EventNode* node = (EventNode*)AllocateEventNode(12);
    if (node != nullptr) {
        node->vtable = (uint32_t)&gEventNodeVtable;
        node->listPointer = (char*)this + 0x48;
        node->next = 0;
        // Insert into linked list at this+0x4C (tail pointer)
        if ((char*)this + 0x48 != nullptr) {
            node->next = *(uint32_t*)((char*)this + 0x4C);
            *(uint32_t*)((char*)this + 0x4C) = (uint32_t)node + 4; // point to listPointer? Actually code sets *(this+0x4C) = (puVar6+1)
            // The original code: *(undefined4**)(param_1 + 0x4c) = puVar6 + 1; // offset 4 bytes into node
            // So node->listPointer is the second field. So we store address of node->listPointer.
            *(void**)((char*)this + 0x4C) = &node->listPointer;
        }
    }
    QueueEvent((int)this + 0x1CC, 0, gEventType, node, 0);
}