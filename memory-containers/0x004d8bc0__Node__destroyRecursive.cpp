//FUNC_NAME: Node::destroyRecursive
int __fastcall Node::destroyRecursive(void* thisPtr)
{
    // Check if there is a child node at offset +0x20
    if (*(void**)((char*)thisPtr + 0x20) != nullptr)
    {
        // Recursively destroy the child
        destroyRecursive(*(void**)((char*)thisPtr + 0x20));
    }
    // Call the deallocation/destructor helper
    FUN_009c8eb0(thisPtr);
    return (int)thisPtr;
}