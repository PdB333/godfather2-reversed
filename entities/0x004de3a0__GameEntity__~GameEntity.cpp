// FUNC_NAME: GameEntity::~GameEntity
void __thiscall GameEntity::~GameEntity(GameEntity* this)
{
    // +0x00: vtable pointer
    this->vtable = &vtable_GameEntity;
    
    // +0x04: pointer to child object (owned, must be destroyed via virtual destructor)
    if (this->mChildObject != nullptr)
    {
        // Call virtual destructor at vtable offset 0xc (index 3) of child object
        (*(void(__thiscall**)(void*))(*(uint32_t*)this->mChildObject + 0xc))(this->mChildObject);
    }
    
    // Set vtable to base class vtable for base destructor call
    this->vtable = &vtable_BaseClass;
}