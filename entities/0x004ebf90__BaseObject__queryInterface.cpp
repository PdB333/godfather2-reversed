// FUNC_NAME: BaseObject::QueryInterface
// Function at 0x004ebf90: Standard COM-style QueryInterface implementation for a base object.
// Supports two known interface IDs: 0xF3C619FF and 0xFFD2E5B1 (in hex, constants negated in decompiled code).

#include <cstdint>

// Assume BaseObject is the base class for all EARS engine objects.
class BaseObject
{
public:
    // Standard QueryInterface pattern.
    // Returns 1 (S_OK) if the requested interface is supported, 0 (E_NOINTERFACE) otherwise.
    // Sets *outObject to this if supported, else to nullptr.
    uint32_t QueryInterface(int32_t interfaceId, void **outObject)
    {
        static const int32_t kInterfaceIdA = -0x0c39e601; // 0xF3C619FF
        static const int32_t kInterfaceIdB = -0x002d1a4f; // 0xFFD2E5B1

        if (interfaceId == kInterfaceIdA)
        {
            if (outObject != nullptr)
            {
                *outObject = this;
            }
            return 1; // S_OK
        }
        else
        {
            // For any other ID, first set output to nullptr
            if (outObject != nullptr)
            {
                *outObject = nullptr;
            }

            // Check second supported ID
            if (interfaceId != kInterfaceIdB)
            {
                return 0; // E_NOINTERFACE
            }

            // Second interface supported
            if (outObject != nullptr)
            {
                *outObject = this;
            }
            return 1; // S_OK
        }
    }
};