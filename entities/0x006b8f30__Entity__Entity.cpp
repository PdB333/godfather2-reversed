// FUNC_NAME: Entity::Entity
class Entity {
public:
    // Constructor at 0x006b8f30
    // param_2: flag byte - if bit 0 set, initialize internal data of size 0x9c
    Entity(bool allocate) {
        // Call base class constructor (0x006b8b60)
        BaseEntity::BaseEntity();  

        if (allocate) {
            // Initialize internal allocation with size 0x9c (156 bytes)
            // This may allocate memory or set up member arrays
            initInternalAllocation(0x9c);  // Calls FUN_0043b960(this, 0x9c)
        }
    }

private:
    void initInternalAllocation(int size);  // defined at 0x0043b960
};