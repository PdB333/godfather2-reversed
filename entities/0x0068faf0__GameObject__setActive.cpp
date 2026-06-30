// FUNC_NAME: GameObject::setActive
void __thiscall GameObject::setActive(GameObject* this, uint param2) {
    // Calls internal setActive with flag 1 (true/active) and the given parameter
    this->SetActiveInternal(1, param2);
    return;
}