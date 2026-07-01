// FUNC_NAME: GameObject::removeFromActiveList
void GameObject::removeFromActiveList(GameObject* obj)
{
    // Check if the object is currently active/valid via helper function
    if (FUN_008f6ed0(obj)) {
        // Remove the object from the global active list.
        // obj + 0x3c likely contains a pointer to the list node or manager reference.
        if (obj != nullptr) {
            removeFromList(&g_activeListHead, obj + 0x3c, 0);
        } else {
            removeFromList(&g_activeListHead, nullptr, 0);
        }
    }
}