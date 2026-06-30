// FUN_NAME: EARSObject::~EARSObject (scalar deleting destructor)
// Reconstructed scalar deleting destructor for EARSObject (based on EA EARS engine pattern).
// Calls base destructor, then conditionally calls operator delete if the low bit of deletingFlag is set.
// Returns the this pointer (standard MSVC scalar deleting destructor convention).

class EARSObjectBase {
public:
    void __thiscall ~EARSObjectBase();  // Base destructor at 0x00453a70
};

class EARSObject : public EARSObjectBase {
public:
    void __thiscall ~EARSObject(unsigned char deletingFlag);
};

void __thiscall EARSObject::~EARSObject(unsigned char deletingFlag) {
    // Call the base class destructor
    this->EARSObjectBase::~EARSObjectBase();

    // If the scalar delete flag (bit 0) is set, free the memory
    if (deletingFlag & 1) {
        operator delete(this);
    }

    // Return this pointer (compiler convention for scalar deleting destructors)
    return;
}