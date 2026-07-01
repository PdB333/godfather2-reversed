// FUNC_NAME: UnknownClass::getOwner
// Function address: 0x007d65e0
// This function returns a pointer to the owning container object by
// subtracting the embedded object offset (0x48) from a stored pointer at +0x13c.
// Used for reverse-lookup from a component/child to its parent.

class UnknownClass {
    // Private member at offset +0x13c pointing to the container start?
    // Actually stored pointer is derived from the container's base by +0x48.
    int *mContainerPtr; // +0x13c
public:
    // Returns container pointer or 0 if mContainerPtr is null
    int *getOwner() {
        if (mContainerPtr != 0) {
            // The container is 0x48 bytes before the stored pointer.
            // This assumes the embedded object is at offset 0x48 within the container.
            return (int *)(mContainerPtr - 0x48);
        }
        return 0;
    }
};