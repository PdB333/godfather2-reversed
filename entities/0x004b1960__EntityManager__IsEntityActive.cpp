// FUNC_NAME: EntityManager::IsEntityActive

// Global singleton pointer to the entity manager
extern EntityManager* g_pEntityManager; // at 0x01223510

// Virtual method table layout (simplified)
struct EntityManagerVTable {
    // ... other virtual methods at offsets 0x00, 0x04, ... 
    // Offset 0x38 corresponds to method index 14 (0x38 / 4)
    bool (__thiscall *IsActive)(EntityManager* this, int entityId); // returns bool
};

// EntityManager class definition (partial)
struct EntityManager {
    EntityManagerVTable* vtable; // offset 0x00
    // ... other members
};

// Standalone wrapper function that delegates to the virtual method
bool EntityManager::IsEntityActive(int entityId) {
    // Call virtual method at vtable offset 0x38
    EntityManager* mgr = g_pEntityManager;
    bool result = mgr->vtable->IsActive(mgr, entityId);
    return result;
}