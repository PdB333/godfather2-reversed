// FUNC_NAME: EARSNode::setupNode
// Address: 0x005fc4a0
// Initializes a node, optionally attaching a resource handle.
// Uses a local buffer to store the this pointer and the resource handle.

class EARSNode {
public:
    // vtable layout:
    // +0: (unknown)
    // +4: void __thiscall attachResource(void* resource, int flag)
    // +8: void __thiscall preInit()
    // +12: void __thiscall postInit()
};

// Helper: function at 0x004265d0 (likely creates a resource handle)
extern int __stdcall ResourceManager_createHandle(void* resource, int* base);

void __thiscall EARSNode::setupNode(void* this, void* resource) {
    int localBuffer[2];         // temporary stack storage
    int* base = localBuffer;    // unaff_EDI in Ghidra

    // Store this pointer in the buffer
    base[0] = (int)this;

    // Call pre-initialize vtable+8
    (*(void (__thiscall**)(void*))(*(int*)this + 8))();

    if (resource != 0) {
        // Obtain and store resource handle (vtable+4 expects resource and flag=0)
        int handle = ResourceManager_createHandle(resource, base);
        base[1] = handle;

        // Attach resource to node
        (*(void (__thiscall**)(void*, void*, int))(*(int*)this + 4))(this, resource, 0);

        // Finalize initialization
        (*(void (__thiscall**)(void*))(*(int*)this + 12))();
    } else {
        // No resource: clear handle
        base[1] = 0;

        // Finalize initialization
        (*(void (__thiscall**)(void*))(*(int*)this + 12))();
    }
}