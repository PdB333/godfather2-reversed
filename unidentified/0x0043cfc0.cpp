// FUN_0043cfc0: CEventDispatcher::dispatchMatchingEvents
// This function iterates in reverse order over an array of elements, filtering by a bitmask, and calls a handler method on matching elements.
// It then calls an internal helper (FUN_0043db10) for each match.
// The element array is stored at this+0x10, each element is 0x1C bytes.
// this+0x14 holds the element count (int).
// this+0xC holds a pointer to a 'handler' object with a virtual method at vtable+4 (index 1) that takes an entity pointer and an int (0).

class CEventDispatcher {
    // Fields at known offsets
    // +0x0: vtable pointer (if any) - not used here
    // +0xC: m_pHandler (CHandler*) - pointer to a handler object with virtual Dispatch method
    // +0x10: m_pElements (SElement*) - pointer to dynamic array of element structs (size 0x1C each)
    // +0x14: m_elementCount (int) - number of elements in the array
public:
    void dispatchMatchingEvents(uint eventMask);
};

// Element structure: each entry is 0x1C bytes
struct SElement {
    // +0x00: unknown (4 bytes)
    // +0x04: unknown (4 bytes)
    // +0x08: unknown (4 bytes)
    // +0x0C: unknown (4 bytes)
    // +0x10: unknown (4 bytes)
    // +0x14: unknown (4 bytes)
    // +0x18: m_pEntity (CEntity*) - pointer to entity object
};

// Entity class with flags at +8
struct CEntity {
    // +0x00: vtable (4 bytes)
    // +0x04: unknown (4 bytes)
    // +0x08: m_eventMask (uint) - bitmask of event types this entity responds to
    // ... rest of entity data
};

// Handler interface (or base class) with virtual Dispatch
class CHandler {
public:
    virtual void dispatch(CEntity* entity, int param) = 0; // vtable index 1 (offset 4)
};

void CEventDispatcher::dispatchMatchingEvents(uint eventMask) {
    int count = *(int*)((char*)this + 0x14);
    int i = count - 1;
    if (i >= 0) {
        int offset = i * 0x1C;
        do {
            // Get element at index i
            SElement* element = *(SElement**)((char*)this + 0x10);
            CEntity* entity = *(CEntity**)((char*)element + 0x18 + offset);

            // Check entity is non-null and its event mask matches the requested mask
            if (entity != 0 && (*(uint*)((char*)entity + 8) & eventMask) != 0) {
                // Call the handler's dispatch method (vtable+4) on the entity
                CHandler* handler = *(CHandler**)((char*)this + 0xC);
                void (**vtable)(void) = *(void (***)(void))handler; // get vtable pointer
                void (*dispatchFunc)(CEntity*, int) = (void (*)(CEntity*, int))vtable[1];
                dispatchFunc(entity, 0);

                // If i is still non-negative, call internal helper FUN_0043db10()
                // (This condition is always true because i hasn't changed; call always happens)
                if (i >= 0) {
                    FUN_0043db10(); // internal processing (defined elsewhere)
                }
            }
            i--;
            offset -= 0x1C;
        } while (i >= 0);
    }
}