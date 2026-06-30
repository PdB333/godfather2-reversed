// FUNC_NAME: WorldSpatialManager::queryObjectsWithinRadius
// Address: 0x005fcf80
// Role: Iterates over all objects in the world, checks sphere-AABB overlap, and calls a functor for each overlapping object.
// Uses a global singleton (gWorldSpatialManager) at DAT_01223524.
// Objects must have a linked list structure (node +0x00 next, +0x08 object pointer).
// Object must have a valid AABB at offset 0x48 (float[6]: minX, minY, minZ, maxX, maxY, maxZ).
// Object must have a short flag at offset 0x3e (0 = inactive?).
// The functor's vtable: 
//   [1] (offset 4): bool isCandidate(Object*) - returns true if object should be considered
//   [2] (offset 8): int getContext() - returns a context ID (fallback: gWorldSpatialManager->defaultContext)
//   [3] (offset 12): void finishQuery() - called after iteration
// The threshold param_3 is squared distance.

#include <cstddef>

// Forward declarations
class Object;
class QueryFunctor;

// Likely the vtable layout for QueryFunctor
class QueryFunctorVTable {
public:
    bool (*isCandidate)(QueryFunctor*, Object*);        // vtable+4
    int  (*getContext)(QueryFunctor*);                 // vtable+8
    void (*finishQuery)(QueryFunctor*);                // vtable+12
};

class QueryFunctor {
public:
    QueryFunctorVTable* vtable;
};

// Object node for intrusive linked list
struct ObjectNode {
    ObjectNode* next;       // +0x00
    int padding;            // +0x04 (unknown)
    Object* object;         // +0x08
};

// World spatial manager singleton
class WorldSpatialManager {
public:
    // offsets known from decompiled code
    // +0x28: pointer to head of global object list (ObjectNode*)
    // +0x50: default context ID (int)
    // +0x00? maybe other members
    char unknown[0x28];
    ObjectNode* objectListHead; // +0x28
    char unknown2[0x50 - 0x28 - 4];
    int defaultContext;        // +0x50
};

// External globals
extern WorldSpatialManager* gWorldSpatialManager;  // DAT_01223524

// Internal helper functions (decompiled elsewhere)
extern void assertError(const char* msg); // FUN_00b97aea
extern void addQueryResult(QueryFunctor* functor, Object* obj); // FUN_005fcce0
extern void finalizeSpatialQuery(float* point, QueryFunctor* functor, int context, float squaredRadius, int someFlag); // FUN_006021f0

// The main query function
void WorldSpatialManager::queryObjectsWithinRadius(float* point, QueryFunctor* functor, float squaredRadius)
{
    int context = functor->vtable->getContext(functor);
    if (context == 0) {
        context = gWorldSpatialManager->defaultContext;  // fallback
    }

    ObjectNode* currentNode = gWorldSpatialManager->objectListHead;
    ObjectNode* headNode = *(ObjectNode**)((char*)gWorldSpatialManager + 0x28); // same as above, but the decompiler uses global+0x28

    while (true) {
        ObjectNode* listEndSentinel = *(ObjectNode**)((char*)gWorldSpatialManager + 0x28); // reload each iteration? actuelly iVar4+0x28
        // These checks appear to be debug assertion iterators:
        if (gWorldSpatialManager == (WorldSpatialManager*)-0x10) { // sentinel check? weird
            assertError("Invalid spatial manager");
        }
        if (headNode == listEndSentinel) break;

        if (gWorldSpatialManager == (WorldSpatialManager*)-0x10) {
            assertError("Invalid spatial manager");
        }
        if (headNode == *(ObjectNode**)((char*)gWorldSpatialManager + 0x28)) {
            assertError("List corrupted");
        }

        Object* obj = headNode->object;  // puVar7[2] => offset 8
        short flags = *(short*)((char*)obj + 0x3E);
        if (flags != 0 && functor->vtable->isCandidate(functor, obj)) {
            float* aabb = *(float**)((char*)obj + 0x48); // AABB: minX, minY, minZ, maxX, maxY, maxZ
            float dx = point[0] - aabb[0];
            if (dx < 0.0f) {
                dx = point[0] - aabb[3]; // maxX
                if (dx > 0.0f) {
                    dx = 0.0f;
                } else {
                    dx = dx * dx;
                }
            } else {
                dx = dx * dx;
            }
            float dy = point[1] - aabb[1];
            if (dy < 0.0f) {
                dy = point[1] - aabb[4];
                if (dy > 0.0f) {
                    dy = 0.0f;
                } else {
                    dy = dy * dy;
                }
            } else {
                dy = dy * dy;
            }
            float dz = point[2] - aabb[2];
            if (dz < 0.0f) {
                dz = point[2] - aabb[5];
                if (dz > 0.0f) {
                    dz = 0.0f;
                } else {
                    dz = dz * dz;
                }
            } else {
                dz = dz * dz;
            }
            float squaredDist = dx + dy + dz;
            if (squaredDist <= squaredRadius) {
                addQueryResult(functor, obj);
            }
        }

        if (headNode == *(ObjectNode**)((char*)gWorldSpatialManager + 0x28)) {
            assertError("List corrupted");
        }
        headNode = headNode->next; // iterate to next node
    }

    int someFlag = functor->vtable->finishQuery(functor); // returns a value, used as uVar6
    finalizeSpatialQuery(point, functor, context, squaredRadius, someFlag);
}