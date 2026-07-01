// Xbox PDB: EARS_Apt_UITrickleTextManager_UITrickleTextManager
// FUNC_NAME: UITrickleTextManager::TricklePool::TricklePool
// Address: 0x0098f6c0
// Constructor for the UITrickleTextManager's internal TricklePool object.
// Initializes vtable pointers, memory pool metadata via debug allocation, and clears pool state.

#include <cstddef>

// Forward declarations
class UITrickleTextManager;
extern UITrickleTextManager* g_TrickleTextManager; // DAT_01129934

class UITrickleTextManager {
public:
    // TricklePool: manages a pool of trickle text entries (fading text overlays)
    class TricklePool {
    public:
        // Virtual table pointers (multiple inheritance)
        void** m_vtable1;      // +0x00
        void** m_vtable2;      // +0x04

        // Pool state fields (offsets based on initialization)
        int m_nextFreeIndex;   // +0x3C (param_1[0xf]) - index of next free slot, 0 initially
        int m_activeCount;     // +0x40 (param_1[0x10]) - number of active entries, 0 initially
        int m_allocatedCount;  // +0x44 (param_1[0x11]) - size of allocated pool, 0 initially
        int m_maxCount;        // +0x48 (param_1[0x12]) - maximum capacity, 0 initially
        int m_lastAssignedID;  // +0x4C (param_1[0x13]) - last used ID, initialized to -1

        // Constructor
        __thiscall TricklePool() {
            // Store global reference to this pool instance
            g_TrickleTextManager = reinterpret_cast<UITrickleTextManager*>(this);

            // Set vtable pointers (for two virtual base classes)
            m_vtable1 = reinterpret_cast<void**>(0x00d91b10);
            m_vtable2 = reinterpret_cast<void**>(0x00d91b04);

            // Call debug allocation/pool initialization routine
            // Parameters: size=0x20, alignment=8, name="UITrickleTextManager::TricklePool", flags=0, unknown=0x10
            // This likely initializes a memory pool or debug tracker for the trickle entries
            FUN_004de0b0(0x20, 8, "UITrickleTextManager::TricklePool", 0, 0x10);

            // Initialize pool state: all free, no entries, no ID assigned
            m_nextFreeIndex = 0;
            m_activeCount = 0;
            m_allocatedCount = 0;
            m_maxCount = 0;
            m_lastAssignedID = -1;

            // Return this pointer implicitly
        }
    };
};

// The global pointer to the TricklePool (also serves as UITrickleTextManager*)
UITrickleTextManager* g_TrickleTextManager = nullptr; // DAT_01129934