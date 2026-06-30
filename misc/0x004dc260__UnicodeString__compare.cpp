// FUNC_NAME: UnicodeString::compare
// Function address: 0x004dc260
// Role: Compares a UnicodeString object (utf-16) with a raw null‑terminated wide string.
// Returns -1 (less), 0 (equal), 1 (greater), with special handling for null/empty inputs.

class UnicodeString {
public:
    ushort* mpBuffer;       // +0x00: pointer to utf-16 characters
    int     mLength;        // +0x04: length (0 means empty/null string)

    // Compares this string to another null-terminated utf-16 string.
    // - Returns 1 if this string is empty and the other is not (non‑standard, but used by the engine).
    // - Returns -1 if this string is non‑empty and the other is empty.
    // - Standard strcmp result otherwise.
    int compare(const ushort* other) {
        // Determine if the other string is non‑null and non‑empty.
        bool otherHasContent = (other != nullptr) && (*other != 0);

        // If this string's length is zero (empty/null), return content indicator of other.
        if (mLength == 0) {
            return static_cast<uint>(otherHasContent);
        }

        // If the other string is empty while this one is not, return -1.
        if (!otherHasContent) {
            return 0xffffffff;  // -1 as unsigned int
        }

        // Pointers for traversal.
        ushort* thisPtr = mpBuffer;
        ushort* otherPtr = const_cast<ushort*>(other);

        while (true) {
            ushort thisChar = *thisPtr;
            ushort otherChar = *otherPtr;

            bool less = (thisChar < otherChar);
            if (thisChar != otherChar) {
                // Generate -1 if less, 1 if greater.
                return static_cast<int>((1 - static_cast<uint>(less)) - static_cast<uint>(less != false));
            }

            // Characters equal; check for end of string.
            if (thisChar == 0) {
                return 0;
            }

            // Move to next character (wide char = 2 bytes).
            thisPtr += 1;
            otherPtr += 1;
        }
    }
};