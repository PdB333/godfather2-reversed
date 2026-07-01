// FUNC_NAME: SimObject::SimObject
// Constructor at 0x00899390 for a SimObject-like class that is registered into a global linked list.
// Based on EA EARS engine patterns (Torque-derived). Called with a name string, ID, type, and flags.

// Assumed base class (constructor at 0x0064cc90)
class BaseObject {
public:
    BaseObject();
    // Base class vtable etc.
};

// Global list head pointer (DAT_012059ec)
extern BaseObject* g_simObjectListHead;

class SimObject : public BaseObject {
public:
    SimObject(const char* name, uint32_t objectId, uint32_t type, uint32_t flags);

    // Virtual table pointer at +0x00 (PTR_LAB_00d77de0)
    // Fields (offsets in bytes):
    // +0x04 uint32_t m_objectId;      (this[1] = objectId)
    // +0x08 uint32_t m_flags;         (this[2] = flags, from param_5)
    // +0x0C uint32_t m_type;          (this[3] = type, from param_4)
    // +0x10 - +0x1C uint32_t reserved[4]; (zeroed)
    // +0x20 char m_name[64];          (8*4 = 0x20)
    // +0x70 SimObject* m_next;        (0x1c * 4 = 0x70)

private:
    SimObject(const SimObject&) = delete;
    SimObject& operator=(const SimObject&) = delete;
};

// Constructor implementation
SimObject::SimObject(const char* name, uint32_t objectId, uint32_t type, uint32_t flags)
    : BaseObject()  // calls FUN_0064cc90
{
    // Set vtable pointer (address of class vtable)
    extern void* PTR_LAB_00d77de0;
    *reinterpret_cast<void**>(this) = PTR_LAB_00d77de0;

    // Copy name into buffer (max 63 characters, null-terminated)
    char* nameBuffer = reinterpret_cast<char*>(this) + 0x20; // m_name at offset 0x20
    strncpy(nameBuffer, name, 0x3f);
    nameBuffer[0x3f] = '\0'; // ensure null termination

    // Set fields (note the scrambled parameter-to-field mapping)
    m_objectId = objectId;               // this[1]
    m_flags    = flags;                  // this[2] (param_5)
    m_type     = type;                   // this[3] (param_4)

    // Clear reserved area (offsets 0x10–0x1C)
    uint32_t* reserved = reinterpret_cast<uint32_t*>(this) + 4; // +0x10
    reserved[0] = 0; // +0x10
    reserved[1] = 0; // +0x14
    reserved[2] = 0; // +0x18
    reserved[3] = 0; // +0x1C

    // Insert this object at head of global singly-linked list
    // m_next at offset 0x70 (this[0x1c])
    m_next = static_cast<SimObject*>(g_simObjectListHead);
    g_simObjectListHead = this;
}