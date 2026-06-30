// FUNC_NAME: Entity::constructor
int Entity::constructor(void* thisPtr, unsigned int param2) {
    int result = 0;
    if (thisPtr != 0) {
        // Call base class constructors (order as in vtable layout)
        SimObject::constructor(thisPtr);  // likely sim object base
        NetObject::constructor(thisPtr);  // networking base
        // Register the new entity with the global entity manager
        result = EntityManager::registerEntity(gEntityManager, param2);
    }
    return result;
}