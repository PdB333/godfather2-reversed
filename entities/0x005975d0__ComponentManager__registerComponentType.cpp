// FUNC_NAME: ComponentManager::registerComponentType
int ComponentManager::registerComponentType() {
    int componentType = 2;  // +0x00: stack variable representing a type ID or size
    void* manager = *(void**)0x01205590;  // Global EARS manager singleton
    // Virtual function at offset 0x10 (vtable slot 4) – typically "beginComponentRegistration"
    (*(void(__thiscall**)(void*))(*((int*)manager) + 0x10))(manager);
    // Same virtual function variant – "addComponentType" with this+2, componentType pointer, and size=2
    (*(void(__thiscall**)(void*, void*, int))(*((int*)manager) + 0x10))((char*)this + 2, &componentType, 2);
    return 4;  // Returns constant – likely the size of the registered component descriptor
}