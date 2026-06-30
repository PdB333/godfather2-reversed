// FUNC_NAME: containsAllIds
// Address: 0x00565530
// Role: Checks if the container holds all specified IDs in its item list.

// Offsets:
//   +0x24: Item** items   (array of pointers to items)
//   +0x3c: uint32_t itemId (within each item struct)
//   +0x124: uint32_t numItems

struct Item {
    uint32_t id;   // +0x3c
};

class SomeContainer {
public:
    Item** items;       // +0x24
    uint32_t numItems;  // +0x124

    bool __thiscall hasAllIds(uint32_t* ids) {
        uint32_t count = ids[0];
        if (count == 0) {
            return true;
        }

        uint32_t i = 0;
        do {
            ids++;   // move past count to first actual ID (or to next ID on subsequent iterations)
            uint32_t j = 0;
            if (numItems == 0) {
                return false;
            }

            Item** iter = items;
            while ((*iter)->id != *ids) {
                j++;
                iter++;
                if (j >= numItems) {
                    return false;
                }
            }
            i++;
        } while (i < count);

        return true;
    }
};