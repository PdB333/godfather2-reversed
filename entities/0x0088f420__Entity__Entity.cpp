// FUNC_NAME: Entity::Entity
// 0x0088f420 - Constructor for Entity base class

#include <cstdint>

class Entity {
public:
    Entity();
    virtual ~Entity() = default;

private:
    // vtable at +0x00
    void* m_vtable;
    // interface vtables (+0x3C, +0x48)
    void* m_interface1Vtable;
    void* m_interface2Vtable;
    // unknown fields
    uint32_t m_field50;   // +0x50
    uint32_t m_field54;   // +0x54
    uint32_t m_field58;   // +0x58
    int32_t m_handle;     // +0x5C, initialized to -1

    // Linked list node at +0x64
    struct ListNode {
        ListNode* m_next;   // +0x64
        ListNode* m_prev;   // +0x68
        uint32_t m_count;   // +0x6C
        uint8_t  m_flag;    // +0x70
        uint32_t m_field74; // +0x74
    } m_listNode;
};

// External symbols for vtables
extern void* Entity_vtable;
extern void* Interface1_vtable;
extern void* Interface2_vtable;
extern uint32_t g_EntityRegistration; // DAT_0112e248

// Constructor
Entity::Entity() {
    // Register with engine object manager
    Engine::registerComponent(&g_EntityRegistration, 0);

    // Set vtables
    m_vtable = &Entity_vtable;
    m_interface1Vtable = &Interface1_vtable;
    m_interface2Vtable = &Interface2_vtable;

    // Initialize members
    m_field50 = 0;
    m_field54 = 0;
    m_field58 = 0;
    m_handle = -1;

    // Initialize embedded linked list as empty circular list
    m_listNode.m_next = &m_listNode;
    m_listNode.m_prev = &m_listNode;
    m_listNode.m_count = 0;
    m_listNode.m_flag = 0;
    m_listNode.m_field74 = 0;

    // Call base class / additional constructor
    FUN_0088dd00(this);
}