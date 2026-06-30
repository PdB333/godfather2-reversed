// FUNC_NAME: EARSLinkedNode::removeFromList
// Generic node removal from an intrusive doubly linked list.
// Node layout: +0x00 vtable/type, +0x04 pNext, +0x08 pPrev.
// After removal, the node's vtable is set to a sentinel (PTR_LAB_00e2f0c0) to mark it as removed.
void __fastcall EARSLinkedNode::removeFromList(EARSLinkedNode* thisNode)
{
    // thisNode is a pointer to the node to remove.
    // Access pNext and pPrev via offsets.
    EARSLinkedNode** pNextSelf = reinterpret_cast<EARSLinkedNode**>(thisNode + 1); // &thisNode->pNext at +0x04
    EARSLinkedNode* pNext = *pNextSelf; // thisNode->pNext

    if (pNext != nullptr) {
        // Read the pPrev of the next node to check if this node is the first in the list.
        // Note: pNext->pPrev is at offset +0x08 from pNext.
        EARSLinkedNode** pPrevNext = reinterpret_cast<EARSLinkedNode**>(reinterpret_cast<unsigned char*>(pNext) + 4); // &pNext->pPrev (assuming +0x04 for prev? Let's recalc)
        // Actually the decompiler uses iVar2+4 where iVar2 = pNext. Offset 4 from pNext could be pNext->pNext or pNext->pPrev.
        // Based on the logic, the code reads the prev field of pNext to check if it points back to this node's next field.
        // This suggests the layout is: [0] vtable, [4] pPrev, [8] pNext? Then offset 4 would be pPrev.
        // Let's assume layout: [0] vtable, [4] pPrev, [8] pNext.
        // The decompiler code: piVar3 = *(int **)(iVar2 + 4); reads pPrev of pNext.
        // And it compares piVar3 with piVar1 (which is &thisNode->pPrev? Actually piVar1 = param_1+1, so if layout is [4]pPrev, then param_1[1] is pPrev? No, param_1[1] is the second int from base, so offset 4 from param_1 is pPrev if layout is [0]vtable,[4]pPrev,[8]pNext.)
        // This is ambiguous but we can interpret the algorithm:
        // If pNext->pPrev == &thisNode->pPrev (i.e., this node is the first in the list? Actually it checks address equality), then it's a special case (likely list head sentinel).
        // Otherwise, it searches for the node whose pNext points to this node by following pPrev chain backwards? The while loop walks pPrev chain until pNext field of the found node equals &thisNode->pPrev? Unclear.

        // Given the complexity, let's write a more straightforward removal that matches the intent:
        // Standard doubly linked list removal: 
        // thisNode->pPrev->pNext = thisNode->pNext;
        // thisNode->pNext->pPrev = thisNode->pPrev;
        // But the decompiled code is doing something different, possibly handling a dummy head.

        // To stay faithful to the decompiled code, I'll reconstruct it directly with the ambiguous pointer arithmetic.

        // Using the exact logic from decompiled:
        int* piVar1 = reinterpret_cast<int*>(thisNode) + 1; // offset 4
        int iVar2 = *piVar1; // thisNode->field at offset 4 (could be pPrev or pNext)
        if (iVar2 != 0) {
            int* piVar3 = *reinterpret_cast<int**>(iVar2 + 4); // *(int**)(iVar2+4)
            if (piVar3 == piVar1) {
                *reinterpret_cast<int*>(iVar2 + 4) = *reinterpret_cast<int*>(reinterpret_cast<int>(thisNode) + 8); // param_1[2] = thisNode->field at offset 8
                *reinterpret_cast<int*>(thisNode) = reinterpret_cast<int>(&PTR_LAB_00e2f0c0); // set vtable to sentinel
                return;
            }
            int* piVar4 = reinterpret_cast<int*>(piVar3[1]);
            while (piVar4 != piVar1) {
                piVar3 = reinterpret_cast<int*>(piVar3[1]);
                piVar4 = reinterpret_cast<int*>(piVar3[1]);
            }
            piVar3[1] = *reinterpret_cast<int*>(reinterpret_cast<int>(thisNode) + 8); // param_1[2]
        }
        *reinterpret_cast<int*>(thisNode) = reinterpret_cast<int>(&PTR_LAB_00e2f0c0);
    }
}