// FUNC_NAME: SimEntity::orphanFromSystem
void SimEntity::orphanFromSystem(int entity) {
    int iVar1 = DAT_01205968;
    SimSystem::orphanEntity(entity);
    if (*(int *)(iVar1 + 0x814) == 0) {
        SimSystem::updateClients(entity); // or similar notification function
    }
    // Remove from doubly-linked list: prev->next = next
    if (*(undefined4 **)(entity + 0x40) != (undefined4 *)0x0) {
        **(undefined4 **)(entity + 0x40) = *(undefined4 *)(entity + 0x3c);
    }
    // Remove from doubly-linked list: next->prev = prev
    if (*(int *)(entity + 0x3c) != 0) {
        *(undefined4 *)(*(int *)(entity + 0x3c) + 0x40) = *(undefined4 *)(entity + 0x40);
    }
    // Null out links and set to orphaned state
    *(undefined4 *)(entity + 0x3c) = 0; // +0x3C prev pointer
    *(undefined4 *)(entity + 0x40) = 0; // +0x40 next pointer
    *(undefined4 *)(entity + 0x30) = 0; // +0x30 parent/container pointer or flag
    return;
}