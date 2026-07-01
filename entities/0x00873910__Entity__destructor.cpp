// FUNC_NAME: Entity::destructor
void __thiscall Entity::destructor(Entity* this)
{
    if (this != 0) {
        this->release(0, 0); // FUN_005e6820: release resources
        this->deinit();      // FUN_005e6660: deinitialize
    }
}