// FUNC_NAME: GodfatherGameManager::getSimManager
// Function at 0x007ff880 - Retrieves the SimManager from a stored handle pointer inside the GameManager.
// Offset 0x1e40 stores a pointer to the SimManager's internal data block (at offset 0x48 from the actual SimManager object).
// Returns nullptr if the handle is null.

#include <cstdint>

class SimManager; // Forward declaration

class GodfatherGameManager
{
public:
    // +0x1e40: Pointer to SimManager internal data (offset 0x48 from SimManager base)
    // Returns the SimManager* by subtracting the known offset.
    SimManager* getSimManager() const
    {
        // Dereference the handle and subtract 0x48 to get the SimManager base
        if (uintptr_t handle = *(uintptr_t*)(this + 0x1e40))
        {
            return reinterpret_cast<SimManager*>(handle - 0x48);
        }
        return nullptr;
    }
};