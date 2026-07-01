// FUNC_NAME: ObjectFactory::createAndRegister(uint objectType)
void __fastcall ObjectFactory::createAndRegister(uint objectType) {
    // Check if the game simulation is active
    if (!Game::isSimulationActive()) {
        return;
    }

    // Allocate memory for a new object (size 0x38 = 56 bytes)
    void* objectMemory = Memory::allocate(0x38);
    if (objectMemory != nullptr) {
        // Construct the object using the objectType and the allocated memory
        // FUN_008aa450 likely performs initialization and returns the object
        Object* newObject = Object::constructFromType(objectType);
        // Register the object with the simulation manager
        Simulation::registerObject(newObject);
        return;
    }

    // If allocation fails, register a null pointer to indicate failure
    Simulation::registerObject(nullptr);
}