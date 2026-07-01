// FUNC_NAME: Entity::deactivate
void __fastcall Entity::deactivate(Entity* this)
{
    // +0x80: flag indicating if entity is active/registered
    if (this->activeFlag != 0) {
        // Remove from global entity manager (singleton at 0x0112f9c0)
        gEntityManager.removeEntity(&gEntityManager);
        this->activeFlag = 0;
    }
}