// FUNC_NAME: Gameplay::updateTargetedEntity
void Gameplay::updateTargetedEntity(void)
{
    int targetPtr = GetCurrentTarget();
    if (targetPtr != 0) {
        UpdateEntity(reinterpret_cast<Entity*>(targetPtr - 0x58)); // offset 0x58 to get owning Entity
        return;
    }
    UpdateEntity(nullptr);
}