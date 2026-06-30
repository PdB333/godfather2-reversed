// FUNC_NAME: GameObjectComponent::create
// Function address: 0x005f7290
// Role: Allocate and initialize a GameObjectComponent with given owner pointer

class GameObjectComponent
{
public:
    void* vtable;                // +0x00
    int    m_refCount;           // +0x04
    void*  m_pOwner;             // +0x08
    int    m_state;              // +0x0C
    int    m_flags;              // +0x10
    int    m_type;               // +0x14
    int    m_subType;            // +0x18
    int    m_priority;           // +0x1C
    int    m_timer;              // +0x20
    int    m_counter;            // +0x24
    int    m_value1;             // +0x28
    int    m_value2;             // +0x2C
    int    m_value3;             // +0x30
    int    m_value4;             // +0x34

    static GameObjectComponent* create(void* owner);
};

// External allocation function (likely custom allocator)
extern void* allocate(size_t size);

GameObjectComponent* GameObjectComponent::create(void* owner)
{
    // Allocate memory for the component (0x38 bytes)
    GameObjectComponent* obj = (GameObjectComponent*)allocate(0x38);
    if (obj != nullptr)
    {
        // Initialize fields
        obj->m_refCount = 0;
        obj->vtable = &PTR_FUN_00e407e4;  // Virtual function table
        obj->m_pOwner = owner;
        obj->m_state = 0;
        obj->m_flags = 0;
        obj->m_type = 0;
        obj->m_subType = 0;
        obj->m_priority = 0;
        obj->m_timer = 0;
        obj->m_counter = 0;
        obj->m_value1 = 0;
        obj->m_value2 = 0;
        obj->m_value3 = 0;
        obj->m_value4 = 0;
    }
    return obj;
}