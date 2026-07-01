// FUNC_NAME: CountryManager::initCountries

// Unknown class representing a country item
class Country {
public:
    char field_0x80[32]; // +0x80: country name string (null-terminated)
};

// Virtual interface for the country list manager
class CountryListManager {
public:
    virtual int getCount() = 0;          // vtable[0]
    virtual Country* getItem(uint index) = 0; // vtable[1]
};

// CountryManager class – handles country initialization and lookup
class CountryManager {
public:
    int m_count;                // +0x58: number of countries
    uint m_matchedIndex;        // +0x70: index of matched country
    char* m_targetCountryName;  // +0x74: target country name to find

    void initCountries();
};

// Global pointer to some base object (actual offset after adjustment)
extern void* gGlobalBase; // DAT_012234b8

void __thiscall CountryManager::initCountries()
{
    // Compute base from global pointer
    int base;
    if (gGlobalBase == nullptr) {
        base = 0;
    } else {
        base = (int)gGlobalBase - 0xc;
    }

    // Get country list manager from base +0x234
    CountryListManager* countryMgr = *(CountryListManager**)(base + 0x234);

    // Retrieve total count and store it
    int count = countryMgr->getCount();
    m_count = count;

    // Log initialization start
    FUN_005a04a0("InitCountries", 0, &DAT_00d8d668, 0);

    // Iterate over all countries
    uint idx = 0;
    count = countryMgr->getCount(); // reload count (may have changed? or just coding style)
    if (count != 0) {
        do {
            Country* country = countryMgr->getItem(idx);
            // Compare country name with target name
            if (__stricmp(country->field_0x80, m_targetCountryName) == 0) {
                m_matchedIndex = idx;
            }

            // Log each added country
            FUN_005a04a0("AddCountry", 0, &DAT_00d8d668, 1, country);

            idx++;
            count = countryMgr->getCount(); // update count each iteration
        } while (idx < (uint)count);
    }
}