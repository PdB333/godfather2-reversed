// FUNC_NAME: AudioComponent::AudioComponent

class AudioComponent {
public:
    struct VTable {
        void* vf0; // +0x00
        void* vf4; // +0x04
        void* vf8; // +0x08
        void* vf12; // +0x0C
        void* vf16; // +0x10
        void* vf20; // +0x14
        void* vf24; // +0x18
        // ...
    };
    VTable* vtable;

    // Fields based on decompiled offsets (this as int*)
    // +0x00: vtable
    // +0x04..+0x48: unknown base class
    int* ownerList;          // +0x17 (0x5C) - pointer to a list
    int ownerList2;          // +0x18 (0x60) - count or something
    int* anotherList;        // +0x1c (0x70) - another list pointer
    int anotherList2;        // +0x1d (0x74) - count or something
    char field_0x19;         // +0x19 (0x64)
    char field_0x66;         // +0x66 (0x66)
    void* ownerPtr;          // +0x12 (0x48) - pointer to owner object (used for query)
    int queryResult;         // +0x16 (0x58) - result of interface query
    void* audioBus;          // +0x1a (0x68) - pointer to an audio bus
    void* audioSource;       // +0x1b (0x6C) - pointer to an audio source
    char field_0x1e;         // +0x1e (0x78) - ?
    char field_0x65;         // +0x65 (0x65)
    // ... other fields

    // Constructor
    AudioComponent(int param2, int param3);
};

// Global functions - stubs
int* FUN_0080e6a0(int, int);  // base class constructor
void FUN_004daf90(int* ptr);  // free/delete
void* FUN_0043b870(void* globalPtr); // singleton getter
void FUN_007f63e0(int ms);    // sleep
void FUN_009b0720(int val);   // set audio flag

AudioComponent::AudioComponent(int param2, int param3)
{
    // Base class constructor call
    FUN_0080e6a0(param2, param3);

    // Set vtable (or store pointer)
    this->vtable = (VTable*)0x00d63dc0; // PTR_LAB_00d63dc0

    // Initialize lists
    this->ownerList = nullptr;
    this->ownerList2 = 0;
    this->anotherList = nullptr;
    this->anotherList2 = 0;

    // Clear existing lists if needed
    if (this->ownerList != nullptr) {
        FUN_004daf90(this->ownerList);
        this->ownerList = nullptr;
    }
    this->field_0x19 = 0;
    this->field_0x66 = 0;
    if (this->anotherList != nullptr) {
        FUN_004daf90(this->anotherList);
        this->anotherList = nullptr;
    }

    // Query owner for interface ID 0x369ac561
    int* ownerObj = nullptr;
    if (this->ownerPtr != nullptr) {
        // Get containing object by subtracting offset 0x48
        ownerObj = (int*)((char*)this->ownerPtr - 0x48);
    }
    int queryParam = 0; // param_3
    char queryResult = ((bool (__thiscall*)(void*, uint, int*))((*(int**)ownerObj)[4]))(ownerObj, 0x369ac561, &queryParam);
    this->queryResult = (queryResult != 0) ? 0x369ac561 : 0; // uVar4 = -(uint)(cVar3 != '\0') & unaff_retaddr; simplification

    // Get audio bus and source singletons
    static void* audioBusGlobal = (void*)0x0113105c; // DAT_0113105c
    static void* audioSourceGlobal = (void*)0x01131038; // DAT_01131038
    if (this->queryResult != 0) {
        this->audioBus = FUN_0043b870(audioBusGlobal); // FUN_0043b870(DAT_0113105c)
    } else {
        this->audioBus = nullptr;
    }
    this->field_0x1e = 0;

    if (this->queryResult != 0) {
        this->audioSource = FUN_0043b870(audioSourceGlobal); // FUN_0043b870(DAT_01131038)
    } else {
        this->audioSource = nullptr;
    }

    // Set audio bus volume/mute
    // field_0x65 = ~(audioBus->field_0x78 >> 4) & 1
    if (this->audioBus != nullptr) {
        unsigned char* busField78 = (unsigned char*)this->audioBus + 0x78;
        this->field_0x65 = (~(*busField78 >> 4)) & 1;
        unsigned short* busField78Short = (unsigned short*)busField78;
        *busField78Short &= 0xFFDF; // clear bit 5
    }

    // Sleep for 98ms
    FUN_007f63e0(0x62); // 0x62 = 98

    // If query succeeded, get audio source again and call a function
    if (this->queryResult != 0) {
        void* src = FUN_0043b870(audioSourceGlobal);
        if (src != nullptr) {
            FUN_009b0720(0); // likely disable audio or something
        }
    }
}