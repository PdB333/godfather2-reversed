// FUNC_NAME: EventRouter::processEvent

// Function address: 0x0044aab0
// Role: Routes an event to a handler based on event ID and state.
// The object at 'this' contains an event ID (+0x04), a context pointer (+0x08),
// a state/type field (+0x0c), and a data source index (+0x18).
// Global 'gEventManagement' at 0x01223410 holds a table of ID->handler pairs
// at offset +0xd0 (array of {int id, HandlerFunc* func}) with count at +0x2d0.
// If state is 0 or 0x48, a handler is looked up and called.
// Otherwise, a derived object is used to call a virtual method at vtable+0x60.

#include <cstdint>

// Forward declarations
typedef uint32_t (*HandlerFunc)(int eventID, uint32_t* data, int, int, int);
extern uint8_t* gEventManagement; // DAT_01223410

// Helper to fetch a 4-word data block from a source index (returns pointer to static or heap data)
extern uint32_t* fetchData(uint16_t sourceIndex); // FUN_00449be0

class EventRouter
{
public:
    // Offsets:
    // +0x04: int eventID
    // +0x08: uint8_t* contextPtr  (points to another object)
    // +0x0c: int state  (0 or 0x48 trigger handler lookup, else fallback)
    // +0x18: uint16_t dataSourceIndex

    int eventID;
    uint8_t* contextPtr;
    int state;
    uint16_t dataSourceIndex;

    void __thiscall processEvent()
    {
        if ( (this->state == 0) || (this->state == 0x48) )
        {
            // ----- Handler dispatch path -----
            int* idToFind = &this->eventID;
            uint32_t count = *(uint32_t*)(gEventManagement + 0x2d0);
            if (count != 0)
            {
                // Search through the handler table (array of {int, HandlerFunc})
                int* tableEntry = (int*)(gEventManagement + 0xd0);
                uint32_t idx = 0;
                while (tableEntry[0] != *idToFind)
                {
                    idx++;
                    tableEntry += 2;
                    if (idx >= count)
                        return; // ID not found
                }
                HandlerFunc handler = (HandlerFunc)tableEntry[1];
                if (handler != nullptr)
                {
                    // Pre-call: invoke a method on the object pointed to by this->contextPtr
                    // contextPtr->+0x08 is another pointer, then vtable+0x1c
                    uint8_t* contextObj = *(uint8_t**)(this->contextPtr + 8);
                    (**(void (__thiscall**)(void))(**((uint8_t***)contextObj) + 0x1c))();

                    // Build a 4-word buffer on stack
                    uint32_t dataBuffer[4];
                    dataBuffer[0] = 0xbadbadba;
                    dataBuffer[1] = 0xbeefbeef;
                    dataBuffer[2] = 0xeac15a55;
                    dataBuffer[3] = 0x91100911;

                    // Fetch actual data based on dataSourceIndex
                    uint32_t* fetched = fetchData(this->dataSourceIndex);
                    dataBuffer[0] = fetched[0];
                    dataBuffer[1] = fetched[1];
                    dataBuffer[2] = fetched[2];
                    dataBuffer[3] = fetched[3];

                    // Call the handler: handler(eventID, &dataBuffer, 0, 0, 3)
                    handler(*idToFind, dataBuffer, 0, 0, 3);
                }
            }
        }
        else
        {
            // ----- Fallback path: use derived object -----
            uint8_t* derivedObj;
            if (this->state == 0)
                derivedObj = nullptr;
            else
                derivedObj = (uint8_t*)(this->state - 0x48);

            if (derivedObj != nullptr)
            {
                // derivedObj+0x130 points to a vtable pointer, then call virtual at offset 0x60
                uint8_t* vtablePtr = *(uint8_t**)(derivedObj + 0x130);
                if (vtablePtr != nullptr)
                {
                    (**(void (__thiscall*)(uint8_t*))(*((uint8_t***)vtablePtr)[0x60 / 4]))(derivedObj);
                }
            }
        }
    }
};