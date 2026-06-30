// FUNC_NAME: Entity::releaseResources
void __fastcall Entity::releaseResources(int param_1)
{
    // +0xac: pointer to first resource (e.g., audio stream, animation)
    if (*(int *)(this + 0xac) != 0) {
        releaseResource(*(int *)(this + 0xac), param_1);
        *(int *)(this + 0xac) = 0;
    }
    // +0xb0: pointer to second resource
    if (*(int *)(this + 0xb0) != 0) {
        releaseResource(*(int *)(this + 0xb0), param_1);
        *(int *)(this + 0xb0) = 0;
    }
    // Call base class cleanup
    Entity::baseDestroy(this);
}