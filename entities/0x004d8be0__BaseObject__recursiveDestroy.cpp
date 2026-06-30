// FUNC_NAME: BaseObject::recursiveDestroy
// Address: 0x004d8be0
// Role: Recursive destruction of a tree structure; frees child nodes after processing

void __fastcall BaseObject::recursiveDestroy(int thisPtr)
{
    // +0x14: pointer to child object (or next in a linked list)
    BaseObject* child = *(BaseObject**)(thisPtr + 0x14);
    if (child != 0) {
        // Recursively destroy descendants first
        child->recursiveDestroy();
        // Free the child's memory
        FUN_009c8eb0(child);
    }
    // The caller is responsible for freeing this object if needed
}