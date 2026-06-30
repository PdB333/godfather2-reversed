// FUNC_NAME: AICharacter::processTrackedObject
// Function address: 0x004a6210
// Role: Updates alert state of an AI character based on flags of a monitored target object.
//       If the target is found in the internal tracked-object list and has certain flags,
//       sets local alert flags and adds this character to the global active AI list.

#include <cstdint>

// Forward declaration for a function called within (address 0x004a69b0)
extern void resetAlertState(int zero);  // placeholder name, called with 0

// Static globals for the active AI linked list (doubly linked)
static AICharacter* g_activeListHead = nullptr;   // DAT_01205484
static AICharacter* g_activeListTail = nullptr;   // DAT_01205480

class AICharacter
{
public:
    // +0x68: pointer to array of tracked objects (pairs of object pointer + flags)
    uint32_t* m_trackedObjectArray;
    // +0x6c: number of entries in the array
    uint32_t  m_trackedObjectCount;
    // +0x82: local alert flags (bit0: 0x01, bit3: 0x08, bit7: 0x80, etc.)
    uint16_t  m_alertFlags;
    // +0x84: previous node in global active list
    AICharacter* m_prevInActiveList;
    // +0x88: next node in global active list
    AICharacter* m_nextInActiveList;

    // Internal struct for each tracked object entry (size 8 bytes)
    struct TrackedObjectEntry {
        AICharacter* object;   // pointer to tracked character
        uint16_t     flags;    // flags associated with that object
        // padding to 8 bytes implicit
    };

    __thiscall void processTrackedObject(AICharacter* target)
    {
        uint32_t index = 0;
        bool alertTriggered = false;

        // If there are no tracked objects, early out
        if (m_trackedObjectCount == 0)
            return;

        // Iterate through the array of tracked objects (8 bytes per entry)
        TrackedObjectEntry* entry = reinterpret_cast<TrackedObjectEntry*>(m_trackedObjectArray);
        while (entry->object != target)
        {
            index++;
            entry++;
            if (index >= m_trackedObjectCount)
                return;
        }

        // Found the target entry, now check its flags
        uint16_t targetFlags = entry->flags;

        // Bit 1 (0x2) and bit 3 (0x8) both set? Then set our local bit 3 (0x8)
        if ((targetFlags & 0x2) && (targetFlags & 0x8))
        {
            m_alertFlags |= 0x8;
            alertTriggered = true;
        }

        // Bit 4 (0x10) set? Then set our local bit 7 (0x80)
        if (targetFlags & 0x10)
        {
            m_alertFlags |= 0x80;
        }

        // If alert was triggered and this character is not already in the global active list,
        // insert it at the head of the list.
        if (alertTriggered && (m_nextInActiveList == nullptr) && (m_prevInActiveList == nullptr))
        {
            // Call some reset function (address 0x004a69b0)
            resetAlertState(0);

            // Standard doubly linked list insertion at head
            m_prevInActiveList = g_activeListHead;   // previous becomes current head
            m_nextInActiveList = nullptr;            // this will be new head, so next is null

            if (g_activeListHead != nullptr)
            {
                // Old head's next becomes this
                g_activeListHead->m_nextInActiveList = this;
                // Update tail to the old tail (seems like the original code retains the tail)
                // In the original, iVar2 = g_activeListTail, and then g_activeListTail = iVar2 (no change)
                // We replicate that (tail not updated here, but kept as is)
                // Actually the code sets g_activeListTail = (old tail) which is a no-op, so we do nothing.
            }

            // Set the head to this
            g_activeListHead = this;
        }
    }
};