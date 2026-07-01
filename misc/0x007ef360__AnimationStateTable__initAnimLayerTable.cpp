// FUNC_NAME: AnimationStateTable::initAnimLayerTable
// Address: 0x007ef360
// Role: Initializes an array of animation layer entries with fixed IDs and a shared pointer from this+0x4.
// The array starts at offset 0x30, each entry is 0x1C bytes. Only the first two fields (ID and pointer) are set.

class AnimationStateTable {
public:
    // Structure for each animation layer entry (size 0x1C)
    struct AnimLayerEntry {
        int layerId;      // +0x00
        void* sharedPtr;  // +0x04
        // remaining 0x18 bytes unknown (padding or other data)
    };

    // Member at offset +0x4 (likely a pointer to shared animation data)
    void* m_sharedAnimData; // +0x04

    // Array of 6 layer entries starting at +0x30
    AnimLayerEntry m_layerEntries[6]; // +0x30

    // Initializes the layer entries with fixed IDs and the shared pointer
    void __fastcall initAnimLayerTable() {
        // Layer 0: ID = 0xB (11)
        m_layerEntries[0].layerId = 0xB;
        m_layerEntries[0].sharedPtr = m_sharedAnimData;

        // Layer 1: ID = 0x11 (17)
        m_layerEntries[1].layerId = 0x11;
        m_layerEntries[1].sharedPtr = m_sharedAnimData;

        // Layer 2: ID = 0x17 (23)
        m_layerEntries[2].layerId = 0x17;
        m_layerEntries[2].sharedPtr = m_sharedAnimData;

        // Layer 3: ID = 0x1D (29)
        m_layerEntries[3].layerId = 0x1D;
        m_layerEntries[3].sharedPtr = m_sharedAnimData;

        // Layer 4: ID = 0x1D (29)
        m_layerEntries[4].layerId = 0x1D;
        m_layerEntries[4].sharedPtr = m_sharedAnimData;

        // Layer 5: ID = 0x1D (29)
        m_layerEntries[5].layerId = 0x1D;
        m_layerEntries[5].sharedPtr = m_sharedAnimData;
    }
};