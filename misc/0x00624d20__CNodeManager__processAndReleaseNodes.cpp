// FUNC_NAME: CNodeManager::processAndReleaseNodes
void __fastcall CNodeManager::processAndReleaseNodes(int* thisPtr)
{
    int* node = (int*)thisPtr[8]; // +0x20: head of linked list
    while (node != nullptr) {
        // Recursive processing (possibly a bug in decompilation; suspected to be a different function)
        // FUN_00624d20();
        (**(code**)(*thisPtr + 0x1c))(node); // vtable[0x1c] – processNode or similar

        if (!(*(byte*)(node + 5) & 1)) { // node->flags & FLAG_DELAYED_RELEASE
            (**(code**)(*node + 4))(1); // vtable[4] – release(1) or delete
        } else {
            node[5] |= 2; // set FLAG_PENDING_DELETE
        }
        node = (int*)thisPtr[8]; // reset to head (assumes head updated by vcall)
    }
}