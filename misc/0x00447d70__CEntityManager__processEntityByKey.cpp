// FUNC_NAME: CEntityManager::processEntityByKey
// Address: 0x447d70 (or CEntityManager::processMatchingEntity)
void __thiscall CEntityManager::processEntityByKey(void* this, int* pKey) // pKey is a 128-bit key (4 x 32-bit), likely a GUID
{
    int* piIter;
    int* piChild;
    uint hash = getHash(); // FUN_004209c0 - probably a hash function returning a uint based on context
    int iNode = *(int*)(*(int*)((char*)this + 0x70) + (hash % *(uint*)((char*)this + 0x74)) * 4); // hash bucket lookup

    if (iNode != 0) {
        // Walk the collision chain looking for the node matching pKey
        while (true) {
            int* piNodeContents = (int*)getNodeFromBucket(); // FUN_0043ab10 - returns pointer to node's data area (first 4 ints)
            if (piNodeContents[0] == pKey[0] && piNodeContents[1] == pKey[1] &&
                piNodeContents[2] == pKey[2] && piNodeContents[3] == pKey[3]) {
                break; // found matching node
            }
            iNode = *(int*)(iNode + 0x18); // +0x18 is next pointer in collision chain
            if (iNode == 0) {
                return; // key not found
            }
        }

        // Node found at iNode. Process its attached child list (behaviors/scripts)
        int* piAttachList = *(int**)(iNode + 0x14); // +0x14 is head of attached child linked list
        while (piAttachList != 0) {
            piChild = (int*)piAttachList[4]; // +0x10 is next child pointer (since each child struct has 5 ints? Actually piAttachList[4] is offset 0x10)
            int flags = piAttachList[5]; // +0x14 flags word

            undefined1* puCallTarget;
            if ((flags & 0x8000000) == 0) {
                // Call target is the first dword of the child structure
                puCallTarget = (undefined1*)*piAttachList;
            } else {
                // Child has a custom call target at offset 0x3C (piAttachList+0xF is 0x3C bytes into the struct? Actually piAttachList is int*, +0xF means offset 0x3C)
                int* piCustomTarget = piAttachList + 0xF; // offset 0x3C
                if ((*(unsigned char*)(piAttachList + 0x10) & 2) != 0) { // check byte at +0x40
                    char local_4 = 0;
                    struct {
                        int local_c; // global data pointer
                        int* local_8; // custom target
                    } callParams;
                    callParams.local_c = DAT_012067dc; // some global data
                    callParams.local_8 = piCustomTarget;
                    // Call a method on the custom target's vtable
                    (**(void (__thiscall**)(void*))(*(int*)piCustomTarget + 4))(&callParams);
                }
                puCallTarget = (undefined1*)*piCustomTarget;
            }
            // Call the target with argument 1 (probably a tick count or action)
            (*(void (*)(int))*puCallTarget)(1);
            piAttachList = piChild;
        }
    }
}