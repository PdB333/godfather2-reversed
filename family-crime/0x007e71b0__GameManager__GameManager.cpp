// FUNC_NAME: GameManager::GameManager
GameManager::GameManager(int someId, int someFlags) {
    EARSObject::EARSObject(someId, someFlags);
    this->vtable = (void*)&VTABLE_GameManager; // VTABLE at 0x00d6fb70
    this->field_0x74 = 0; // +0x74: some integer flag
    *(uint8_t*)&this->field_0x7c = 0; // +0x7c: single byte flag
    this->field_0x80 = 0; // +0x80: counter or pointer
    SomeManagedSystem* sys = SomeManagedSystem::getInstance();
    this->field_0x78 = *(uint32_t*)((uintptr_t)sys + 4); // +0x78: store version/ID from system
    sys->virtualFunction(2); // first vtable entry with arg=2
    Player* player = reinterpret_cast<Player*>(this->field_0x58); // +0x58: pointer to player object
    if (isGameActive()) {
        if (player != nullptr && player->field_0x4a8 == 0) {
            setDifficultyLevel((DifficultyLevel)3);
        }
        AudioManager::update(); // global audio update
    }
    if (isGameActive()) {
        InputManager::enable(0); // disable input? (param 0)
        InputManager::setCursorMode(0); // lock cursor?
    }
    // implicit return of this
}