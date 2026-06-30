// FUN_NAME: NetConnection::synchronizeGhostLists
void NetConnection::synchronizeGhostLists()
{
    // param_1 is 'this' (NetConnection*)
    int *thisObj = this; // not needed but clarity
    // Virtual call at vtable+0x5c - likely a check/isReady?
    if ((this != 0) && (*(code *)(*(int *)this + 0x5c))() != 0) {
        // Virtual call at vtable+0x08 - get reference list (e.g., remoteGhostList)
        int *remoteList = (int *)(*(code *)(*(int *)this + 8))();
        // Virtual call at vtable+0x20 - get item count
        uint count = (*(code *)(*(int *)this + 0x20))();
        uint idx = 0;
        if (count != 0) {
            do {
                // Virtual call at vtable+0x24 - get item by index
                int *localItem = (int *)(*(code *)(*(int *)this + 0x24))(idx);
                int localId = (*(code *)(*localItem + 0xc))();   // virtual offset 0xc: item ID
                int remoteId = (*(code *)(*remoteList + 0xc))(); // virtual offset 0xc: reference ID

                if (localId != remoteId) {
                    int idCopy = localId;
                    // Probably pack the ID into network format
                    packGhostId(&idCopy);   // FUN_0065dda0
                    if (ghostNeedsUpdate == 0) { // iStack_10 == 0 (uninitialized? - representing a condition)
                        idCopy = localId;
                        unpackGhostId(buffer, &idCopy); // FUN_0065de00
                        idCopy = localId;
                        packGhostId(&idCopy); // FUN_0065dda0 again

                        // Allocate new ghost update object (size 0x10)
                        int *newUpdate = (int *)operatorNew(0x10); // FUN_009c8e50
                        if (newUpdate != 0) {
                            int *updateData = constructGhostUpdate(); // FUN_0065dc50
                            newUpdate[1] = (int)updateData; // offset +0x04
                            // Note: iStack_c is missing; likely the newUpdate pointer itself was supposed to be stored somewhere (e.g., in a list)
                            // The decompiler omitted assignment; we assume it's stored in a field or added to a list.
                        }
                    }
                }
                idx++;
            } while (idx < count);
        }
    }
}