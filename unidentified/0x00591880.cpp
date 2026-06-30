// FUN_00591880: DialogTree::processNode
// Processes a dialog tree node: dispatches to type-specific handler based on node type (low 6 bits of first byte),
// then recursively processes child nodes stored at offset 0xC.
// nodeData: pointer to byte array describing the node
// context: opaque context pointer (e.g., DialogContext*)
void DialogTree::processNode(void* nodeData, void* context) {
    uint8_t* node = (uint8_t*)nodeData;
    uint8_t nodeType = node[0] & 0x3F; // Type field in low 6 bits
    if (nodeType < 0x23) { // Only 35 known node types
        // Dispatch table at 0x0103b0e0 holds per-type handler function pointers
        void (**handler)(DialogTree*, uint8_t*, void*) = (void (**)(DialogTree*, uint8_t*, void*))(&DAT_0103b0e0);
        if (handler[nodeType] != nullptr) {
            handler[nodeType](this, node, context);
        }
    }
    int8_t childCount = (int8_t)node[1]; // Number of child nodes (signed byte, non-negative)
    if (childCount > 0) {
        // Child node pointers start at offset 0xC (12 bytes) into the node data
        uint8_t** children = (uint8_t**)(node + 0xC);
        for (int8_t i = 0; i < childCount; i++) {
            processNode(children[i], context);
        }
    }
}