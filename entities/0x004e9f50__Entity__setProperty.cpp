// FUNC_NAME: Entity::setProperty
// Address: 0x004e9f50
// Role: Sets a property value on an entity. The second parameter type determines the property type;
// if type is 2, the value is interpreted as a boolean and applied accordingly via an internal helper.

void __thiscall Entity::setProperty(int value, int type) {
    // The internal function applyProperty receives the value and a boolean flag indicating
    // whether type equals 2 (likely a specific property category).
    Entity::applyProperty(value, type == 2);
}