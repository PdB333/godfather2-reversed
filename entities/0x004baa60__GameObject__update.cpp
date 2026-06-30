// FUNC_NAME: GameObject::update
int* __thiscall GameObject::update(GameObject* this)
{
    // Call virtual function at vtable offset 8 (index 2 – third entry)
    (*(void (__thiscall**)(GameObject*))(*reinterpret_cast<int*>(this) + 8))(this);
    return this;
}