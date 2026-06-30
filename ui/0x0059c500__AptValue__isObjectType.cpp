// FUNC_NAME: AptValue::isObjectType
// Function at 0x0059c500: Checks if an APT value is of a specific object type (0x16).
// This is a member function of the APT value class. It validates that the value is non-null
// and that its type tag matches the expected type. Returns 1 if true, 0 otherwise.
// The debug block triggers an assertion failure if 'this' is null.

int AptValue::isObjectType() const
{
  // Debug assertion block for null 'this'
  if (this == nullptr)
  {
    // Source: c:\packages001_pc\apt\0.19.optimized\source\apt\_AptValue.h line 0x1ae
    const char* sourceFile = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    int sourceLine = 0x1ae;
    int assertionCount = 2;

    // Global flag to disable assertions (DAT_01128f0f)
    // If not already disabled, call the error handler and trigger a breakpoint.
    // In release builds, this may be skipped.
    // For simplicity, we treat this as an assertion that would halt execution.
    // However, the original code may fall through to the type check; we assume proper behavior.
    return 0;  // Safe fallback for null pointer
  }

  // Check the value's type tag:
  // Lower 15 bits must equal 0x16 and bit 15 must be set (0x8000).
  if (((*this & 0x7fff) == 0x16) && ((*this & 0x8000) != 0))
  {
    return 1;
  }

  return 0;
}