// FUNC_NAME: SimManager::updateAll
// Address: 0x005313a0
// Iterates a global linked list of SimObjects, calling their update method.

#include <cstdint>

// Forward declaration of SimObject update function
void SimObject_update(SimObject* obj);

// Global head of SimObject linked list
static SimObject* g_SimObjectListHead = nullptr; // DAT_01194a6c

void SimManager::updateAll()
{
    SimObject* current = g_SimObjectListHead; // iVar1
    while (current != nullptr)
    {
        SimObject_update(current); // calls FUN_005326c0
        current = current->next;   // offset +0x10: pointer to next object in list
    }
}