// FUNC_NAME: UIListRenderer::drawEntryList
// Address: 0x005f2830
// Draws a list of UI entries with alternating scale offsets based on an active entry's scale.
// Each entry is processed with a texture, position, scale, alpha, and rotation.
// Parameters:
//   pRenderContext - rendering context pointer (used to get a texture pointer at offset +4)
//   pListData - list data structure containing entry array, count, flags, rotation, and active entry pointer
//   pAlphaMultiplier - input alpha multiplier (float pointer)
// Returns 1 if processing occurred, 0 otherwise.

#include <cstdint>

// Constants from data section
static const float DEFAULT_SCALE = *reinterpret_cast<float*>(0x0112750c);  // base scale
static const float MAX_SCALE = *reinterpret_cast<float*>(0x00e44564);      // maximum scale (used for alternating)

// Forward declarations of called functions
void FUN_005f2680();               // render state push/setup
void FUN_005dbc10(int centerX, int centerY, double scale, double alpha, double rotation); // draw sprite
uint32_t FUN_005f37b0();           // get next texture handle
void FUN_005f1400(uint32_t textureHandle); // apply/use texture

int32_t UIListRenderer::drawEntryList(void* pRenderContext, void* pListData, float* pAlphaMultiplier)
{
    // pListData structure (custom struct) offsets:
    // +0x00: unknown
    // +0x04: unknown
    // +0x08: pointer to "active entry" (used for scale override)
    // +0x0c: array of pointers to entries (start)
    // +0x6c: flags byte (bit 2: ?)
    // +0x6f: number of entries (byte)
    // +0x54: rotation angle (float)
    
    // Entry structure offsets:
    // +0x00: unknown
    // +0x04: unknown
    // +0x08: flags byte (bit 2: override default scale with +0x24)
    // +0x0c: texture pointer (set from pRenderContext+4)
    // +0x10: ushort flags (bit 0x100: "selected" indicator)
    // +0x1c: base position (byte, 0-255)
    // +0x1d: byte (set to 1 when clearing selected flag)
    // +0x24: override scale (float, used if bit 2 set in +0x08)

    if (pRenderContext != nullptr && pListData != nullptr)
    {
        void* activeEntry = *reinterpret_cast<void**>(static_cast<char*>(pListData) + 0x08);
        if (activeEntry != nullptr)
        {
            // Get base scale; may be overridden by active entry
            float currentScale = DEFAULT_SCALE;
            uint8_t activeFlags = *reinterpret_cast<uint8_t*>(static_cast<char*>(activeEntry) + 0x08);
            if (activeFlags & 0x02)
            {
                currentScale = *reinterpret_cast<float*>(static_cast<char*>(activeEntry) + 0x24);
            }

            // Iterate over entry array
            void** entryArrayStart = reinterpret_cast<void**>(static_cast<char*>(pListData) + 0x0c);
            uint32_t entryCount = *reinterpret_cast<uint8_t*>(static_cast<char*>(pListData) + 0x6f);
            void** entryArrayEnd = entryArrayStart + entryCount;

            bool alternatingFlag = false;
            void** currentEntryPtr = entryArrayStart;

            if (currentEntryPtr < entryArrayEnd)
            {
                do
                {
                    void* entry = *currentEntryPtr;
                    if (entry != nullptr)
                    {
                        // Scale base position by alpha multiplier to produce x/y coordinate
                        float basePos = static_cast<float>(*reinterpret_cast<uint8_t*>(static_cast<char*>(entry) + 0x1c));
                        int16_t scaledPos = static_cast<int16_t>(basePos * *pAlphaMultiplier);

                        // Call setup (e.g., push state)
                        FUN_005f2680();

                        // Determine scale for this entry
                        float scaleValue;
                        bool clearSelected = false;
                        if (alternatingFlag)
                        {
                            // Even entries: scale = currentScale
                            scaleValue = currentScale;
                            // Check if list flags allow clearing selected flag
                            if ((*reinterpret_cast<uint8_t*>(static_cast<char*>(pListData) + 0x6c) & 0x04) != 0)
                            {
                                uint16_t entryFlags = *reinterpret_cast<uint16_t*>(static_cast<char*>(entry) + 0x10);
                                if (entryFlags & 0x0100)
                                {
                                    // Clear selected flag and set indicator byte
                                    *reinterpret_cast<uint16_t*>(static_cast<char*>(entry) + 0x10) &= ~0x0100;
                                    *reinterpret_cast<uint8_t*>(static_cast<char*>(entry) + 0x1d) = 1;
                                }
                            }
                        }
                        else
                        {
                            // Odd entries: scale = MAX_SCALE - currentScale
                            scaleValue = MAX_SCALE - currentScale;
                            // Check if list flags do NOT allow clearing selected flag
                            if ((*reinterpret_cast<uint8_t*>(static_cast<char*>(pListData) + 0x6c) & 0x04) == 0)
                            {
                                uint16_t entryFlags = *reinterpret_cast<uint16_t*>(static_cast<char*>(entry) + 0x10);
                                if (entryFlags & 0x0100)
                                {
                                    // Clear selected flag and set indicator byte
                                    *reinterpret_cast<uint16_t*>(static_cast<char*>(entry) + 0x10) &= ~0x0100;
                                    *reinterpret_cast<uint8_t*>(static_cast<char*>(entry) + 0x1d) = 1;
                                }
                            }
                        }

                        // Draw the entry sprite
                        float rotation = *reinterpret_cast<float*>(static_cast<char*>(pListData) + 0x54);
                        FUN_005dbc10(scaledPos, scaledPos, static_cast<double>(scaleValue),
                                     static_cast<double>(*pAlphaMultiplier), static_cast<double>(rotation));

                        // Copy texture pointer from render context into entry
                        *reinterpret_cast<void**>(static_cast<char*>(entry) + 0x0c) = *reinterpret_cast<void**>(static_cast<char*>(pRenderContext) + 0x04);

                        // Get next texture and apply it
                        uint32_t textureHandle = FUN_005f37b0();
                        FUN_005f1400(textureHandle);
                    }

                    alternatingFlag = !alternatingFlag;
                    currentEntryPtr++;
                } while (currentEntryPtr < entryArrayEnd);

                return 1;
            }
        }
    }
    return 0;
}