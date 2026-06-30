// FUNC_NAME: Entity::~Entity
// Address: 0x00683280
// Role: Destructor - chains to base class destructor (BaseEntity::~BaseEntity at 0x004dafd0)
void __thiscall Entity::~Entity() {
    BaseEntity::~BaseEntity();
}