// FUNC_NAME: ColorScaleManager::initializeColorScales

#include <cstdint>

// ------------------------------------------------------------------
// External engine functions (EARS memory/context helpers)
// FUN_0060a380: allocate new color scale resource handle
int __fastcall colorScaleAllocHandle();

// FUN_0060a580: assign a source value to a given handle's internal data
int __fastcall colorScaleAssign(int handle, int sourceValue);

// FUN_0060a2e0: obtain handle from a table entry pointer
int __fastcall colorScaleGetHandleFromTable(int tableEntryPointer);

// ------------------------------------------------------------------
// Global static tables (addresses reverse‑engineered from Ghidra)
extern int g_colorScaleSourceData[3][12];     // at PTR_s_color_scale_010c2150
extern int g_presetTable[20];               // pointers at PTR_PTR_011281b0
extern int g_presetSourceData[20][15];      // array at 0x10c2180 (sum of offsets)

// ------------------------------------------------------------------
// Class structure inferred from offsets
class ColorScaleManager {
public:
    void __thiscall initializeColorScales();

private:
    // +0x1E0, +0x1E4, +0x1E8 : three color scale resource handles (third is at +0x1E8)
    int m_colorScaleH0;        // +0x1E0
    int m_colorScaleH1;        // +0x1E4
    int m_colorScaleH2;        // +0x1E8

    // +0x23C : 3 * 12 ints = 0x90 bytes (color scale source data per handle)
    int m_colorScaleData[3][12]; // +0x23C

    // +0x1EC : 20 preset handles (20 * 4 = 80 bytes)
    int m_presetHandles[20];    // +0x1EC

    // +0x2CC : 20 * 15 ints = 0x4B0 bytes (preset data per handle)
    int m_presetData[20][15];   // +0x2CC
};

// ------------------------------------------------------------------
// Implementation
void __thiscall ColorScaleManager::initializeColorScales()
{
    // === First part: three color scales with 12 values each ===
    for (int i = 0; i < 3; ++i)
    {
        // Allocate a new color scale handle
        int handle;
        if (i == 2)
        {
            handle = colorScaleAllocHandle();
            m_colorScaleH2 = handle;               // +0x1E8
        }
        else
        {
            handle = colorScaleAllocHandle();
            if (i == 0)
                m_colorScaleH0 = handle;           // +0x1E0
            else
                m_colorScaleH1 = handle;           // +0x1E4
        }

        // Fill the 12‑slot data block for this scale
        int *dest = &m_colorScaleData[i][0];       // +0x23C + i*0x30
        for (int j = 0; j < 12; ++j)
        {
            int src = g_colorScaleSourceData[i][j]; // static table
            dest[j] = colorScaleAssign(handle, src);
        }
    }

    // === Second part: 20 presets with 15 values each ===
    int *handlePtr = m_presetHandles;              // starts at +0x1EC
    int *dataPtr   = &m_presetData[0][0];          // starts at +0x2CC

    // Compute base offset so that (dataPtr + offset) always points to the
    // next source element in the global preset array.  Initially:
    //   offset = 0x10C1EB4 - this
    // After each outer iteration offset is decreased by 0x3C so that the sum
    // (dataPtr + offset) remains constant, effectively linearising the source.
    int sourceOffset = 0x10C1EB4 - reinterpret_cast<int>(this);

    for (int i = 0; i < 20; ++i)
    {
        // Obtain handle via the pointer table
        int tableEntry = g_presetTable[i];
        int handle = colorScaleGetHandleFromTable(tableEntry);
        *handlePtr = handle;

        // Fill the 15‑slot preset data block
        for (int j = 0; j < 15; ++j)
        {
            int src = *( reinterpret_cast<int*>(
                            reinterpret_cast<int>(dataPtr) + sourceOffset )
                        );
            *dataPtr = colorScaleAssign(handle, src);
            ++dataPtr;               // advance by one int
        }

        ++handlePtr;                 // next handle slot
        sourceOffset -= 0x3C;        // step backward to keep next sum constant
    }
}