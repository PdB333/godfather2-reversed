// FUNC_NAME: CollisionManager::processActiveObjects

// Address: 0x004540f0
// Role: Iterates over all active physics objects from a global linked list,
//       checks for collisions against a set of static objects and a spatial partition,
//       creates collision pair objects when new collisions are detected.

class PhysicsObject;
class CollisionPair;
class SpatialCellNode;

// Global linked list head of all physics objects
PhysicsObject* g_pObjectListHead = nullptr; // Actually DAT_0120e9f4

// Collision pair allocation function (size 0x54)
extern void* __cdecl allocCollisionPair(); // FUN_009c8e50

// Initializer for collision pair (given an active object and flag)
extern CollisionPair* __thiscall initCollisionPair(CollisionPair* this, PhysicsObject* activeObj, int flag); // FUN_004a8750

// Virtual table offsets for PhysicsObject:
// +0x04: getCollisionId(SomeId* out)
// +0x10: onMatchFound()
// +0x2c: updateTransform()
// +0x60: onCollisionResolved()

// SomeId is a 8-byte structure (e.g., two ints)
struct SomeId {
    int id0;
    int id1;
};

class PhysicsObject {
public:
    void** vtable;               // +0x00
    PhysicsObject* next;         // +0x04 (next in global list)
    CollisionPair* collisionPtr; // +0x0C (offset 3 in int units)
    // ... other fields
};

class CollisionPair {
    // 0x54 bytes allocated
    PhysicsObject* activeObj;
    int flag; // 1 typically
    // ... other collision data
};

class SpatialCellNode {
public:
    SpatialCellNode* next;        // +0x34 (offset 0x34 from parent)
    int cellId0;                  // +0x48
    int cellId1;                  // +0x4C
    char flags;                   // +0x3C (bit 0: already has active pair)
    PhysicsObject* sourceObj;     // +0x40 (the object that caused this cell to be relevant)
};

class CollisionManager {
public:
    SpatialCellNode* cellListHead; // +0x20
    int* processedIdArray;        // +0x28 (array of cell IDs already processed)
    int processedIdCount;         // +0x2C
};

void __thiscall CollisionManager::processActiveObjects(CollisionManager* this) {
    PhysicsObject* activeList[128];  // up to 128 active objects (aiStack_a10)
    int activeCount = 0;
    
    PhysicsObject* staticList[512];  // up to 512 non-active objects (aiStack_808)
    int staticCount = 0;
    
    PhysicsObject* objIter = g_pObjectListHead;
    
    // Phase 1: separate objects into active (needs update) and static
    while (objIter != nullptr) {
        if (objIter->collisionPtr == nullptr) {
            // Object has no collision pair yet -> treat as active
            objIter->vtable[0x2c](); // updateTransform()
            if (activeCount < 128) {
                activeList[activeCount] = objIter;
                activeCount++;
            }
        } else {
            // Already has a collision pair -> treat as static for this frame
            if (staticCount < 512) {
                staticList[staticCount] = objIter;
                staticCount++;
            }
        }
        objIter = objIter->next;
    }
    
    if (activeCount == 0) {
        return;
    }
    
    // Phase 2: for each active object, find collisions
    for (int activeIdx = 0; activeIdx < activeCount; activeIdx++) {
        PhysicsObject* activeObj = activeList[activeIdx];
        bool collisionFound = false;
        
        // 2a: Check against all static objects
        for (int staticIdx = 0; staticIdx < staticCount; staticIdx++) {
            PhysicsObject* staticObj = staticList[staticIdx];
            
            SomeId activeId, staticId;
            activeObj->vtable[0x04](&activeId);  // getCollisionId
            staticObj->vtable[0x04](&staticId);  // getCollisionId
            
            if (activeId.id0 == staticId.id0 && activeId.id1 == staticId.id1) {
                // Collision detected between active and static
                activeObj->vtable[0x10](); // onMatchFound
                activeObj->vtable[0x60](); // onCollisionResolved
                collisionFound = true;
                break;
            }
        }
        
        if (collisionFound) {
            continue;
        }
        
        // 2b: If not found, search spatial cell hierarchy (linked list from this->cellListHead)
        SpatialCellNode* cellNode = this->cellListHead;
        int foundCellNode = 0;  // iStack_a30
        SpatialCellNode* matchedCell = nullptr;
        
        while (cellNode != nullptr) {
            SomeId activeId;
            activeObj->vtable[0x04](&activeId);
            
            if (cellNode->cellId0 == activeId.id0 && cellNode->cellId1 == activeId.id1) {
                // This cell matches the active object's ID
                if (cellNode->flags & 0x01) {
                    // Cell already has a collision pair: search processedIdArray
                    int idx = 0;
                    int foundIdx = -1;
                    if (this->processedIdCount > 0) {
                        int* idArray = this->processedIdArray;
                        for (; idx < this->processedIdCount; idx++, idArray++) {
                            if (*idArray == (int)cellNode) {
                                foundIdx = idx;
                                break;
                            }
                        }
                    }
                    if (foundIdx == -1) {
                        // Not processed yet, allocate new collision pair
                        goto LAB_ALLOC_PAIR;
                    }
                } else {
                    // Cell not tagged, just store the object pointer
                    cellNode->sourceObj = activeObj;
                    foundCellNode = (int)cellNode;
                    matchedCell = cellNode;
                    break;
                }
            }
            cellNode = cellNode->next;
        }
        
        if (matchedCell == nullptr) {
            // No matching cell found; allocate new collision pair
            LAB_ALLOC_PAIR:
            CollisionPair* newPair = (CollisionPair*)allocCollisionPair(); // size 0x54
            if (newPair != nullptr) {
                newPair = initCollisionPair(newPair, activeObj, 1);
                if (newPair != nullptr) {
                    foundCellNode = (int)newPair; // iStack_a30
                } else {
                    foundCellNode = 0;
                }
            } else {
                foundCellNode = 0;
            }
        }
        
        // Assign collision pair pointer to the active object
        activeObj->collisionPtr = (CollisionPair*)foundCellNode;
        
        // Add active object to static list (so subsequent objects can collide with it too)
        if (staticCount < 512) {
            staticList[staticCount] = activeObj;
            staticCount++;
        }
    }
}