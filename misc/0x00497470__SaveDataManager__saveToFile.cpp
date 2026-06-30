// FUNC_NAME: SaveDataManager::saveToFile
typedef unsigned int undefined4;
typedef unsigned long long undefined8;

// Binary file header structure (28 bytes)
struct RaceHeader {
    unsigned int magic;       // +0x00: "RACE" (0x45414352)
    unsigned int version;     // +0x04: 2
    unsigned int unk1;        // +0x08
    unsigned int unk2;        // +0x0C
    unsigned int unk3;        // +0x10
    unsigned int unk4;        // +0x14
    unsigned int unk5;        // +0x18
    unsigned int unk6;        // +0x1C
};

// Node in the internal linked list
struct SaveDataNode {
    SaveDataNode* pPrev;      // +0x00: previous pointer
    unsigned int field04;     // +0x04
    unsigned char payload[32];// +0x08 (four 8-byte chunks)
    unsigned int field28;     // +0x28: flag (0 or 1) – if 1, node is saved
    SaveDataNode* pNext;      // +0x2C: next pointer (offset 0x0C in undefined4* index)
};

// The main class (has a linked list at +0x30)
class SaveDataManager {
public:
    SaveDataNode* pListHead;  // +0x30: head of internal node list
    // ... other members

    bool saveToFile(const wchar_t* filename) {
        // Logging call
        FUN_00498850(6, DAT_00e35654);

        // Build a filtered list of nodes to save
        SaveDataNode* pFilteredList = nullptr;
        SaveDataNode* pNode = (pListHead != nullptr) ? *reinterpret_cast<SaveDataNode**>(reinterpret_cast<char*>(pListHead) + 0x30) : nullptr;

        while (pNode != nullptr) {
            if (pNode->field28 == 1) {
                // Add node to filtered list
                SaveDataNode* pNewNode = FUN_00498740(&pFilteredList, pNode);
                // Copy 32 bytes of payload from original node
                *(undefined8*)(&pNewNode->field04) = *(undefined8*)(&pNode->field04);
                *(undefined8*)(reinterpret_cast<char*>(pNewNode) + 0x10) = *(undefined8*)(reinterpret_cast<char*>(pNode) + 0x10);
                *(undefined8*)(reinterpret_cast<char*>(pNewNode) + 0x18) = *(undefined8*)(reinterpret_cast<char*>(pNode) + 0x18);
                *(undefined8*)(reinterpret_cast<char*>(pNewNode) + 0x20) = *(undefined8*)(reinterpret_cast<char*>(pNode) + 0x20);
                pNewNode->field28 = pNode->field28;
                pNewNode->field28 = pNode->field28; // Intentional double assign?
                // Also copies the next pointer at offset 0x2C? Not shown.
            }
            pNode = pNode->pNext; // next pointer at offset 0x2C
        }

        // Open binary file for writing
        FILE* file = nullptr;
        if (__wfopen_s(&file, filename, L"wb") != 0) {
            return false;
        }

        // Write header
        RaceHeader header;
        header.magic = 0x45414352;   // 'E','A','C','R' little-endian = "RACE"
        header.version = 2;
        // Other fields are zeroed (local_18, local_10)
        // header.unk1 = local_2c;  -> uninitialized local_2c used as unk1
        header.unk1 = 0; // original uses local_2c, assume 0
        header.unk2 = 0;
        header.unk3 = 0;
        header.unk4 = 0;
        header.unk5 = 0;
        header.unk6 = 0;
        _fwrite(&header, sizeof(RaceHeader), 1, file);

        // Now walk the filtered list and write each node's payload
        SaveDataNode* pWriteNode = pFilteredList;
        while (pWriteNode != nullptr) {
            // Write the original node pointer (4 bytes) – probably for relocation?
            _fwrite(&pWriteNode->pPrev, 4, 1, file); // write first 4 bytes of node
            // Write 16 bytes of data starting at offset 0x08 (payload)
            _fwrite(reinterpret_cast<char*>(pWriteNode) + 8, 16, 1, file);
            pWriteNode = pWriteNode->pNext;
        }

        _fclose(file);
        // Return success
        return true;
    }
};

// External function declarations (stubs)
extern void FUN_00498850(int, int);
extern SaveDataNode* FUN_00498740(SaveDataNode**, SaveDataNode*);
extern void FUN_00498180();
extern void FUN_009c8f10(void*);
extern void FUN_009c8eb0(void*);