// Xbox PDB: EARS::Framework::OnlineServices::GameManager::GameManager
// FUNC_NAME: MultiplayerGameManager::MultiplayerGameManager

#include <windows.h> // Assume standard types

class MultiplayerGameManager : public SomeBaseClass {
public:
    // Constructor
    MultiplayerGameManager(int param2) // param2 is likely a controller/index handle
    {
        // Call base constructor
        someBaseConstructor();

        // Set vtable pointers (multiple inheritance)
        this->vtable0 = (void*)0x00e35de8; // primary vtable
        this->vtable1 = (void*)0x00e35e80; // secondary vtable

        // Set the specific vtable for message handling at offset 0xd8 (0x360 bytes offset)
        this->messageHandlerVtable = (void*)0x00e2f19c; // initial vtable
        this->messageHandlerField = 1;   // +0x364
        this->someFlag = 0;              // +0x368
        this->anotherFlag = 0;           // +0x36C
        *(BYTE*)((DWORD)this + 0x370) = 0; // byte at offset 0x370
        this->initialParam = param2;     // +0x374

        // Register message handlers using string-based message IDs
        DWORD msgId;
        msgId = getMessageId("iMsgMultiplayerGameStart");
        registerMessageHandler(&DAT_01218070, msgId);

        msgId = getMessageId("iMsgMultiplayerGameEnd");
        registerMessageHandler(&DAT_01218058, msgId);

        msgId = getMessageId("iMsgHostMigrationStart");
        registerMessageHandler(&DAT_01218068, msgId);

        msgId = getMessageId("iMsgHostMigrationEnd");
        registerMessageHandler(&DAT_01218060, msgId);

        msgId = getMessageId("iMsgPostNetworkUpdate");
        registerMessageHandler(&DAT_0120ea74, msgId);

        // Conditionally attach handler if already registered
        if (DAT_0120ea74 != 0) {
            attachMessageHandler((DWORD)this + 0x360, &DAT_0120ea74);
        }
    }

private:
    // Vtable pointers
    void* vtable0;               // +0x00
    void* vtable1;               // +0x04
    // ... other base class members ...
    void* messageHandlerVtable;  // +0x360 (offset 0xd8 * 4)
    int messageHandlerField;     // +0x364
    int someFlag;                // +0x368
    int anotherFlag;             // +0x36C
    BYTE flagByte;               // +0x370
    int initialParam;            // +0x374

    // Message registration globals (defined elsewhere, presumably static data)
    static DWORD DAT_01218070;
    static DWORD DAT_01218058;
    static DWORD DAT_01218068;
    static DWORD DAT_01218060;
    static DWORD DAT_0120ea74;

    // External functions
    void someBaseConstructor();
    DWORD getMessageId(const char* name);
    void registerMessageHandler(DWORD* storage, DWORD msgId);
    void attachMessageHandler(DWORD handlerAddr, DWORD* storage);
};