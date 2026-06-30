// FUNC_0045fa60: Entity::getSpeed
float __thiscall Entity::getSpeed(void)
{
    float result = 0.0f;
    // +0x218: pointer to a MovementData sub-object
    if (this->movementData != 0) {
        // +0x24 in MovementData: current speed value
        result = this->movementData->speed;
    }
    return result;
}