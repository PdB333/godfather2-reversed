// FUNC_NAME: EARSObject::release
// Address: 0x00648460
// Role: Releases the object if it is still alive or if a forced delete is requested and pending destroy flag is set.
// If a custom destructor callback exists, it invokes it with additional parameters, otherwise frees the memory via VirtualFree.

class EARSObject {
public:
    // +0x08: some data (e.g., identifier or size)
    int unknownData1; // offset 0x8

    // +0x0d: flag indicating object is alive/active
    char aliveFlag; // offset 0xD

    // +0x0e: flag indicating object is pending destroy (used with force delete)
    char pendingDestroyFlag; // offset 0xE

    // +0x10: function pointer for custom destructor/callback
    // Signature: void (__stdcall *)(int param2, EARSObject* this, int data1, int data2)
    void (__stdcall *destructorCallback)(int, EARSObject*, int, int); // offset 0x10

    // +0x14: another piece of data (passed to callback)
    int unknownData2; // offset 0x14
};

// Reconstructed function
// __thiscall: this pointer passed via ecx
// param_2: some integer context (possibly a user-defined value)
// param_3: boolean indicating force delete
int __thiscall EARSObject::release(int param2, char param3)
{
    // Check: object is alive OR (force delete requested AND pendingDestroyFlag is set)
    if (this->aliveFlag != 0 ||
        (param3 != 0 && this->pendingDestroyFlag != 0))
    {
        // If a custom destructor callback exists, invoke it
        if (this->destructorCallback != nullptr)
        {
            // Call the callback with: param2, this, unknownData1, unknownData2
            this->destructorCallback(param2, this, this->unknownData1, this->unknownData2);
            return 1; // success
        }
        
        // No custom callback: free the entire memory block
        // dwSize = 0, dwFreeType = MEM_RELEASE (0x8000)
        VirtualFree(this, 0, 0x8000);
        return 1; // success
    }
    
    return 0; // indicates no action taken
}