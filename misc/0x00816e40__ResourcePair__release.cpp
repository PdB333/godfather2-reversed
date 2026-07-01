// FUNC_NAME: ResourcePair::release
// Address: 0x00816e40
// Role: Releases two resources stored in the object: one via a stored deleter function pointer, another via a standard deallocation function.

struct ResourcePair
{
    // +0x04: Pointer to first resource (e.g., allocated block)
    void*   resource1;
    // +0x10: Pointer to second resource (e.g., object with custom deleter)
    void*   resource2;
    // +0x1c: Function pointer to custom deleter for resource2
    void    (*customDeleter)(void*);
};

void __fastcall ResourcePair::release()
{
    // If resource2 is non-null, call its custom deleter
    if (this->resource2 != 0) {
        this->customDeleter(this->resource2);
    }
    // If resource1 is non-null, free it via the generic deallocation function
    if (this->resource1 != 0) {
        FUN_009c8f10(this->resource1); // external; likely operator delete or heap free
    }
}