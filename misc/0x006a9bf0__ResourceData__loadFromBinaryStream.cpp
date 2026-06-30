// FUNC_NAME: ResourceData::loadFromBinaryStream
// Address: 0x006a9bf0
// Role: Reads serialized data from a stream into a resource data block

class ResourceData {
public:
    // Offset 0x3C: large data buffer (0x8000 bytes)
    char m_dataBuffer[0x8000];  // +0x3C

    // These are fields within m_dataBuffer at known offsets
    // +0x50: handle0 (int)
    // +0x58: handle1 (int)
    // +0x60: handle2 (int)
    // +0x68: handle3 (int)
    // +0x70: flags (bitmask)
    // +0x74: quaternion1 (4 ints)
    // +0x84: resourceId1
    // +0x8C: quaternion2 (4 ints)
    // +0x9C: resourceId2
    // +0xA4..0xC0: individual flags/values (8 ints)

    void __thiscall loadFromBinaryStream(void* stream) {
        int tokenValue;
        uint32_t uVar5 = 0;
        int* quadPtr;

        // Initialize stream reader and expect magic number
        streamReaderBegin(stream);
        streamReaderExpectMagic(stream, 0x100351e6);

        // Loop until end of token stream
        while (!streamReaderIsEnd()) {
            streamReaderNextToken();  // advance to next token
            int tokenType = streamReaderGetTokenType();

            switch(tokenType) {
                case 0: // Field: object type flag? (offset 0x70)
                    tokenValue = streamReaderReadToken();
                    *(int*)((char*)this + 0x70) = *(int*)(tokenValue + 8);
                    break;
                case 1: // Field: string handle at 0x50
                    streamReaderNextToken();
                    tokenValue = streamReaderGetTokenInt(); // string ID or handle
                    copyStringHandle((char*)this + 0x50, tokenValue);
                    break;
                case 2: // Field: string handle at 0x58
                    streamReaderNextToken();
                    tokenValue = streamReaderGetTokenInt();
                    copyStringHandle((char*)this + 0x58, tokenValue);
                    break;
                case 3: // Field: integer at 0xA4
                    tokenValue = streamReaderReadToken();
                    *(int*)((char*)this + 0xA4) = *(int*)(tokenValue + 8);
                    break;
                case 4: // Field: integer at 0xA8
                    tokenValue = streamReaderReadToken();
                    *(int*)((char*)this + 0xA8) = *(int*)(tokenValue + 8);
                    break;
                case 5: // Field: integer at 0xAC
                    tokenValue = streamReaderReadToken();
                    *(int*)((char*)this + 0xAC) = *(int*)(tokenValue + 8);
                    break;
                case 6: // Field: integer at 0xB0
                    tokenValue = streamReaderReadToken();
                    *(int*)((char*)this + 0xB0) = *(int*)(tokenValue + 8);
                    break;
                case 7: // Field: integer at 0xB4
                    tokenValue = streamReaderReadToken();
                    *(int*)((char*)this + 0xB4) = *(int*)(tokenValue + 8);
                    break;
                case 8: // Field: integer at 0xB8
                    tokenValue = streamReaderReadToken();
                    *(int*)((char*)this + 0xB8) = *(int*)(tokenValue + 8);
                    break;
                case 9: // Field: integer at 0xBC
                    tokenValue = streamReaderReadToken();
                    *(int*)((char*)this + 0xBC) = *(int*)(tokenValue + 8);
                    break;
                case 10: // Field: integer at 0xC0
                    tokenValue = streamReaderReadToken();
                    *(int*)((char*)this + 0xC0) = *(int*)(tokenValue + 8);
                    break;
                case 11: // Field: quaternion at 0x74 (4 ints)
                    streamReaderNextToken();
                    quadPtr = (int*)streamReaderGetTokenQuad();
                    if (quadPtr[0] != 0 || quadPtr[1] != 0 || quadPtr[2] != 0 || quadPtr[3] != 0) {
                        *(int*)((char*)this + 0x74) = quadPtr[0];
                        *(int*)((char*)this + 0x78) = quadPtr[1];
                        *(int*)((char*)this + 0x7C) = quadPtr[2];
                        *(int*)((char*)this + 0x80) = quadPtr[3];
                    }
                    break;
                case 12: // Field: quaternion at 0x8C (4 ints)
                    streamReaderNextToken();
                    quadPtr = (int*)streamReaderGetTokenQuad();
                    if (quadPtr[0] != 0 || quadPtr[1] != 0 || quadPtr[2] != 0 || quadPtr[3] != 0) {
                        *(int*)((char*)this + 0x8C) = quadPtr[0];
                        *(int*)((char*)this + 0x90) = quadPtr[1];
                        *(int*)((char*)this + 0x94) = quadPtr[2];
                        *(int*)((char*)this + 0x98) = quadPtr[3];
                    }
                    break;
                case 13: // Field: string handle at 0x60
                    streamReaderNextToken();
                    tokenValue = streamReaderGetTokenInt();
                    copyStringHandle((char*)this + 0x60, tokenValue);
                    break;
                case 14: // Field: string handle at 0x68
                    streamReaderNextToken();
                    tokenValue = streamReaderGetTokenInt();
                    copyStringHandle((char*)this + 0x68, tokenValue);
                    break;
                case 15: // Field: optional resource ID (stored in uVar5)
                    tokenValue = streamReaderReadToken();
                    uVar5 = *(uint32_t*)(tokenValue + 8);
                    break;
                case 16: // Field: resourceId at 0x84 and 0x9C
                    tokenValue = streamReaderReadToken();
                    uint32_t id = *(uint32_t*)(tokenValue + 8);
                    *(uint32_t*)((char*)this + 0x84) = id;
                    *(uint32_t*)((char*)this + 0x9C) = id;
                    break;
            }
            streamReaderAdvance(); // consume token? (FUN_0043b1a0)
        }

        // Ensure resource IDs are set; if not, generate default
        if (*(uint32_t*)((char*)this + 0x9C) == 0) {
            uint32_t defaultId = generateDefaultResourceId(uVar5);
            *(uint32_t*)((char*)this + 0x84) = defaultId;
            *(uint32_t*)((char*)this + 0x9C) = defaultId;
        }

        // If flag at 0x70 bit 0 is set and global default data exists, copy it
        if ((*(char*)((char*)this + 0x70) & 1) != 0 && g_defaultData != 0) {
            memcpyLarge((char*)this + 0x3C, g_defaultData, 0x8000);
        }
    }
};

// External functions (stubs for the called routines)
void streamReaderBegin(void* stream);
void streamReaderExpectMagic(void* stream, uint32_t magic);
bool streamReaderIsEnd();
int streamReaderReadToken(); // returns token pointer or index
int streamReaderGetTokenType();
int streamReaderGetTokenInt();
int* streamReaderGetTokenQuad();
void streamReaderNextToken();
void streamReaderAdvance();
void copyStringHandle(void* dest, int handle); // copies a string identifier
uint32_t generateDefaultResourceId(uint32_t hint);
void memcpyLarge(void* dest, void* src, uint32_t size);

extern void* g_defaultData; // DAT_0120e93c