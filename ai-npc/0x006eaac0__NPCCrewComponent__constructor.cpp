// FUNC_NAME: NPCCrewComponent::constructor

// Address: 0x006eaac0
// Role: Constructor for NPCCrewComponent, initializes base class and zeros all tracking fields

class NPCCrewComponent {
public:
    void* vtable;                          // +0x00

    // Base class data (inherited from SentientComponent or similar)
    // ...

    // Crew-specific fields:
    // Offset 0x3C: pointer to some global data (maybe crew list template)
    void* someListPtr;                     // +0x3C

    // Offset 0x48: pointer to another global data (crew behavior table?)
    void* behaviorTable;                   // +0x48

    // Offset 0x50: integer count of something
    int crewMemberCount;                   // +0x50

    // Offset 0x54: short flags or ID
    short flags1;                          // +0x54

    // Offset 0x56: another short
    short flags2;                          // +0x56

    // Offset 0x58: integer for something
    int someInt1;                          // +0x58

    // Offset 0x5C: integer
    int someInt2;                          // +0x5C

    // Offset 0x5E: short
    short someShort1;                      // +0x5E

    // Offset 0x60: integer
    int someInt3;                          // +0x60

    // Offset 0x64: integer
    int someInt4;                          // +0x64

    // Offset 0x66: short
    short someShort2;                      // +0x66

    // Offset 0x68: integer
    int someInt5;                          // +0x68

    // Offset 0x6C: integer
    int someInt6;                          // +0x6C

    // Offset 0x70: integer
    int someInt7;                          // +0x70

    // Offset 0x74: integer
    int someInt8;                          // +0x74

    // Offset 0x78: byte, maybe a bool
    byte someFlag;                         // +0x78

    // Constructor
    __thiscall NPCCrewComponent* constructor(NPCCrewComponent* this, int baseParam) {
        // Call base class constructor (e.g., SentientComponent, with baseParam as session/owner ID)
        FUN_0046c590(baseParam);

        // Set vtable pointer (points to NPCCrewComponent vtable)
        this->vtable = (void*)0x00d5fdbc;

        // Initialize crew-related pointers to global tables
        this->someListPtr = (void*)0x00d5fdac;
        this->behaviorTable = (void*)0x00d5fda8;

        // Zero out all numeric fields
        this->crewMemberCount = 0;
        this->flags1 = 0;
        this->flags2 = 0;
        this->someInt1 = 0;
        this->someInt2 = 0;
        this->someShort1 = 0;
        this->someInt3 = 0;
        this->someInt4 = 0;
        this->someShort2 = 0;
        this->someInt5 = 0;
        this->someInt6 = 0;
        this->someInt7 = 0;
        this->someInt8 = 0;
        this->someFlag = 0;

        return this;
    }
};