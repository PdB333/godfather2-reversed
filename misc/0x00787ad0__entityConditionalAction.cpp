// FUNC_NAME: entityConditionalAction
void entityConditionalAction(void* entity, void* target) {
    // Check if the entity is active; if so, perform the action on target.
    int active = isEntityActive(entity);
    if (active != 0) {
        performActionOnTarget(target);
    }
    // Run global post-update logic.
    globalPostUpdate();
}