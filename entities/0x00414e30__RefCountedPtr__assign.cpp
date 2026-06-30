// FUNC_NAME: RefCountedPtr::assign
// Function: 0x00414e30 - Copies a reference-counted pointer, incrementing the reference count.
// The managed object has a reference count at offset +0x04.
// This method is used to assign one RefCountedPtr to another, sharing ownership.

class RefCountedPtr {
public:
    int* mData; // +0x00: pointer to the managed object (which has refcount at +0x04)

    void assign(const RefCountedPtr& other) {
        int* newData = other.mData;      // Get the pointer from the source handle
        mData = newData;                  // Assign to this handle
        if (newData != nullptr) {
            // Increment the reference count at offset +0x04 of the managed object
            (*(int*)(newData + 4))++;
        }
    }
};