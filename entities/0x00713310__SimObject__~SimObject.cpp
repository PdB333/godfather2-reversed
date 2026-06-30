// FUNC_NAME: SimObject::~SimObject
// Address: 0x00713310
// Role: Destructor for a base EA EARS engine object. Releases two dynamically allocated members, then sets vtable pointer to a static address (likely to mark deleted object).

#include <cstdint>

// Forward declaration of helper – safe delete that zeros the pointer (found at 0x004daf90)
static void safeDeleteAndNull(void** ptr);

// Vtable symbol (referenced at 0x00e2f0c0)
extern void* g_vtableStatic;

class SimObject {
public:
    void* vtable;          // +0x00
    void* member1;         // +0x04  (first dynamic pointer)
    // +0x08 (unknown, possibly padding or another member)
    void* member2;         // +0x0C (second dynamic pointer)

    // Destructor
    __thiscall ~SimObject() {
        // Release member2 (offset 0x0C) if it exists
        if (this->member2 != 0) {
            safeDeleteAndNull(reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x0C));
        }
        // Release member1 (offset 0x04) if it exists
        if (this->member1 != 0) {
            safeDeleteAndNull(reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x04));
        }
        // Mark vtable to static address (likely indicator that object has been destroyed)
        this->vtable = &g_vtableStatic;
    }
};

// Implementation of helper function (decompiled from 0x004daf90)
void safeDeleteAndNull(void** ptr) {
    if (*ptr) {
        delete *ptr;   // or some custom deallocation
        *ptr = 0;
    }
}