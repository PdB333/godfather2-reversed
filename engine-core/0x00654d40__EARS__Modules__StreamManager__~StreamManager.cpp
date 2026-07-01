// FUNC_NAME: EARS::Modules::StreamManager::~StreamManager
void __fastcall EARS::Modules::StreamManager::~StreamManager(StreamManager* this)
{
    int* piVar1;
    int remainingCount;
    int* piVar3;
    undefined4* currentNode;
    undefined4* nextNode;

    remainingCount = this->itemCount; // +0x0C
    this->vtable = &PTR_LAB_00e43130; // vtable for destructor phase

    // Destroy all items in the array at +0x14
    while (remainingCount != 0) {
        destroyStreamItem(this, *(undefined4*)this->itemsArray); // +0x14
        remainingCount = this->itemCount; // +0x0C
    }

    // Notify global singleton managers of destruction
    if (g_someSingleton != (int*)0x0) {
        (**(code**)(*g_someSingleton + 0x70))(1);
    }
    if (g_otherSingleton != (int*)0x0) {
        (**(code**)(*g_otherSingleton + 0x0C))();
    }
    g_otherSingleton = (int*)0x0;

    shutdownGlobalStreamManager();

    // Close and delete handles
    if (this->handleA != 0) { // +0x54
        closeHandle();
        deleteHandle(this->handleA);
    }
    if (this->handleB != 0) { // +0x58
        closeHandle();
        deleteHandle(this->handleB);
    }

    // Decrement reference counts for two smart pointer objects
    piVar3 = (int*)this->refCountObjB; // +0x34
    if (piVar3 != (int*)0x0) {
        piVar1 = piVar3 + 2;
        *piVar1 = *piVar1 - 1;
        if (*piVar1 == 0) {
            (**(code**)(*piVar3 + 8))(); // release
        }
    }
    piVar3 = (int*)this->refCountObjA; // +0x30
    if (piVar3 != (int*)0x0) {
        piVar1 = piVar3 + 2;
        *piVar1 = *piVar1 - 1;
        if (*piVar1 == 0) {
            (**(code**)(*piVar3 + 8))(); // release
        }
    }

    // Free dynamically allocated buffers
    free(this->bufferC); // +0x2C
    free(this->bufferB); // +0x20
    free(this->bufferA); // +0x14 (actually itemsArray, already processed)

    this->vtable = &PTR_LAB_00e42de4; // switch to base vtable

    // Clear linked list of nodes (starting at +0x04)
    currentNode = (undefined4*)this->linkedListHead; // +0x04
    while (currentNode != (undefined4*)0x0) {
        nextNode = (undefined4*)currentNode[2]; // next pointer
        *currentNode = 0;
        currentNode[1] = 0;
        currentNode[2] = 0;
        currentNode = nextNode;
    }
    return;
}