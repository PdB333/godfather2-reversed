// FUNC_NAME: SimManager::destructor
void __fastcall SimManager::destructor(SimManager* this)
{
    int* piVar1;
    int count;
    int* piVar3;
    undefined4* node;
    undefined4* nextNode;

    count = this->field_0x0c; // +0x0c: count of items in list at +0x14
    this->vtable = &SimManager_vtable_0; // +0x00: set to base vtable

    // Process all items in the list at +0x14
    while (count != 0) {
        SimManager::removeItem(this, *(undefined4*)this->field_0x14); // +0x14: list of items
        count = this->field_0x0c;
    }

    // Notify global singleton if present
    if (g_GlobalSingleton1 != (int*)0x0) {
        (**(code**)(*g_GlobalSingleton1 + 0x70))(1);
    }

    // Notify another global singleton
    if (g_GlobalSingleton2 != (int*)0x0) {
        (**(code**)(*g_GlobalSingleton2 + 0x0c))();
    }
    g_GlobalSingleton2 = (int*)0x0;

    // Global cleanup
    SimManager::globalShutdown();

    // Release two stream resources at +0x54 and +0x58
    if (this->field_0x54 != 0) {
        StreamManager::closeStream();
        StreamManager::deleteStream(this->field_0x54);
    }
    if (this->field_0x58 != 0) {
        StreamManager::closeStream();
        StreamManager::deleteStream(this->field_0x58);
    }

    // Decrement reference counts on two objects at +0x34 and +0x30
    piVar3 = (int*)this->field_0x34; // +0x34: ref-counted object
    if (piVar3 != (int*)0x0) {
        piVar1 = piVar3 + 2; // ref count at offset +8
        *piVar1 = *piVar1 - 1;
        if (*piVar1 == 0) {
            (**(code**)(*piVar3 + 8))(); // call destructor via vtable
        }
    }
    piVar3 = (int*)this->field_0x30; // +0x30: another ref-counted object
    if (piVar3 != (int*)0x0) {
        piVar1 = piVar3 + 2;
        *piVar1 = *piVar1 - 1;
        if (*piVar1 == 0) {
            (**(code**)(*piVar3 + 8))();
        }
    }

    // Free dynamically allocated buffers
    free(this->field_0x2c); // +0x2c: buffer
    free(this->field_0x20); // +0x20: buffer
    free(this->field_0x14); // +0x14: list buffer

    // Switch vtable to derived class vtable
    this->vtable = &SimManager_vtable_1;

    // Clear linked list at +0x04
    node = (undefined4*)this->field_0x04; // +0x04: linked list head
    while (node != (undefined4*)0x0) {
        nextNode = (undefined4*)node[2]; // next pointer at offset +8
        node[0] = 0; // clear data
        node[1] = 0;
        node[2] = 0;
        node = nextNode;
    }

    return;
}