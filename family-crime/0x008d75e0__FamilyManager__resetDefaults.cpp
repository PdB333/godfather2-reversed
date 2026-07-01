// FUNC_NAME: FamilyManager::resetDefaults
// Function address: 0x008d75e0
// Resets family manager data to default sentinel values.
// Initializes two dynamic arrays and a fixed array of 5 elements.

extern int kDefaultFamilyValue; // _DAT_00d5780c
extern int kDefaultCrewStatus;  // _DAT_00d5c458

struct FamilyManager
{
    int field_0x28;          // +0x28: family health or threshold
    int* arr1;               // +0x2c: pointer to array of structures (size 0x2c)
    int arr1Count;           // +0x30: number of elements in arr1
    int* arr2;               // +0x38: pointer to array of structures (size 0x18)
    int arr2Count;           // +0x3c: number of elements in arr2
    int fixedArray[5];       // +0x54: fixed array of 5 ints, stride 0x14
};

void __thiscall FamilyManager::resetDefaults()
{
    // Set main threshold
    this->field_0x28 = kDefaultFamilyValue;

    // Reset arr1: each element has two fields at +0x0c and +0x20
    if (this->arr1Count != 0)
    {
        for (int i = 0; i < this->arr1Count; i++)
        {
            int* base1 = &this->arr1[i * 11]; // 0x2c bytes = 11 ints
            base1[3] = kDefaultCrewStatus;    // offset 0x0c
            base1[8] = kDefaultCrewStatus;    // offset 0x20 (0x0c + 20)
        }
    }

    // Reset arr2: each element has one field at +0x14
    if (this->arr2Count != 0)
    {
        for (int i = 0; i < this->arr2Count; i++)
        {
            int* base2 = &this->arr2[i * 6];  // 0x18 bytes = 6 ints
            base2[5] = kDefaultFamilyValue;   // offset 0x14
        }
    }

    // Reset fixed array of 5 ints at +0x54 (each int is 4 bytes, stride 0x14 = 20 bytes => actually only one int per slot? No, it's 5 separate fields spaced 0x14 apart)
    // Since the original code sets offsets 0x54, 0x68, 0x7c, 0x90, 0xa4 individually, we write them directly.
    *(int*)((char*)this + 0x54) = kDefaultFamilyValue;
    *(int*)((char*)this + 0x68) = kDefaultFamilyValue;
    *(int*)((char*)this + 0x7c) = kDefaultFamilyValue;
    *(int*)((char*)this + 0x90) = kDefaultFamilyValue;
    *(int*)((char*)this + 0xa4) = kDefaultFamilyValue;
}