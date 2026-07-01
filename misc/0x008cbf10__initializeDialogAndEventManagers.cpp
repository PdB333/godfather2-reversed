// FUNC_NAME: initializeDialogAndEventManagers
// Address: 0x008cbf10
// Role: Initialize global DialogTreeManager and EventScheduler instances, then register the same event callback with two different subsystems.

// Known EA EARS subsystem: DialogTreeManager, EventScheduler
// Allocator: operator new with size 0x1f54 (possibly sizeof(DialogTreeManager) == sizeof(EventScheduler) == 8020 bytes)
// Callback at 0x008cb230 is likely DialogTreeManager::onEvent or EventScheduler::onEvent

extern void* __cdecl operatorNew(uint32_t size);                               // FUN_009c8e50
extern DialogTreeManager* __cdecl DialogTreeManager::Create();                  // FUN_008cb910
extern EventScheduler* __cdecl EventScheduler::Create();                        // FUN_008cbbf0
extern void* __cdecl CreateEventConnection(void* callback);                     // FUN_004b5d30
extern void* __cdecl CreateEventConnectionAlt(void* callback);                  // FUN_008cc210
extern void __cdecl SubscribeToEvent(void* connection, void* callback);         // FUN_00442d90

// Globals
DialogTreeManager* g_pDialogTreeManager = nullptr;  // DAT_0112f970
EventScheduler* g_pEventScheduler = nullptr;         // DAT_0112f974

void initializeDialogAndEventManagers() {
    // 1. Create DialogTreeManager
    void* mem = operatorNew(0x1f54);
    if (mem != nullptr) {
        g_pDialogTreeManager = DialogTreeManager::Create();
    } else {
        g_pDialogTreeManager = nullptr;
    }

    // 2. Create EventScheduler
    mem = operatorNew(0x1f54);
    if (mem != nullptr) {
        g_pEventScheduler = EventScheduler::Create();
    } else {
        g_pEventScheduler = nullptr;
    }

    // 3. Register the same callback with two different event systems
    void (*eventCallback)() = reinterpret_cast<void(*)()>(0x008cb230);   // known event handler
    void* connection = CreateEventConnection(eventCallback);              // first system registration
    SubscribeToEvent(connection, eventCallback);

    connection = CreateEventConnectionAlt(eventCallback);                 // second system registration
    SubscribeToEvent(connection, eventCallback);
}