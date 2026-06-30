// FUNC_NAME: GameObject::addReference
int GameObject::addReference() {
    int* refCount = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x6038);
    (*refCount)++;
    if (*refCount == 0) {
        *refCount = 1; // Prevent wrap-around to zero (likely overflow protection)
    }
    return *refCount;
}