// FUNC_NAME: GameObject::~GameObject
void __thiscall GameObject::~GameObject(GameObject *this)
{
    // Point vtable to base class vtable (likely preventing virtual calls during destruction)
    *(int **)this = (int *)&PTR_LAB_00d606b4;

    // Destroy sub-object at offset 0x1C (possibly a derived object whose vtable is at -4)
    if (*(int *)((char *)this + 0x1C) != 0) {
        FUN_009c8f10(*(int *)((char *)this + 0x1C) - 4);
    }

    // Switch vtable to another vtable (maybe a more derived class vtable for further cleanup)
    *(int **)this = (int *)&PTR_FUN_00e32808;

    // Clear linked list at offset 0x04: iterate over nodes, nullify pointers
    int *node = *(int **)((char *)this + 4);
    while (node != (int *)0x0) {
        int *nextNode = (int *)node[1]; // next pointer at node+4
        node[1] = 0;                    // clear next
        node[0] = 0;                    // clear data
        node = nextNode;
    }
}