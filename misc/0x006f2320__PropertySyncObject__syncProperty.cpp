// FUNC_NAME: PropertySyncObject::syncProperty
// address: 0x006f2320
// __thiscall member function that synchronizes local cached properties from a global manager based on property ID.

class PropertySyncObject {
public:
    // Offsets documented in comments
    // +0x10: pointer to some global/derived object
    void* m_somePointer;    
    // +0x14: boolean flag (e.g., active)
    bool m_activeFlag;       
    // +0x15: byte always set to 0 (reserved/padding)
    uint8_t m_paddingByte;   
    // +0x18: integer property A
    int m_propertyA;         
    // +0x1c: integer property B
    int m_propertyB;         
    // +0x20: string buffer (size unknown, at least 1 byte)
    char m_stringBuffer[256]; 

    // Public method
    void __thiscall syncProperty(int unusedValue, int propertyID);
};

// External helper functions (inferred from called addresses)
// 0x0043b210: When called with this -> initializes/resets this (case 0).
// When called without args -> returns global manager pointer (cases 1–5).
void __cdecl globalInitOrReset(PropertySyncObject* thisPtr); // with arg
void* __cdecl getGlobalManager(); // without arg

// 0x0043ad10: Additional initialization step (case 0)
void __thiscall initPropertyPart2(PropertySyncObject* this);

// 0x0043ab90: Returns a value (e.g., a string or resource handle)
void* __cdecl getSomeValue();

// 0x004d3d90: Copies/assigns a value (used in case 1)
void __cdecl assignValue(void* value);

// 0x006f08a0: Converts assigned value to a pointer (case 1)
void* __cdecl valueToPointer(void* value);

// 0x00408980: Copies a string from source to destination (case 5)
void __cdecl copyString(char* dst, void* src);

void PropertySyncObject::syncProperty(int unusedValue, int propertyID) {
    void* globalManager;
    void* someValue;
    void* pointerResult;

    switch (propertyID) {
        case 0:
            // Full reset/reinitialize of local properties
            globalInitOrReset(this); // FUN_0043b210(this)
            initPropertyPart2(this); // FUN_0043ad10(this)
            break;

        case 1:
            // Sync pointer from global state
            globalInitOrReset(); // FUN_0043b210() – global manager update/init (return ignored)
            someValue = getSomeValue(); // FUN_0043ab90()
            assignValue(someValue); // FUN_004d3d90(someValue)
            pointerResult = valueToPointer(someValue); // FUN_006f08a0(someValue)
            m_somePointer = pointerResult; // *(this+0x10)
            m_paddingByte = 0; // *(this+0x15) = 0
            break;

        case 2:
            // Sync boolean flag from global manager field at offset +8
            globalManager = getGlobalManager(); // FUN_0043b210()
            m_activeFlag = *(int*)((char*)globalManager + 8) != 0; // false if zero
            break;

        case 3:
            // Sync integer property A from global manager field at +8
            globalManager = getGlobalManager();
            m_propertyA = *(int*)((char*)globalManager + 8); // *(this+0x18)
            break;

        case 4:
            // Sync integer property B from global manager field at +8
            globalManager = getGlobalManager();
            m_propertyB = *(int*)((char*)globalManager + 8); // *(this+0x1c)
            break;

        case 5:
            // Sync string (copied from some source)
            globalInitOrReset(); // FUN_0043b210() – possibly updates global state
            someValue = getSomeValue(); // FUN_0043ab90() – get string source
            copyString(m_stringBuffer, someValue); // FUN_00408980(this+0x20, someValue)
            break;

        default:
            break;
    }
}