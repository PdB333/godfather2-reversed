// FUNC_NAME: Entity::onUpdate
void __thiscall Entity::onUpdate(Entity* this, float deltaTime) {
    char isActive;
    char componentFlag[16];  // auStack_50
    char componentData[60];  // auStack_40

    // set internal time delta or update frame counter
    updateTime(deltaTime);  // FUN_0046f9c0

    // vtable+0x19c: query active state (e.g., isFinished, isPaused)
    isActive = (this->vtable->isActive)(this);
    if (isActive == 0) {
        // +0x2E8: some pending work flag (param_1[0xBA])
        if (this->field_0x2E8 != 0) {
            // retrieve component data using deltaTime
            getComponent(deltaTime, componentData);  // FUN_004b59d0
            // process the component (e.g., update animation, AI, etc.)
            processComponent(componentData);          // FUN_00aa3930
            // cleanup or finalize the component
            cleanupComponent(componentFlag);          // FUN_009f4c70
        }
    } else {
        // handle completion or transition when active returns true
        onComplete();  // FUN_0055db80
    }

    // vtable+0x258: call base class update (e.g., Entity::baseUpdate)
    (this->vtable->baseUpdate)(this);
}