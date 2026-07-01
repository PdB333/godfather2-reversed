// FUNC_NAME: FamilyManager::refreshFamilyMemberList
// Address: 0x009171f0
// Role: Rebuilds the array of family member data (16-byte entries) from two sources:
//   - A list of family members (from getFamilyList())
//   - A single player family entry (from getPlayerFamily())
// The array is stored at this+0x7c, count at this+0x80.

#include <cstdint>

// Forward declarations for external functions
void* __fastcall getFamilyManagerSingleton(); // FUN_00ad8d40
void __fastcall freeArray(void* ptr);         // FUN_009c8f10
void* __fastcall allocateArray(int size);     // FUN_009c8e80
void __fastcall copy16ByteData(void* dst, void* src); // FUN_00ad8dd0

// 16-byte structure for a family member entry
struct FamilyMemberData {
    uint64_t field0; // +0x00
    uint64_t field8; // +0x08
};

// Virtual table offsets for the family list object (piVar2)
struct FamilyList {
    virtual int getCount();          // vtable+0x0c
    virtual void* getItem(int idx);  // vtable+0x28
};

// Virtual table offsets for a family member item
struct FamilyMemberItem {
    virtual void* getMemberData();   // vtable+0x08
};

// Virtual table offsets for member data
struct MemberData {
    virtual int getID();             // vtable+0x04
    virtual int64_t getValue();      // vtable+0x08
};

// Virtual table offsets for the player family object (piVar1)
struct PlayerFamily {
    virtual void* getPlayerFamilyData(); // vtable+0x28
};

// Class that holds the family member array
class FamilyManager {
public:
    FamilyMemberData* memberArray; // +0x7c
    int memberCount;               // +0x80

    void refreshFamilyMemberList() {
        // Get the singleton manager (e.g., FamilyManager::getInstance())
        void* manager = getFamilyManagerSingleton();
        if (manager == nullptr) return;

        // Get the family list and player family objects via virtual calls
        FamilyList* familyList = (FamilyList*)(*(void***)manager)[0x44](); // vtable+0x44
        PlayerFamily* playerFamily = (PlayerFamily*)(*(void***)manager)[0x48](); // vtable+0x48
        if (familyList == nullptr || playerFamily == nullptr) return;

        // Free the old array if it exists
        if (memberArray != nullptr) {
            freeArray(memberArray);
            memberArray = nullptr;
        }
        memberCount = 0;

        // Get the number of family members
        int numMembers = familyList->getCount();
        if (numMembers == 0) {
            numMembers = 1; // At least one slot for the player family
        } else {
            numMembers += 1; // +1 for the player family entry
        }

        // Allocate array of FamilyMemberData (size = numMembers * sizeof(FamilyMemberData))
        int allocSize = numMembers * sizeof(FamilyMemberData);
        memberArray = (FamilyMemberData*)allocateArray(allocSize);
        if (memberArray == nullptr) return;

        // Initialize each element with default constructor (vector_constructor_iterator)
        // This is handled by allocateArray internally (calls constructor at LAB_00565e00)

        // Iterate over family list items
        for (int i = 0; i < numMembers - 1; i++) {
            void* item = familyList->getItem(i);
            if (item == nullptr) continue;

            FamilyMemberItem* memberItem = (FamilyMemberItem*)(*(void***)item)[0x08](); // vtable+0x08
            if (memberItem == nullptr) continue;

            MemberData* data = (MemberData*)(*(void***)memberItem)[0x04](); // vtable+0x04
            if (data == nullptr) continue;

            int64_t value = data->getValue(); // vtable+0x08
            if (value <= 0) continue;

            // Copy the 16-byte data from the member
            FamilyMemberData* src = (FamilyMemberData*)copy16ByteData(data);
            FamilyMemberData* dst = &memberArray[memberCount];
            *dst = *src; // 16-byte copy (two 64-bit fields)
            memberCount++;
        }

        // Add the player family entry
        void* playerData = playerFamily->getPlayerFamilyData(); // vtable+0x28
        if (playerData != nullptr) {
            FamilyMemberData* src = (FamilyMemberData*)copy16ByteData(playerData);
            FamilyMemberData* dst = &memberArray[memberCount];
            *dst = *src;
            memberCount++;
        }
    }
};