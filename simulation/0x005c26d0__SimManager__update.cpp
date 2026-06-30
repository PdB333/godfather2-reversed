// FUNC_NAME: SimManager::update
void SimManager::update(void)
{
    // +0x00: vtable pointer (base class)
    // +0x04: ... (inherited fields)
    // Call base class update (ProcessManager::update or similar)
    baseUpdate(this);

    // Lazy initialization of the singleton instance (size 0xC8 = 200)
    if (gSingleton == 0) {
        void* mem = operatorNew(200, 0);  // Could be __nw__FUiUi or similar
        if (mem == 0) {
            gSingleton = 0;
        } else {
            // Call constructor / init on the allocated memory
            gSingleton = singletonInit(mem);  // Returns a pointer to the singleton
        }
        singletonPostInit();
    }

    // Get the current active simulation object (returns pointer to a SimObject subset at offset +0x10?)
    SimObject* obj = getActiveSimObject(this);
    if (obj != 0) {
        // obj is actually a pointer to a subobject at offset +0x10 from the actual SimObject
        // The actual SimObject base (with vtable) is at obj - 0x10
        // Call virtual function at vtable+0x28 (e.g., process or update)
        (**(code **)(*(int *)((char*)obj - 0x10) + 0x28))();
        return;
    }
    // No active object – call the default function on a global default object (if any)
    SimObject* defaultObj = gDefaultSimObject;  // Hypothetical global
    if (defaultObj != 0) {
        (**(code **)(*(int*)defaultObj + 0x28))();
    }
}