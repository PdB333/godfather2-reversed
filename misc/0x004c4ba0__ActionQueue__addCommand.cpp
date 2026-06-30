// FUNC_NAME: ActionQueue::addCommand
// Address: 0x004c4ba0
// Role: Inserts a new command into the action queue buffer, optionally linking it for immediate processing.

class ActionQueue {
public:
    // Offsets: (relative to 'this')
    // +0x10: m_pCommands (Base pointer to an array of CommandEntry, each 0x20 bytes)
    // +0x34: m_capacity (Max number of entries in the buffer)
    // +0x38: m_count (Current number of entries)
    // +0x18: m_bFlag (Flag byte, set to 0 on insertion)
    // +0x3c: m_bProcessImmediately (If non-zero, invokes post-insertion linking)
    // +0x24: m_pLinkBase (Base for linking new entries into a chain)
    
    void addCommand(uint param1, uint param2, uint param3, uint param4) {
        int count = *(int*)((int)this + 0x38);
        int capacity = *(int*)((int)this + 0x34);
        
        if (count < capacity) {
            // Update count and clear flag
            *(int*)((int)this + 0x38) = count + 1;
            *(char*)((int)this + 0x18) = 0;
            
            int entryOffset = count * 0x20; // Each entry is 0x20 bytes
            uint* pCommands = *(uint**)((int)this + 0x10);
            
            // Generate a unique ID and store it at the beginning of the entry
            uint newId = generateUniqueId(param1); // FUN_004c4a10
            pCommands[entryOffset / sizeof(uint)] = newId;
            
            // Copy the remaining command parameters into the entry
            copyCommandEntry(count, param1, param4, param2, param3); // FUN_004c4cb0
            
            // Optional immediate linking
            if (*(char*)((int)this + 0x3c) != 0) {
                uint commandPtr = *(uint*)((int)this + 0x10);
                uint entryAddr = commandPtr + entryOffset;
                
                int link1 = getLinkedListNode(*(uint*)entryAddr, (int)this + 0x24); // FUN_004c4610
                int link2 = getLinkedListNode(*(uint*)(entryAddr + 4), link1 + 0xC); // FUN_004c4610
                linkCommand(this, link2 + 0xC); // FUN_004c4730
            }
        }
    }
    
private:
    // Stub declarations for called functions
    uint generateUniqueId(uint input);    // FUN_004c4a10
    void copyCommandEntry(int index, uint a, uint b, uint c, uint d); // FUN_004c4cb0
    int getLinkedListNode(uint key, int base); // FUN_004c4610
    void linkCommand(ActionQueue* queue, int node); // FUN_004c4730
};