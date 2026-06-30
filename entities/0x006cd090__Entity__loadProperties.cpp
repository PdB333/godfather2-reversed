// FUNC_NAME: Entity::loadProperties
// Address: 0x006cd090
// Role: Reads a property stream and populates object fields (linked lists, flags, etc.)

class Entity {
public:
    // Fields (offsets relative to this):
    // +0x58: m_pPropertyStream1 (some sub-stream/pointer)
    // +0x68: m_pPropertyStream2 (another sub-stream)
    // +0x78: m_pListHead1 (head of linked list for type 0 properties)
    // +0x80: m_pListHead2 (head of linked list for type 1 properties)
    // +0x90: m_iPropertyValue (integer read from property type 2)
    // +0x94: m_flags (bitfield, top bit 0x80000 indicates property type 2 was read)
    int m_pPropertyStream1;   // actually pointer, offset 0x58
    int m_pPropertyStream2;   // offset 0x68
    int* m_pListHead1;        // offset 0x78
    int* m_pListHead2;        // offset 0x80
    int m_iPropertyValue;     // offset 0x90
    uint32 m_flags;           // offset 0x94
};

// Forward declarations for utility functions (these are guessed names)
void initStream(void* stream);   // FUN_004738b0
void setMagic(void* stream, uint32 magic); // FUN_0043aff0 with magic 0x5576abcd
bool isStreamEnd(void* stream);  // FUN_0043b120
void* readNextProperty(void* stream); // FUN_0043b210 returns property data
int getPropertyType(void* stream);    // FUN_0043ab70
void beginSubProperty(void* stream);  // FUN_0043ad10
void endSubProperty(void* stream);    // FUN_0043b1a0
void* findProperty(void* subStream, int index); // FUN_00445ff0
bool readPropertyValue(void* stream, uint32 typeID, int* outValue); // FUN_004480d0
void freeLinkedListNode(int** node); // FUN_004daf90

void __thiscall Entity::loadProperties(void* thisPtr, void* stream)
{
    int propData;
    int* node;
    int value;
    bool end;
    
    // Initialize property reader
    initStream(stream);
    setMagic(stream, 0x5576abcd);
    
    // Loop over all properties in the stream
    do {
        end = isStreamEnd(stream);
        if (end) {
            return;
        }
        
        // Prepare to read next property
        readNextProperty(stream);
        int type = getPropertyType(stream);
        
        switch (type) {
        case 0: {
            // Type 0: read a sub-stream and store a reference to a linked list at +0x78
            void* subStream = (void*)(thisPtr + 0x68);  // offset 0x68 used as temporary sub-stream pointer?
            // Actually: iVar3 = param_1 + 0x68; iVar5 = iVar3; FUN_0043b210(iVar3); FUN_0043ad10(iVar5);
            // This is confusing: it uses the field at +0x68 as a sub-stream?
            // The code does: FUN_0043b210(iVar3) then FUN_0043ad10(iVar5) on the same address.
            // Likely they treat the object's own property field as a temporary sub-property stream.
            // Then FUN_00445ff0(iVar3,0) gets a property from that sub-stream.
            // Then FUN_004480d0 reads a value of type 0x55859efa.
            int* subProp = findProperty((void*)(thisPtr + 0x68), 0);
            if (readPropertyValue(subProp, 0x55859efa, &value) && value != 0) {
                // value is actually a pointer to a node?
                // The assignment: piVar4 = (int*)(param_1 + 0x78); then linked list insertion
                node = (int*)(thisPtr + 0x78);
                int* newNode = (int*)(value + 0x48); // offset 0x48 in the new node
                if (*node != newNode) {
                    if (*node != 0) {
                        freeLinkedListNode(node); // detach old?
                    }
                    *node = newNode;
                    if (newNode != 0) {
                        node[1] = *(int*)(value + 0x4c); // set next pointer
                        *(int**)(value + 0x4c) = node;  // update previous
                    }
                }
            }
            break;
        }
        case 1: {
            // Type 1: similar but using property at +0x58 and list at +0x80
            int* subProp = findProperty((void*)(thisPtr + 0x58), 0);
            if (readPropertyValue(subProp, 0x55859efa, &value) && value != 0) {
                node = (int*)(thisPtr + 0x80);
                int* newNode = (int*)(value + 0x48);
                if (*node != newNode) {
                    if (*node != 0) {
                        freeLinkedListNode(node);
                    }
                    *node = newNode;
                    if (newNode != 0) {
                        node[1] = *(int*)(value + 0x4c);
                        *(int**)(value + 0x4c) = node;
                    }
                }
            }
            break;
        }
        case 2: {
            // Type 2: read a raw integer and store at +0x90, set flag bit 0x80000
            void* propertyData = readNextProperty(stream);
            m_iPropertyValue = *(int*)((char*)propertyData + 8);
            m_flags |= 0x80000;
            break;
        }
        case 3: {
            // Type 3: clear flags and set a single bit based on a value read from property data
            m_flags = 0;
            void* propertyData = readNextProperty(stream);
            int bitIndex = *(int*)((char*)propertyData + 8);
            m_flags = 1 << (bitIndex & 0x1f);
            break;
        }
        }
        
        // Advance to next property in stream
        endSubProperty(stream);
        end = isStreamEnd(stream);
    } while (true);
}