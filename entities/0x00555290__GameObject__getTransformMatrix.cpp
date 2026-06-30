// FUNC_NAME: GameObject::getTransformMatrix

int __fastcall GameObject::getTransformMatrix(GameObject* this)
{
    // Offset 0x30: pointer to internal structure (e.g., RenderTransform)
    // Offset 0x18 from that structure: pointer to matrix data
    // Then add 0x30 to get the final matrix pointer (offset into data)
    return *(int*)(*(int*)((char*)this + 0x30) + 0x18) + 0x30;
}