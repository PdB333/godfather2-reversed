// Xbox PDB: EARS_Apt_UIPauseMap_SetPlayerEffect
//FUNC_NAME: Player::loadPlayerData
void __thiscall Player::loadPlayerData(int this, char forceReload) {
    // +0xf4: pointer to head of intrusive linked list of player data nodes
    int* pListHead = (int*)(this + 0xf4);
    
    // Acquire mutex or critical section (EARS synchronization)
    lockMutex();
    
    if (forceReload) {
        int selectedValue;
        // +0x14c: state/version field (1 or >4 selects one path, else other)
        int state = *(int*)(this + 0x14c);
        if (state == 1 || state > 4) {
            // +0x140: primary data identifier
            selectedValue = *(int*)(this + 0x140);
        } else {
            // +0x144: secondary data identifier
            selectedValue = *(int*)(this + 0x144);
        }
        
        // +0x148: expected identifier to match
        if (selectedValue == *(int*)(this + 0x148)) {
            // Generate a unique ID or timestamp for this data
            int uniqueId = getUniqueId();
            
            // Format the ID into a string buffer (76 bytes)
            char formattedId[76];
            formatString(formattedId, uniqueId);
            
            // Log or set debug variable "dv_player"
            debugPrint("dv_player");
            
            // Allocate a new player data node (size 0x2ff, alignment 4, flags 0, tag 0xffffffff)
            int newNode = allocateObject(&local_64, local_60, formattedId, 0x2ff, 4, 0, 0xffffffff, 0);
            
            // If there was an existing head, detach it (set its next pointer to null)
            if (*pListHead != 0) {
                *(int*)(*pListHead + 8) = 0;  // +8: next pointer in node
                *pListHead = 0;
            }
            
            // Insert new node at head of list
            *pListHead = newNode;
            if (newNode != 0) {
                // Set the node's next pointer to point back to the list head pointer
                *(int**)(newNode + 8) = pListHead;
            }
        }
    }
    // Implicit unlock (likely handled by lockMutex or caller)
}