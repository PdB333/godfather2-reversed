// FUNC_NAME: GameObject::removeFromManager
// Address: 0x00428d00
// Role: Removes this game object from its type's object list in the global ObjectManager.
//        Uses a lookup table (0x80 entries, 0x18 bytes each) to map object->typeID to a TypeList.
//        Removes by swapping with the last element in the TypeList's dynamic array.

void GameObject::removeFromManager()
{
    // Global ObjectManager singleton. Layout:
    // [0x0000..0x2FFF] TypeList array (0x80 entries, each 0x60 bytes)
    // [0x0040..0x0FFF] LookupTable (0x80 entries, each 0x18 bytes)
    // TypeList structure (0x60 bytes):
    //   +0x48: ObjectNode* pNodes  (dynamic array of ObjectNode, each 0x50 bytes)
    //   +0x4c: int nodeCount
    // ObjectNode structure (0x50 bytes):
    //   +0x40: int pObject  (pointer to the actual GameObject, compared to 'this')
    ObjectManager* pMgr = g_pObjectManager;
    LookupEntry* pLookup = (LookupEntry*)((int)pMgr + 0x40);
    int typeIdx = 0;

    do {
        // Match object's type ID (offset 0xB4) against lookup table entry
        if (pLookup->typeId == *(int*)((int)this + 0xB4)) {
            // Index into TypeList array (each 0x60 bytes)
            TypeList* pTypeList = (TypeList*)((int)pMgr + typeIdx * 0x60);
            if (pTypeList != nullptr) {
                int nodeCount = *(int*)((int)pTypeList + 0x4C);
                if (nodeCount != 0) {
                    int* pObjectField = (int*)(*(int*)((int)pTypeList + 0x48) + 0x40);
                    int objIdx = 0;
                    // Linear search for this object's pointer in the node array
                    while (*pObjectField != (int)this) {
                        objIdx++;
                        pObjectField += 0x14; // advance 0x14 ints = 0x50 bytes per node
                        if (nodeCount <= objIdx) {
                            return;
                        }
                    }
                    // If not the last element, overwrite with the last element
                    if (objIdx != nodeCount - 1) {
                        ObjectNode* pLast = (ObjectNode*)((int)pTypeList->pNodes + (nodeCount - 1) * 0x50);
                        ObjectNode* pTarget = (ObjectNode*)((int)pTypeList->pNodes + objIdx * 0x50);
                        // Copy the last node over the removed slot (size 0x50 = 0x14 dwords)
                        for (int i = 0x14; i != 0; i--) {
                            *(int*)pTarget = *(int*)pLast;
                            pLast = (ObjectNode*)((int)pLast + 4);
                            pTarget = (ObjectNode*)((int)pTarget + 4);
                        }
                    }
                    // Decrement count
                    pTypeList->nodeCount--;
                }
            }
            return;
        }
        typeIdx++;
        pLookup = (LookupEntry*)((int)pLookup + 0x18);
    } while (typeIdx < 0x80);
}