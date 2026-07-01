//FUNC_NAME: updateAllCategories

#include <cstdint>

// Global data: array of 5 category entries, each containing a count and an unknown field.
// Address: 0x00e564f4
struct CategoryData {
    uint32_t count;   // +0x00
    uint32_t unknown; // +0x04
};

extern CategoryData g_categoryData[5]; // DAT_00e564f4

// Per-item processing function (address 0x009241b0)
void processCategoryItem(uint32_t category, uint32_t index, uint32_t subIndex);

void updateAllCategories(void)
{
    uint32_t category = 0;
    CategoryData *pData = g_categoryData;

    do {
        uint32_t index = 0;
        if (pData->count != 0) {
            do {
                processCategoryItem(category, index, 0);
                processCategoryItem(category, index, 1);
                index++;
            } while (index < pData->count);
        }
        category++;
        pData++;
    } while (category < 5);
}