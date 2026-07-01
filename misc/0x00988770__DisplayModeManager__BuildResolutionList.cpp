// FUNC_NAME: DisplayModeManager::BuildResolutionList

#include <cstdio>
#include <cstdlib>

class DisplayModeManager {
public:
    // Fields (offsets from this)
    // +0x6c: uint m_currentResolutionIndex
    // +0xbc: uint m_resolutionCount
    // +0xc0: float* m_resolutionData  // array of 12-byte entries (3 floats: width, height, refresh)
    // +0x110: int m_currentWidth
    // +0x114: int m_currentHeight? wait recheck: code uses +0x114 as width, +0x110 as height, +0x118 as refresh? Actually:
    //   *(float *)(iVar8 + *(int *)(param_1 + 0xc0)) == (float)*(int *)(param_1 + 0x114)
    //   pfVar1[1] == (float)*(int *)(param_1 + 0x110)
    //   pfVar1[2] == (float)*(int *)(param_1 + 0x118)
    // So +0x114 is width, +0x110 is height, +0x118 is refresh.
    // +0xe8: char m_resolutionString[64] // buffer for sprintf

    // External functions (assumed from same binary):
    // void FreeMemory(void* ptr); // 0x009c8f10
    // void LogEvent(const char* event, int a, const char* str, int b); // 0x005a04a0
    // bool BeginEnumeration(); // 0x0060e860
    // bool EnumDisplayModes(void* outData, void* outFreq, void* outFlags, void* outOther, bool includeInterlaced); // 0x0060ea60
    // void EndEnumeration(); // 0x00609aa0
    // void* AllocateMemory(int size); // 0x009c8e80
    // void ReadEnumerationResults(void* buffer); // 0x006099f0

    static const float kFloatAdjustment = 65536.0f; // DAT_00e44578

    bool BuildResolutionList() {
        // Free previous data if any
        if (m_resolutionData != nullptr) {
            FreeMemory(m_resolutionData);
            LogEvent("ClearResolutionList", 0, "gfxMenu", 0);
        }

        // Local buffer for enumeration
        char local_164[320]; // actually a structure, but we treat as buffer
        uint local_160 = 0;
        int local_c = 0;
        int local_8 = 0;
        int local_4 = 0;

        bool init = BeginEnumeration();
        bool includeInterlaced = !init;
        bool found = EnumDisplayModes(local_164, local_158, local_150, local_154, includeInterlaced);
        if (found) {
            // Retrieve count of modes
            ReadEnumerationResults(local_c + 8); // likely stores count into local_160
            m_resolutionCount = local_160;

            // Allocate memory for resolution data: 3 floats per mode * m_resolutionCount
            int size = m_resolutionCount * 12; // 3 * 4 bytes
            m_resolutionData = (float*)AllocateMemory(size);
            m_currentResolutionIndex = 0;

            if (m_resolutionCount > 0) {
                int* enumData = (int*)(local_164 + 8); // skip header? actual data starts at local_164+8
                int offset = 0;
                for (uint i = 0; i < m_resolutionCount; i++) {
                    int widthInt = enumData[-2];
                    int heightInt = enumData[-1];
                    int refreshInt = enumData[0];

                    // Convert int to float, handling negative values as unsigned
                    float width = (widthInt < 0) ? (float)widthInt + kFloatAdjustment : (float)widthInt;
                    float height = (heightInt < 0) ? (float)heightInt + kFloatAdjustment : (float)heightInt;
                    float refresh = (refreshInt < 0) ? (float)refreshInt + kFloatAdjustment : (float)refreshInt;

                    float* mode = &m_resolutionData[offset / 4];
                    mode[0] = width;
                    mode[1] = height;
                    mode[2] = refresh;

                    // Check if this matches current display mode (stored as ints but compared as floats)
                    float currentWidth = (float)m_currentWidth;
                    float currentHeight = (float)m_currentHeight;
                    float currentRefresh = (float)m_currentRefresh;
                    if (width == currentWidth && height == currentHeight && refresh == currentRefresh) {
                        m_currentResolutionIndex = i;
                    }

                    // Format resolution string
                    sprintf(m_resolutionString, "%d x %d @ %dHz",
                            (int)width, (int)height, (int)refresh);
                    LogEvent("AddResolutionOption", 0, m_resolutionString, 0);

                    offset += 12;
                    enumData += 3; // each entry is 3 ints? actually stepping by 4 ints (since enumData[0], then skipping 1? Wait analysis: piVar6 = piVar6 + 4, so 4 ints per entry. But we only used -2, -1, 0. The fourth maybe unused.)
                }
            }

            FreeMemory(local_164);
            EndEnumeration();
            return true;
        }

        EndEnumeration();
        return false;
    }

private:
    // Forward declarations of external functions (implemented elsewhere)
    void FreeMemory(void* ptr);
    void LogEvent(const char* event, int a, const char* str, int b);
    bool BeginEnumeration();
    bool EnumDisplayModes(void* outData, void* outFreq, void* outFlags, void* outOther, bool includeInterlaced);
    void EndEnumeration();
    void* AllocateMemory(int size);
    void ReadEnumerationResults(void* buffer);

    float* m_resolutionData;       // +0xc0
    uint m_resolutionCount;        // +0xbc
    uint m_currentResolutionIndex; // +0x6c
    int m_currentWidth;            // +0x114
    int m_currentHeight;           // +0x110
    int m_currentRefresh;          // +0x118
    char m_resolutionString[64];   // +0xe8
};