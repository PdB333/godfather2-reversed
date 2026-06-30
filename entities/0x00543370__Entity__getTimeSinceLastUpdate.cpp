// FUNC_NAME: Entity::getTimeSinceLastUpdate
int __thiscall Entity::getTimeSinceLastUpdate(Entity* thisPtr)
{
    // Virtual function at vtable+0x1fc returns current engine time (likely in ms or seconds)
    int currentTime = (*(int (__thiscall**)(Entity*))(*(int*)thisPtr + 0x1fc))(thisPtr);

    // Field at +0x2BC stores the timestamp of the last update event
    int lastUpdateTime = *(int*)((char*)thisPtr + 0x2BC);

    // Return elapsed time since the last recorded update
    return lastUpdateTime - currentTime;
}