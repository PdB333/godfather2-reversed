// Xbox PDB: EARS_Apt_UIFamilyInfo_ColorFamilyInfo
// FUNC_NAME: MonopolyManager::loadFamilyTreeStub
// Address: 0x0092a290
// Reads family tree stub files (node counts, member IDs) and updates per-node color/alpha based on member role and status.

#include <cstdio>
#include <cstdlib> // atol

// Forward declarations of known functions (simulated)
extern int FormatString(char* out, int maxLen, const char* fmt, ...); // FUN_005c4630
extern void WriteFloatToFile(const char* path, float value); // FUN_0059ef40 (writes 3 floats? or just set color?)
extern void ReadIntFromFile(const char* path, int* out); // FUN_0059fb30
extern void ReadStringFromFile(const char* path, char* out, int maxLen); // FUN_0059f8d0
extern int GetMissionAssetID(const char* missionName); // FUN_004dafd0
extern bool GetMissionCompletionState(int assetID, float* outProgress); // FUN_008934e0
extern int GetCharacterOrSomething(); // FUN_0090a5a0
extern bool IsCharacterAlive(int charID); // FUN_008ff210
extern int GetSomeGlobal(); // FUN_008fdfb0
extern int GetNodeColorIndex(int characterIdx); // FUN_0092a080
extern void WriteIntToFile(const char* path, int value); // FUN_0059ee00

// Color table at 0xe565a0: each entry is 4 bytes (R, G, B, Alpha)
static const unsigned char kColorTable[][4] = {
    // ... filled from binary data
};

void loadFamilyTreeStub(const char* familyPath)
{
    char filePath[512];  // local_480
    char nameBuffer[128]; // local_280
    char memberID[512];  // combined from local_200 and local_1ff (512 bytes total)
    int nodeCount;
    int nodeIndex;

    // Build base path: "%s/ft_stub/ft/bg/" -> used as output? Actually it writes color to this path
    FormatString(filePath, sizeof(filePath), "%s/ft_stub/ft/bg/", familyPath);
    WriteFloatToFile(filePath, /* some color? */ 0.0f); // unclear what floats are written

    nodeCount = 0;
    FormatString(filePath, sizeof(filePath), "%s/ft_stub/ft.node_count", familyPath);
    ReadIntFromFile(filePath, &nodeCount);

    for (nodeIndex = 0; nodeIndex < nodeCount; nodeIndex++)
    {
        int colorIndex = 0;

        // Read member ID string
        FormatString(filePath, sizeof(filePath), "%s/ft_stub/ft/node_%d.memberId", familyPath, nodeIndex);
        memberID[0] = '\0';
        ReadStringFromFile(filePath, memberID, sizeof(memberID));

        // Determine colorIndex based on first character of member ID
        switch (memberID[0])
        {
        case 'D': // 0x44
        case 'd': // 0x64 (100 decimal)
        {
            // Don: check if he has been killed via mission
            FormatString(filePath, sizeof(filePath), "%s/ft_stub/ft.don_name", familyPath);
            char donName[512];
            donName[0] = '\0';
            ReadStringFromFile(filePath, donName, sizeof(donName));

            char missionName[128];
            FormatString(missionName, sizeof(missionName), "DON_%s_KILLED", donName);
            int assetID = GetMissionAssetID(missionName);
            float completion = 0.0f;
            bool found = GetMissionCompletionState(assetID, &completion);
            if (!found || completion == _DAT_00d577a0) {
                // Mission not triggered or not completed? _DAT_00d577a0 is some float (maybe 0.0)
                colorIndex = 9;
            } else {
                colorIndex = 10;
            }
            break;
        }
        case 'H': // 0x48
        case 'h': // 0x68
        {
            // Hitman (or similar): check if character is alive
            int charID = GetMissionAssetID(memberID); // memberID is the char name
            if (IsCharacterAlive(charID))
            {
                int aliveCheck = GetSomeGlobal(); // maybe returns something
                if (aliveCheck != 0)
                {
                    colorIndex = GetNodeColorIndex(aliveCheck);
                }
            }
            break;
        }
        case 'P': // 0x50
        case 'p': // 0x70
        {
            // Possibly Capo: check if there's additional data after the letter
            if (memberID[1] == '\0')
            {
                colorIndex = 8;
            }
            else
            {
                long index = atol(&memberID[1]); // parse numeric part
                // DAT_0112989c + 0x18 is some base pointer; each entry is 0x24 bytes
                if (*(int*)(*(int*)(0x0112989c) + 0x18 + index * 0x24) != 0)
                {
                    int somePtr = GetCharacterOrSomething();
                    if (somePtr != 0)
                    {
                        colorIndex = GetNodeColorIndex(somePtr);
                    }
                }
            }
            break;
        }
        // default: colorIndex remains 0
        }

        // Now write color and alpha for this node
        FormatString(filePath, sizeof(filePath), "%s/ft_stub/ft/node_%d/", familyPath, nodeIndex);
        // Write RGB as floats (0-1) derived from color table
        WriteFloatToFile(filePath,
                         (float)kColorTable[colorIndex][0],
                         (float)kColorTable[colorIndex][1],
                         (float)kColorTable[colorIndex][2]);

        FormatString(filePath, sizeof(filePath), "%s/ft_stub/ft/node_%d._alpha", familyPath, nodeIndex);
        int alphaInt = (kColorTable[colorIndex][3] * 100) / 255;
        WriteIntToFile(filePath, alphaInt);
    }
}