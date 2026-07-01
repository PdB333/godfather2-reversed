// FUNC_NAME: BuildingManager::updateBuildingTypeSelection
// Address: 0x009525f0
// Processes a building selection event: iterates the building ID array to find matching building,
// updates selection index, handles deselection of previous highlight, and optionally sets active selection.

#include <cstdint>

class BuildingManager {
public:
    // +0x5C: number of entries in building ID array
    int m_buildingCount; // offset 0x5C
    // +0x58: pointer to array of building IDs (int)
    int* m_buildingIDs; // offset 0x58
    // +0x78: index of currently highlighted building (for visual feedback)
    int m_highlightedIndex; // offset 0x78
    // +0x48: flag indicating if highlighting is active
    char m_highlightedActive; // offset 0x48
    // +0xA0: index of the newly selected building (after matching)
    int m_selectedIndex; // offset 0xA0
    // +0xA4: subtype for the selection (e.g., demolition/construction)
    char m_selectionSubtype; // offset 0xA4
    // +0x80: index of active selection (used when param_4 is true)
    int m_activeSelectionIndex; // offset 0x80
    // +0x98: building pointer or index returned from getBuildingByIndex
    int m_activeSelectionBuilding; // offset 0x98

    void updateBuildingTypeSelection(Building* building, char subtype, bool setActive);
    // Internal helpers (declared elsewhere):
    void selectBuilding(int index); // FUN_00952030
    void beginSelectionUpdate(); // FUN_009523e0
    int findBuildingIndex(int* buildingPtr); // FUN_00486770 (converts building ptr to index)
    void deselectPreviousHighlight(int index, bool); // FUN_00956a50
    void notifyUISelection(void* uiMgr); // FUN_0097b8e0
    int getBuildingByIndex(int buildingPtr); // FUN_0095a800
};

// Address 0x009525f0
void BuildingManager::updateBuildingTypeSelection(Building* building, char subtype, bool setActive) {
    int index = -1;
    if (building == nullptr) {
        // Clear selection: if there is a previous highlight, deselect it
        if (m_highlightedActive) {
            selectBuilding(m_buildingCount - 1); // decreased by 1? Actually FUN_00952030((m_highlightedActive != 0) - 1)
        }
        m_selectedIndex = -1;
    } else {
        // Start selection update transaction
        beginSelectionUpdate();

        // Iterate through building ID array to find the given building
        for (unsigned int i = 0; i < static_cast<unsigned int>(m_buildingCount); ++i) {
            if (m_buildingIDs[i] == *(int*)(building + 0xC4)) { // building's ID at offset 0xC4
                if (static_cast<int>(i) >= 0) {
                    // Deselect any previously highlighted building
                    selectBuilding(i); // FUN_00952030(i); note: this function may take index and deselect others
                    int buildingPtr = *(int*)(building + 0x38); // offset 0x38 in building structure
                    int newIndex = findBuildingIndex(&buildingPtr);
                    if (newIndex >= 0) {
                        m_selectedIndex = newIndex;
                        notifyUISelection("UpdateBuildingTypeSelection", 0, 0x00d8bc74, 0); // FUN_005a04a0

                        // If there is a previous highlighted building and highlighting is active, deselect it
                        if (m_highlightedIndex != -1 && m_highlightedActive) {
                            deselectPreviousHighlight(m_highlightedIndex, 0); // FUN_00956a50
                        }
                        // Store the selection subtype
                        m_selectionSubtype = subtype;
                    }
                }
                break;
            }
        }
    }

    // Notify UI of the change
    void* uiMgr = (void*)(*(code**)(*(int*)this + 0x9C))(); // vtable call, get UI manager
    notifyUISelection(uiMgr); // FUN_0097b8e0

    if (setActive) {
        if (index >= 0) {
            m_activeSelectionIndex = index;
            int buildingVal = *(int*)(building + 0x38); // re-fetch building pointer (maybe)
            m_activeSelectionBuilding = getBuildingByIndex(buildingVal); // FUN_0095a800
        } else {
            m_activeSelectionIndex = -1;
            m_activeSelectionBuilding = 0;
        }
    }
}