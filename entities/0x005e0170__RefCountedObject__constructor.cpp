// FUNC_NAME: RefCountedObject::constructor

typedef int HandleType; // placeholder for return value of FUN_004265d0

// Forward declarations
int __cdecl FUN_004265d0(int object, void* param);
void __cdecl FUN_005e0b60(void* pObj, HandleType handle);

// Abstract base class with reference counting interface
class RefCountedBase {
public:
    virtual void __thiscall unknown0() = 0;         // offset 0x00 (unused)
    virtual void __thiscall setExtraObject(int obj, int flag) = 0; // offset 0x04
    virtual void __thiscall addRef() = 0;            // offset 0x08
    virtual void __thiscall releaseRef() = 0;        // offset 0x0C
};

// Class that holds a reference to a RefCountedBase and optionally an extra object
class RefCountedObject {
private:
    // +0x14: pointer to the referenced object
    RefCountedBase* pRef;
    // +0x18: handle or ID for the extra object, 0 if none
    HandleType extraHandle;

public:
    // Constructor - returns this pointer (as int) in this decompilation style
    int __thiscall constructor(RefCountedBase* pSend, int extraObj) {
        HandleType uVar1;
        RefCountedBase* pIter = pSend;

        // Increment reference count for the sent object
        pSend->addRef();

        // Compute handle (0 if no extra object)
        if (extraObj == 0) {
            uVar1 = 0;
        } else {
            uVar1 = FUN_004265d0(extraObj, pIter);
        }

        // Initialize internal state (sets up something with pSend and uVar1)
        FUN_005e0b60(pIter, uVar1);

        // Store the pointer to the referenced object
        this->pRef = pSend;

        // Another AddRef – accounts for the stored reference (or possibly a temp)
        pSend->addRef();

        if (extraObj != 0) {
            // Recompute handle using this->pRef (now stored)
            uVar1 = FUN_004265d0(extraObj, this->pRef);
            this->extraHandle = uVar1;

            // Attach the extra object to the referenced object
            pSend->setExtraObject(extraObj, 0);

            // Release the temporary reference (balance the first addRef)
            pSend->releaseRef();
        } else {
            this->extraHandle = 0;
            // Release temporary reference
            pSend->releaseRef();
        }

        return (int)this;
    }
};