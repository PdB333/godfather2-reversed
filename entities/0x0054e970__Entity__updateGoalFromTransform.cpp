// FUNC_NAME: Entity::updateGoalFromTransform
void __thiscall Entity::updateGoalFromTransform(Entity* this, uint goalId) {
    // Dereference chain to get position data:
    // this +0x14: pointer to component container (TransformComponent?)
    TransformComponent* component = *(TransformComponent**)((char*)this + 0x14);
    // component +0x30: pointer to internal transform data (e.g., position matrix)
    TransformData* data = *(TransformData**)((char*)component + 0x30);
    // data +0x18: pointer to position block (Vec3 with extra fields)
    Vec3* worldPos = *(Vec3**)((char*)data + 0x18);
    
    // Read the actual position from offset +0x30 within the position block
    Vec3 goalPosition;
    goalPosition.x = *(float*)((char*)worldPos + 0x30);  // +0x30
    goalPosition.y = *(float*)((char*)worldPos + 0x34);  // +0x34
    goalPosition.z = *(float*)((char*)worldPos + 0x38);  // +0x38

    // Call the goal-setting function (FUN_0054eb70) with the extracted position,
    // the goal ID, and three zero flags (unused).
    FUN_0054eb70(&goalPosition, goalId, 0, 0, 0);
}