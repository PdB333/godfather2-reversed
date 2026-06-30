// FUNC_NAME: SimManager::updateActiveEntities
// Address: 0x0051aa50
// Iterates over the active object list, checks each object's parent ID against the current context,
// and updates flags accordingly. Called periodically to manage simulation state.

// Forward declarations (likely defined elsewhere in the engine)
struct TypeInfo {
    uint flags;        // +0x00 (unknown)
    // ...
    uint extraFlags;   // +0x14
};

struct SimObject {
    uint size;              // +0x00
    // ... other fields ...
    uint flags;             // +0x0c
    TypeInfo* typeInfo;     // +0x10
    SimObject* nextActive;  // +0x14
    // ... other fields ...
    uint parentIdLow;       // +0x70
    uint parentIdHigh;      // +0x74
};

// Constants (bit masks)
const uint kTypeFlag_RootOnly = 0x8000;      // If set, object is a root and is skipped
const uint kFlags_UpdateScheduled = 0x20000; // Object has been scheduled for an update
const uint kFlags_UpdateDirty = 0x40000;     // Object needs an update notification

// Global pointer to the head of the active object linked list
SimObject* gActiveObjectList;  // DAT_01205514

// Function prototypes
uint64 getCurrentContextId(); // FUN_0051d730 – returns a 64-bit context identifier
void notifyObjectUpdateScheduled(); // FUN_0051b120 – called when a new object is scheduled for update

void SimManager::updateActiveEntities()
{
    uint64 currentContext = getCurrentContextId();
    uint32 lowPart = (uint32)(currentContext);
    uint32 highPart = (uint32)(currentContext >> 32);

    SimObject* obj = gActiveObjectList;
    while (obj != nullptr)
    {
        // Check if this object's parent ID matches the current context
        if (obj->parentIdLow == lowPart &&
            obj->parentIdHigh == highPart)
        {
            TypeInfo* type = obj->typeInfo;
            // Skip objects whose type is marked as "root only" (e.g., core objects)
            if ((type->extraFlags & kTypeFlag_RootOnly) == 0)
            {
                // If not already scheduled for update, mark it and trigger notification
                if ((obj->flags & kFlags_UpdateScheduled) == 0)
                {
                    obj->flags |= kFlags_UpdateScheduled;
                    notifyObjectUpdateScheduled();
                }
                // Clear the "dirty" flag after scheduling
                obj->flags &= ~kFlags_UpdateDirty;
            }
        }
        obj = obj->nextActive;
    }
}