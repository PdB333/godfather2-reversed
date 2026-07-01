// FUNC_NAME: AptAnimation::processActionPool
// Address: 0x005a6280
// This function processes actions in a circular action pool (256 slots, each 5 ints).
// It iterates from the current read pointer (head) to the write pointer (tail),
// dispatching actions based on type (0 or 1) via a function table.
// The pool is stored as an array at the beginning of the object, with head/tail pointers at +0x1400/+0x1404.

#include <cstdint>

// Action structure (5 ints, 20 bytes)
struct Action {
    int type;        // 0 or 1
    int param1;      // used for type 1
    int param2;      // used for type 1
    int resourceId;  // index into function table (masked with 0x7FFF)
    int param3;      // unused in this function
};

// Function table for action handlers (externally defined)
extern void (*gActionHandlers[])(uint32_t*); // DAT_0103aee0

// Debug assertion helper (simplified)
static void assertFailed(const char* expr, const char* file, int line) {
    // In debug builds, this triggers a breakpoint
    __debugbreak();
}

class AptAnimation {
public:
    // Action pool: 256 actions, each 20 bytes = 5120 bytes
    Action aActionPool[256]; // offset 0x0

    // Head and tail pointers into the pool (offsets 0x1400 and 0x1404)
    Action* m_pHead; // current read position
    Action* m_pTail; // write position (one past last written)

    // Process all pending actions in the pool
    void processActionPool() {
        Action* pCur = m_pHead;
        Action* pEnd = m_pTail;

        // If pool is empty, reset pointers to base
        if (pCur == pEnd) {
            m_pHead = aActionPool;
            m_pTail = aActionPool;
            return;
        }

        do {
            // Debug bounds check: pCur must be within [aActionPool, aActionPool+256)
            if (pCur < aActionPool) {
                // Assert: pCur >= &aActionPool[0]
                assertFailed("pCur >= &aActionPool[0]", "..\\source\\Apt\\AptAnimation.cpp", 0x2d0);
                // If assertion fails, breakpoint
                __debugbreak();
                return;
            }
            if (pCur >= &aActionPool[256]) {
                // Assert: pCur < &aActionPool[256]
                assertFailed("pCur < &aActionPool[256]", "..\\source\\Apt\\AptAnimation.cpp", 0x2d0);
                __debugbreak();
                return;
            }

            // Dispatch based on action type
            if (pCur->type == 0) {
                // Call handler for resourceId (masked to 15 bits)
                uint32_t index = pCur->resourceId & 0x7FFF;
                gActionHandlers[index](&pCur->resourceId);
            } else if (pCur->type == 1) {
                // Call two handlers: param1 and param2 as resource IDs
                uint32_t index1 = pCur->param1 & 0x7FFF;
                uint32_t index2 = pCur->param2 & 0x7FFF;
                gActionHandlers[index1](&pCur->param1);
                gActionHandlers[index2](&pCur->param2);
            } else {
                // Unknown type - assert
                assertFailed("0", "..\\source\\Apt\\AptAnimation.cpp", 0x2dd);
                __debugbreak();
                return;
            }

            // Advance to next action (5 ints forward)
            pCur += 1; // Action is 5 ints, but pointer arithmetic works because Action is a struct

            // Wrap around if we reach the end of the pool
            if (pCur == &aActionPool[256]) {
                pCur = aActionPool;
            }

            // Check if we've caught up to the tail
            if (pCur == pEnd) {
                m_pHead = aActionPool;
                m_pTail = aActionPool;
                return;
            }
        } while (true);
    }
};