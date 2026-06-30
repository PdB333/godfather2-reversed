// FUNC_NAME: Entity::Entity
// Address: 0x0073a910
// Role: Constructor for an Entity with optional post-initialization flag.

class BaseEntity; // forward declaration
void __thiscall BaseEntity::BaseEntity(void); // base class constructor at 0x007394c0
void __thiscall Entity::postConstruct(void);   // optional post-init at 0x00624da0

class Entity : public BaseEntity {
public:
    // Constructor takes a flags byte; bit 0 triggers postConstruct
    // Returns this pointer (standard __thiscall constructor convention)
    void* __thiscall Entity(unsigned char flags);
};

void* __thiscall Entity::Entity(unsigned char flags) {
    // Call base constructor (initializes base class members)
    BaseEntity::BaseEntity(); // 0x007394c0

    // If the heap-allocated flag (bit 0) is set, perform additional setup
    if (flags & 1) {
        postConstruct(); // 0x00624da0 – registers object or does post-initialization
    }

    // Return this pointer (as required by __thiscall)
    return this;
}