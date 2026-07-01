// FUNC_NAME: BNKStreamManager::BNKStreamManager
// Function address: 0x007ad870
// Role: BNKStreamManager constructor (derived class)

class BNKStreamManager : public EARS::Framework::Object
{
public:
    // Offset 0x58: bool flag to load a resource
    int m_loadResourceFlag; // +0x58
    // Offset 0x74: pointer to stream manager internal data
    void* m_pendingStreamData; // +0x74
    // Offset 0x78: loaded resource pointer
    void* m_resourcePtr; // +0x78

    // Constructor: takes two arguments (likely stream type and some parameter)
    __thiscall BNKStreamManager(void* arg1, void* arg2)
    {
        // Call base class constructor (EARS::Framework::Object)
        EARS::Framework::Object::Object(arg1, arg2);

        // Set vtable pointer for BNKStreamManager
        *(void**)this = (void*)PTR_LAB_00d6bb4c;

        // Get the global stream manager instance
        void* streamMgr = getStreamManagerInstance();
        // Copy stream manager's internal data (offset +4) into this+0x74
        this->m_pendingStreamData = *(void**)((char*)streamMgr + 4);

        // Call stream manager's virtual function at vtable index 0 with argument 2
        // (likely Initialize with priority or thread ID)
        void* streamMgr2 = getStreamManagerInstance();
        void** vtable2 = *(void***)streamMgr2;
        ((void (__thiscall*)(void*, int))vtable2[0])(streamMgr2, 2);

        // If flag at +0x58 is non-zero, load a resource from the global manager
        if (this->m_loadResourceFlag != 0)
        {
            this->m_resourcePtr = resourceManagerGetObject(DAT_01131018);
        }
        else
        {
            this->m_resourcePtr = nullptr;
        }
    }
};

// External functions (likely from EARS engine)
void __thiscall EARS::Framework::Object::Object(void*, void*); // base constructor
void* getStreamManagerInstance();                               // returns singleton
void* resourceManagerGetObject(void* globalPtr);                // loads resource