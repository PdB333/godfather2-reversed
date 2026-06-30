// FUNC_NAME: CallbackNode::CallbackNode

extern void* PTR_FUN_00e312d0;
extern void* DAT_0110ac04; // some global data pointer

short getNewID(); // from FUN_004a6380

class CallbackNode {
public:
    CallbackNode(uint32 identifier, void* context, void* pOwner);
private:
    void* vtable;             // +0x00
    uint32 m_identifier;      // +0x04
    void* m_pOwner;           // +0x08 (passed in EAX on original x86)
    uint32 m_field0C;         // +0x0C
    uint32 m_field10;         // +0x10
    void* m_pGlobalData;      // +0x14 (DAT_0110ac04)
    short m_id;               // +0x18
    short m_field1A;          // +0x1A
    void* m_context;          // +0x1C
};

CallbackNode::CallbackNode(uint32 identifier, void* context, void* pOwner) {
    // Initialize fields from parameters
    m_identifier = identifier;           // param_1
    m_pOwner = pOwner;                   // in_EAX (extra register param)
    vtable = &PTR_FUN_00e312d0;          // set vtable pointer
    m_field0C = 0;                       // clear
    m_field10 = 0;                       // clear
    m_pGlobalData = DAT_0110ac04;        // store global data reference
    m_id = 0;                            // zero out the two shorts at +0x18..0x1B
    m_field1A = 0;

    m_context = context;                 // param_2

    // Decide how to assign the object ID
    if (*(int*)((char*)pOwner + 0x0C) != 0) {
        m_id = getNewID();               // use system‐wide ID generator
        return;
    }

    // Otherwise, increment the owner’s counter at +0x58 and use its previous value
    short oldID = *(short*)((char*)pOwner + 0x58);
    *(short*)((char*)pOwner + 0x58) = oldID + 1;
    m_id = oldID;
}