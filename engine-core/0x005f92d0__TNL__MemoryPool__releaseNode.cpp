// FUNC_NAME: TNL::MemoryPool::releaseNode
// Address: 0x005f92d0
// Role: Deallocates a node from a memory pool list, returning the next node.
// this (EDI): pointer to MemoryPool object
// param_1: pointer to output structure (stores poolObj and nextNode)
// param_2: poolObj - pointer to an object with a free list head at +0x18
// param_3: node being deallocated (must not be the head of the free list)

void __thiscall TNL::MemoryPool::releaseNode(int* outResult, int poolObj, int* node)
{
    int iVar1;
    // Note: EDI contains this, saved as unaff_EDI in the decompilation.
    // We'll use "this" accordingly, but the decompiled code uses unaff_EDI.

    // Assert: poolObj is not null
    if (poolObj == 0) {
        FUN_00b97aea(); // assert
    }

    // Assert: node is not the head of the free list (poolObj + 0x18)
    if (node == *(int**)(poolObj + 0x18)) {
        FUN_00b97aea(); // assert
    }

    iVar1 = *node; // node->next

    // Remove node from its current doubly linked list
    // node->prev->next = node->next
    *(int*)node[1] = iVar1;
    // node->next->prev = node->prev
    *(int*)(*node + 4) = node[1];

    // Free the node memory (vtable offset 4, size 12 bytes)
    (**(code**)(*(int*)this + 4))(node, 0xc); // memory pool deallocator

    // Decrement allocated node count (this+0x1c)
    *(int*)((char*)this + 0x1c) = *(int*)((char*)this + 0x1c) - 1; // unaff_EDI[7]

    // Store output: outResult[0] = poolObj, outResult[1] = node->next
    outResult[1] = iVar1;
    *outResult = poolObj;
    return;
}