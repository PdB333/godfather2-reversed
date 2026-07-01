// FUNC_NAME: EARS::Framework::Entity::~Entity
void __thiscall releaseResource(void *resource);
void __thiscall operatorDelete(void *ptr);

class Entity {
public:
    void **vtable;     // +0x00
    void *resource;    // +0x04
    Entity *__thiscall ~Entity(Entity *this, byte flags);
};

Entity *__thiscall Entity::~Entity(Entity *this, byte flags) {
    if (this->resource != 0) {
        releaseResource(this->resource);
    }
    this->vtable = &PTR_LAB_00e2f0c0;
    if ((flags & 1) != 0) {
        operatorDelete(this);
    }
    return this;
}