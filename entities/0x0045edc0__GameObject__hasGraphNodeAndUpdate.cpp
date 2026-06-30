// FUNC_NAME: GameObject::hasGraphNodeAndUpdate

bool __thiscall GameObject::hasGraphNodeAndUpdate(GameObject* this, int param)
{
    bool hasNode = *(int*)(this + 0x218) != 0;  // graphNodePtr at +0x218
    if (hasNode) {
        FUN_00572c50(param);  // update/render call on graph node
    }
    return hasNode;
}