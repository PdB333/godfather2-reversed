// FUNC_NAME: GeometryData::copyToPropertySlot

// __thiscall, param_1 = this, param_2 = PropertySlot*
void __thiscall GeometryData::copyToPropertySlot(PropertySlot* pSlot) {
    // Get type identifier from slot's vtable
    typedef int (__thiscall *GetHashFn)(void*);
    int hash = ((GetHashFn)(*(int*)pSlot))(pSlot);

    if (hash == 0x1b2d5c51) {
        // Copy geometry vertex buffer type data

        // this->pNodeData at offset +0x68 (points into a linked list node)
        int* pNodeData = *(int**)((char*)this + 0x68);
        int* pNode;
        if (pNodeData == 0) {
            pNode = 0;
        } else {
            // Node base is 0x48 (72) bytes before the data pointer
            pNode = (int*)((char*)pNodeData - 0x48);
        }

        // Geometry list head pointer in the slot at offset +0x64 (pSlot[0x19])
        int** ppGeometryHead = (int**)((int*)pSlot + 0x19);
        int* pOldHead = *ppGeometryHead;

        if (pOldHead != pNode) {
            // Release the previous head node
            if (pOldHead != 0) {
                releaseGeometryNode((int)pOldHead);  // FUN_004daf90
            }

            *ppGeometryHead = pNode;

            if (pNode != 0) {
                // Save old back pointer (stored at node+4) into slot field at +0x68 (pSlot[0x1a])
                int oldBackPtr = pNode[1]; // node[1] is at offset 4
                *(int*)((int*)pSlot + 0x1a) = oldBackPtr;

                // Set node's back pointer to the address of the geometry head
                pNode[1] = (int)ppGeometryHead;
            }
        }

        // Copy field at this+0x78 to slot field at +0x78 (pSlot[0x1e])
        *(int*)((int*)pSlot + 0x1e) = *(int*)((char*)this + 0x78);

    } else if (hash == 0x211bc9c1) {
        // Copy other type data (possibly material or transform)

        // Copy three fields from this to slot:
        // this+0x74 -> slot+0x70 (pSlot[0x1c])
        // this+0x78 -> slot+0x78 (pSlot[0x1e])
        // this+0x70 -> slot+0x80 (pSlot[0x20])
        *(int*)((int*)pSlot + 0x1c) = *(int*)((char*)this + 0x74);
        *(int*)((int*)pSlot + 0x1e) = *(int*)((char*)this + 0x78);
        *(int*)((int*)pSlot + 0x20) = *(int*)((char*)this + 0x70);
    }
}