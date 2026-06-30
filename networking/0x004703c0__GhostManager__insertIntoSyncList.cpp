// FUNC_NAME: GhostManager::insertIntoSyncList
// Address: 0x004703c0
// This function inserts a ghost object from this->pendingGhost (offset +0x130) into a global doubly-linked list
// and serializes 64 bytes from this+0x90 into a packet buffer (g_packetBuffer at 0x1206880).
// Finally it calls a virtual method at vtable offset 0x28 on the object at this+0x58 with argument 2.

void __fastcall GhostManager::insertIntoSyncList(int this)
{
    int objectToInsert; // ghost object pointer from field at +0x130
    int oldTail;
    int *writePtr;

    objectToInsert = *(int *)(this + 0x130); // this->pendingGhost
    if (objectToInsert != 0) {
        helper_004a6a80(0); // unknown initialization (possibly memory manager)

        if (g_ghostListHead != 0) {
            // Insert at head: set current head's prev to new object
            *(int *)(g_ghostListHead + 0x90) = objectToInsert; // head->prev = new
            oldTail = g_ghostListTail;
        } else {
            oldTail = objectToInsert; // first element: tail = new
        }
        g_ghostListTail = oldTail;
        *(int *)(objectToInsert + 0x8C) = g_ghostListHead; // new->next = head
        *(int *)(objectToInsert + 0x90) = 0;                // new->prev = NULL
        g_ghostListHead = objectToInsert;
    }

    if (*(int *)(this + 0x164) != 0) { // this->needsSerialization flag?
        writePtr = (int *)(g_packetBuffer + 0x14); // pointer into packet buffer
        // Write vtable/type marker
        **(int **)(g_packetBuffer + 0x14) = (int)&g_packetVtable; // PTR_LAB_0110ba6c
        *writePtr = *writePtr + 4;
        // Write address of a field (this+0x54)
        *(int *)*writePtr = this + 0x54;
        // Align to 16 bytes and copy 64 bytes from this+0x90
        void *dst = (void *)((*writePtr + 0x13) & 0xFFFFFFF0);
        *writePtr = (int)dst;
        memcpy(dst, (void *)(this + 0x90), 0x40); // copy 64 bytes (DWORDs?)
        *writePtr = *writePtr + 0x40;
    }

    // Call virtual function on sub-object (vtable at this+0x58)
    (*(void (__stdcall **)(int))(*(int *)(this + 0x58) + 0x28))(2);
}