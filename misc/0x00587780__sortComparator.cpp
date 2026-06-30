// FUNC_NAME: sortComparator
// Address: 0x00587780
// This function appears to be a comparator for sorting items, comparing two structures
// pointed to by a and b. It extracts primary, secondary, and tertiary keys based on flags.
// The return value is a 32-bit key that encodes the sort order, possibly with a tiebreaker.

#include <cstdint>

// Structure offsets:
// +0x00: primaryKey (int)
// +0x04: secondaryKey (int)
// +0x14: tertiaryKey (int)
// +0x2C: flags (bit 0x20 = 32 indicates "use secondaryKey if primaryKey >= 2")

uint32_t __fastcall sortComparator(void* unused, int* itemA, int* itemB) {
    uint32_t flagA = itemA[11] & 0x20; // offset +0x2C, bit 5
    uint32_t flagB = itemB[11] & 0x20;

    int primaryA, primaryB;
    int secondaryA, secondaryB;

    // Determine effective primary for A
    if (flagA != 0 && itemA[0] >= 2) {
        primaryA = itemA[1]; // use secondary key
    } else {
        primaryA = itemA[0]; // use primary key
    }
    // Store original primaryA for later (itemA[0] is needed)
    int origPrimaryA = itemA[0];

    // Determine effective primary for B
    if (flagB != 0 && itemB[0] >= 2) {
        primaryB = itemB[1];
    } else {
        primaryB = itemB[0];
    }
    int origPrimaryB = itemB[0];

    if (primaryA == primaryB) {
        // Tie on effective primary; use tertiary keys if applicable
        int tertiaryA;
        if (flagA != 0 && origPrimaryA >= 4) {
            tertiaryA = itemA[5]; // +0x14
        } else {
            tertiaryA = 0;
        }

        if (flagB != 0 && origPrimaryB > 3) {
            // Return combined key: high 24 bits from (itemB[5] >> 8), low 8 bits from comparison
            return ( (itemB[5] >> 8) << 8 ) | ( (uint32_t)(tertiaryA < itemB[5]) );
        } else {
            return (uint32_t)(tertiaryA < 0); // always false (0)
        }
    } else {
        // Different effective primaries; return comparison based on original primaries
        // If flag set and originalPrimary > 1, use secondary key for the first item
        int compA = (flagA != 0 && origPrimaryA > 1) ? itemA[1] : itemA[0];
        int compB;
        if (flagB != 0 && origPrimaryB > 1) {
            compB = itemB[1];
        } else {
            compB = origPrimaryB;
        }
        // Return combined key: high 24 bits from (compA >> 8), low 8 from (compA < compB)
        return ( (compA >> 8) << 8 ) | ( (uint32_t)(compA < compB) );
    }
}