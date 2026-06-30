// FUNC_NAME: RenderObjectList::processActiveNodes
void __thiscall RenderObjectList::processActiveNodes() {
    // this->+0x10: pointer to a NodeList container (or an iterator)
    NodeList* list = *(NodeList**)((char*)this + 0x10);
    if (list != nullptr) {
        // list->+0x20: head of the list (or current node pointer)
        Node* currentNode = *(Node**)((char*)list + 0x20);
        while (currentNode != nullptr) {
            // list->+0x1c: pointer to sentinel or some internal structure
            // Dereference to get the first actual node
            Node* node = *(Node**)*(void**)((char*)list + 0x1c);
            // Safety check: if node is the sentinel, assert (empty list)
            if (node == *(Node**)(*(void**)((char*)list + 0x1c))) {
                FUN_00b97aea(); // likely assertion failure
            }
            // Check bit 0 of node's flags (node+0x8)
            if ((*(unsigned char*)((char*)node + 8) & 1) != 0) {
                // Another sentinel check (maybe strict mode)
                if (node == *(Node**)(*(void**)((char*)list + 0x1c))) {
                    FUN_00b97aea();
                }
                // Call virtual function at vtable index 1 on this->vtable (this+0x4)
                // with argument 0 on the object stored at node+0x10 (node[4])
                (**(code**)(**(int**)((char*)this + 4) + 4))(*(void**)((char*)node + 0x10), 0);
            }
            // Process the node via helper function (likely advances iterator)
            FUN_006217f0(*(undefined4*)((char*)this + 0x10), localBuffer, list, node);
            // Refresh list pointer (may have changed during processing)
            list = *(NodeList**)((char*)this + 0x10);
            currentNode = *(Node**)((char*)list + 0x20);
        }
    }
}