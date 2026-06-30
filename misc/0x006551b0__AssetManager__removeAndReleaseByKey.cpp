// FUNC_NAME: AssetManager::removeAndReleaseByKey
// Address: 0x006551b0
// Role: Searches an array of resource objects by a key (2 shorts + 4 ints), decrements reference count, and removes the object if count reaches zero.
// The 'this' pointer is assumed to be in EDI (not reflected in the formal parameter).
// Resource object layout:
// +0x00: vtable pointer
// +0x08: int refCount
// +0x100: short keyPart0
// +0x102: short keyPart1
// +0x104: int keyPart2
// +0x108: int keyPart3
// +0x10c: int keyPart4
// +0x110: int keyPart5
// Manager layout:
// +0x24: int numItems
// +0x2c: void** items (array of pointers to resource objects)

struct Resource {
    void** vtable; // +0x00
    int refCount;  // +0x08
    short keyPart0; // +0x100
    short keyPart1; // +0x102
    int keyPart2;   // +0x104
    int keyPart3;   // +0x108
    int keyPart4;   // +0x10c
    int keyPart5;   // +0x110
} ;

void __fastcall AssetManager::removeAndReleaseByKey(short* key)
{
    int i = 0;
    if (this->numItems > 0) {
        void** itemPtr = this->items;
        while (true) {
            Resource* res = (Resource*)*itemPtr;
            if (res->keyPart0 == key[0] &&
                res->keyPart1 == key[1] &&
                res->keyPart2 == *(int*)(key + 2) &&
                res->keyPart3 == *(int*)(key + 4) &&
                res->keyPart4 == *(int*)(key + 6) &&
                res->keyPart5 == *(int*)(key + 8)) {
                break;
            }
            i++;
            itemPtr++;
            if (i >= this->numItems) {
                return;
            }
        }
        Resource* foundRes = *(Resource**)(this->items + i);
        foundRes->refCount--;
        if (foundRes->refCount == 0) {
            // Call virtual destructor or release function? The vtable at +8 is likely a virtual function.
            (*(void (**)(void))(*foundRes->vtable + 8))(); // call through vtable at offset 8
        }
        // Remove the found element by shifting subsequent elements down
        if (i < this->numItems - 1) {
            do {
                this->items[i] = this->items[i + 1];
                i++;
            } while (i < this->numItems - 1);
        }
        this->numItems--;
    }
}