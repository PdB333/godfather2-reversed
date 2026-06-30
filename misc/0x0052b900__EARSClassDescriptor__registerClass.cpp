// FUNC_NAME: EARSClassDescriptor::registerClass

// This function is the base-class constructor/registration for the EARS class descriptor system.
// It initializes a static class descriptor object, linking it into a global singly-linked list
// and assigning a unique serial number. It also computes a class ID from the class name via a hash.
// The class descriptor object is located at a fixed global address (0x01125d80).

// +0x00: vtable pointer (implicit)
// +0x04: next pointer (EARSClassDescriptor*)
// +0x08: classId (unsigned int, hash of class name)
// +0x0C: serialNumber (int, global counter assigned on registration)

class EARSClassDescriptor {
public:
    // Virtual function table offsets:
    // [0] : (typical destructor or first virtual)
    // [1] : getClassName() -> const char*  (offset 0x04)
    // [4] : onRegister() -> void           (offset 0x10)

    virtual const char* getClassName();
    virtual void onRegister();

    EARSClassDescriptor* next;      // +0x04 next pointer in global list
    unsigned int classId;           // +0x08 hash identifier for the class
    int serialNumber;               // +0x0C unique registration number

    void __thiscall registerClass();
};

// Global variables for the class registry list
extern EARSClassDescriptor* gClassListHead; // = DAT_012058ec
extern int gClassCounter;                   // = DAT_012058f8 (incremented each registration)

// External function at 0x0060d740: computes a unique ID from a class name string
extern unsigned int __cdecl hashStringToId(const char* name);

// Function at 0x0052b900
void EARSClassDescriptor::registerClass() {
    // 1. Get the class name via virtual call (vtable offset 0x04)
    const char* className = this->getClassName();

    // 2. Convert to a class ID hash
    this->classId = hashStringToId(className);

    // 3. Call optional post-registration virtual (vtable offset 0x10)
    this->onRegister();

    // 4. Insert this descriptor at the head of the global list
    this->next = gClassListHead;
    gClassListHead = this;

    // 5. Assign a unique increasing serial number
    gClassCounter++;
    this->serialNumber = gClassCounter;
}