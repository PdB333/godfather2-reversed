// FUNC_NAME: Entity::~Entity
void __thiscall Entity::~Entity()
{
    // Calls base class / component teardown routine
    Entity::teardown();  // 0x005e1fd0
}