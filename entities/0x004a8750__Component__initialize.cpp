// FUNC_NAME: Component::initialize
// Address: 0x004a8750
// Role: Initializes a component object, registers with owner via virtual callbacks, and inserts into a global linked list.

#include <cstdint>

// Forward declaration of the Component class
class Component;

// Global list structure (assumed to be part of a larger manager)
// Offsets: +0x20 = head, +0x24 = tail
struct GlobalComponentList {
    uint8_t padding0[0x20]; // skip to head
    Component* head;        // +0x20
    Component* tail;        // +0x24
};

// External globals
extern GlobalComponentList* g_pComponentList; // DAT_0122344c
extern void* PTR_LAB_00e355bc; // vtable for Component

// Owner interface (abstract class assumed from virtual calls)
class IOwner {
public:
    // Virtual function at vtable offset +0x04: register a callback handler (stores address of handle)
    virtual void __thiscall registerCallback(void* callbackHandle) = 0;
    // Virtual function at vtable offset +0x5c: returns an ID
    virtual int __thiscall getSomeID() = 0;
};

// The Component class
class Component {
public:
    // Vtable pointer at +0x00
    void* vtable;

    // Fields initialized in constructor order (offsets relative to 'this')
    int32_t m_field1;   // +0x04
    int32_t m_field2;   // +0x08
    int32_t m_field3;   // +0x0c
    int32_t m_field4;   // +0x10
    int32_t m_field5;   // +0x14
    int32_t m_field6;   // +0x18 (set to -1)
    int32_t m_field7;   // +0x1c
    int32_t m_field8;   // +0x20
    int32_t m_field9;   // +0x24 (unused in init)
    int32_t m_field10;  // +0x28
    int32_t m_field11;  // +0x2c
    int32_t m_flags;    // +0x30 (bit 3 set later)
    Component* m_next;  // +0x34
    Component* m_prev;  // +0x38
    int32_t m_field15;  // +0x3c
    void* m_owner;      // +0x40 (first reference to owner)
    int32_t m_someID;   // +0x44 (from owner->getSomeID())
    void* m_callbackHandle; // +0x48 (used as argument to owner->registerCallback)
    void* m_owner2;     // +0x50 (second reference to owner)

    // Constructor-like initializer
    void __thiscall initialize(IOwner* owner);
};

void __thiscall Component::initialize(IOwner* owner) {
    // Zero-initialize most fields
    m_field1 = 0;
    m_field2 = 0;
    m_field8 = 0;
    m_flags = 0;
    m_field6 = -1;
    m_field7 = 0;
    m_field3 = 0;
    m_field4 = 0;
    m_field5 = 0;
    m_field11 = 0;
    m_next = 0;
    m_prev = 0;
    vtable = &PTR_LAB_00e355bc;
    m_field15 = 0;
    m_owner = owner;

    // Call virtual function on owner to register this component's callback handle (at +0x48)
    owner->registerCallback(&m_callbackHandle);

    m_owner2 = owner;

    // Retrieve some ID from owner
    m_someID = owner->getSomeID();

    // Set bit 3 of flags
    m_flags |= 8;

    // Link this component into the global doubly-linked list (tail insertion)
    m_next = 0;
    m_prev = g_pComponentList->tail;
    if (g_pComponentList->tail != 0) {
        g_pComponentList->tail->m_next = this;
        g_pComponentList->tail = this;
    } else {
        g_pComponentList->head = this;
        g_pComponentList->tail = this;
    }
}