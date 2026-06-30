// FUNC_NAME: FocusManager::SetFocus

#include <cstdint>

// Forward declarations
void StopResource(void* resource);

// Definition of the focus object structure based on observed offsets
struct FocusObject {
    // ... other fields ...
    void* m_resource1; // +0x10
    void* m_resource2; // +0x14
    int32_t m_activeFlag; // +0xa4 (0 = inactive, 1 = active)
    // ... other fields ...
};

// Global tracking the currently focused object (DAT_012058e8)
static FocusObject* s_currentFocusObject = nullptr;

/**
 * @brief Sets or toggles the active focus on a given object.
 * 
 * If the object differs from the current focus, it deactivates the old focus
 * resources, sets the new focus active and stores it. If the same object
 * is provided again, it simply deactivates it.
 * 
 * @param obj Pointer to the focus object to set or clear.
 */
void __fastcall FocusManager::SetFocus(FocusObject* obj)
{
    if (s_currentFocusObject != obj) {
        // New focus object: mark as active and update current
        obj->m_activeFlag = 1;
        s_currentFocusObject = obj;

        // Stop (deactivate) the two resources associated with the new focus
        // This likely corresponds to stopping sound, animations, etc.
        StopResource(obj->m_resource1);
        StopResource(obj->m_resource2);
    } else {
        // Same object: toggle off the active flag
        obj->m_activeFlag = 0;
    }
}