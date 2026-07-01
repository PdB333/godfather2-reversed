// FUNC_NAME: ManagedArray::operator=
// Function address: 0x00827520
// The Godfather 2 (2008, x86) - EA EARS engine
// Reconstructed assignment operator for an array of intrusive-pointer entries (8 bytes each)
// Offset 0x00: int* pBuffer       (array of 8-byte entries)
// Offset 0x04: int nSize
// Offset 0x08: int nCapacity

#include <cstdint>

// Forward declarations (internal memory/object management)
extern void* __cdecl AllocArray(int sizeBytes);           // 0x009c8e80
extern void  __cdecl FreeArray(void* ptr);                // 0x009c8f10
extern void  __thiscall ReleaseEntry(int* entry);         // 0x004daf90

struct ManagedArray {
    int**    pBuffer;      // +0x00: array of 8-byte entries (each is a pointer pair)
    int      nSize;        // +0x04: number of valid entries
    int      nCapacity;    // +0x08: allocated capacity

    // Each entry is 8 bytes:
    // [0] : int* pObject;
    // [4] : int* pBackLink;  // set to point back to this entry (intrusive)

    ManagedArray* __thiscall operator=(ManagedArray* pOther);
};

ManagedArray* __thiscall ManagedArray::operator=(ManagedArray* pOther) {
    // Self-assignment check
    if (this == pOther) {
        return this;
    }

    // Destroy existing entries (backwards iteration)
    int* pEntry = this->pBuffer;
    int count = this->nSize;
    for (int i = count - 1; i >= 0; --i) {
        int* entryPtr = pEntry + i * 2; // each entry is 2 ints
        if (entryPtr[0] != 0) {
            ReleaseEntry(entryPtr);        // release the object pointed to
        }
    }

    // Reallocate buffer if needed
    if (this->nCapacity < pOther->nSize) {
        FreeArray(this->pBuffer);                     // free old buffer
        this->nCapacity = pOther->nSize;             // set new capacity
        if (this->nCapacity == 0) {
            this->pBuffer = nullptr;
        } else {
            this->pBuffer = (int**)AllocArray(this->nCapacity * 8); // allocate 8 bytes per entry
        }
    }

    // Copy entries from source
    for (uint32_t i = 0; i < (uint32_t)pOther->nSize; ++i) {
        int* destEntry = (int*)(this->pBuffer + i);
        int* srcEntry = (int*)(pOther->pBuffer + i);

        destEntry[0] = srcEntry[0];          // copy object pointer
        destEntry[1] = 0;                    // initially no back link
        if (destEntry[0] != nullptr) {
            // Update intrusive back link in the object (at offset +4)
            destEntry[1] = *(int*)(destEntry[0] + 1);   // old back link (if any)
            *(int**)(destEntry[0] + 1) = destEntry;     // point object back to this entry
        }
    }

    // Update size
    this->nSize = pOther->nSize;

    return this;
}