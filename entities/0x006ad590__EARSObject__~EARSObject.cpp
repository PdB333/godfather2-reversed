// FUNC_NAME: EARSObject::~EARSObject
// Address: 0x006ad590
// Role: Destructor for EARSObject, cleans up a sub-object at +0x04 and sets vtable to base.

#include <cstddef>

// Forward declaration of the helper that releases a sub-object pointer (likely sets to null)
extern void releaseSubObject(void* pSubObjectField);

class EARSObject {
public:
    int* m_vtable;      // +0x00: vtable pointer (set to base vtable after destruction)
    void* m_subObject;  // +0x04: pointer to a sub-object that must be released

    ~EARSObject() {
        if (m_subObject != nullptr) {
            // Pass address of the sub-object field so the function can nullify it
            releaseSubObject(&m_subObject);
        }
        // Set vtable to base class vtable to avoid virtual calls after destruction
        m_vtable = reinterpret_cast<int*>(0x00e2f0c0);
    }
};