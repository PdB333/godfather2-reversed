// FUNC_NAME: EARS::String::normalizePath

void __thiscall normalizePath(uint *this, char removeDotDot)
{
  char c;
  char *pBuffer;
  char *pCur;
  char *pEnd;
  char *pSrc;
  char *pDst;

  pBuffer = (char *)*this;
  if (pBuffer != (char *)0x0)
  {
    // Replace forward slashes with backslashes and convert uppercase to lowercase.
    pEnd = pBuffer + this[1];
    for (; pBuffer < pEnd; pBuffer = pBuffer + 1)
    {
      c = *pBuffer;
      if (c == '/')
      {
        *pBuffer = '\\';
      }
      else if ((byte)(c + 0xbfU) < 0x1a) // Check if c is uppercase letter (A-Z)
      {
        *pBuffer = c + ' '; // Convert to lowercase (add 0x20)
      }
    }
    pBuffer = (char *)*this;
    c = *pBuffer;
    if (c != '\0')
    {
      // Remove duplicate backslashes
      pEnd = pBuffer + 1;
      c = *pEnd;
      while (c != '\0')
      {
        pSrc = pEnd + 1;
        pEnd = pEnd + 1;
        if (*pSrc == '\0') break;
        if ((c == '\\') && (pDst = pEnd, *pSrc == '\\'))
        {
          do
          {
            *pDst = pDst[1];
            pDst = pDst + 1;
          } while (*pDst != '\0');
        }
        c = *pEnd;
      }
    }
    // Collapse "\..\" sequences (remove parent directory segments)
    pEnd = _strstr((char *)*this, "\\..\\");
    while (pEnd != (char *)0x0)
    {
      c = pEnd[3];
      while (pEnd = pEnd + 1, c != '\0')
      {
        *pEnd = pEnd[2];
        c = pEnd[3];
      }
      *pEnd = '\0';
      pEnd = _strstr((char *)*this, "\\..\\");
    }
    // Handle drive letter colon: if there's a colon and it's at position 2 or later, swap portion after colon to front?
    pEnd = (char *)*this;
    pSrc = _strrchr(pEnd, 0x3a); // ':'
    if ((pSrc != (char *)0x0) && ((char *)(*this + 2) < pSrc))
    {
      pSrc = pSrc - 1;
      do
      {
        *pEnd = *pSrc;
        pSrc = pSrc + 1;
        c = *pEnd;
        pEnd = pEnd + 1;
      } while (c != '\0');
    }
    // Process ".." (parent directory) if param_2 is non-zero
    if (removeDotDot != '\0')
    {
      pEnd = (char *)*this;
      c = *pEnd;
      while (c != '\0')
      {
        pCur = pEnd;
        if (((c == '.') && (pEnd[1] == '.')) &&
            ((char *)*this < pEnd) &&
            ((pSrc = pEnd + 2, pEnd[2] != '.') && (pEnd[-1] != '.')))
        {
          if (pBuffer < pEnd)
          {
            if (pEnd[-1] == '\\')
            {
              pEnd = pEnd - 2;
            }
            else
            {
              pEnd = pEnd - 1;
            }
          }
          pDst = pBuffer;
          if (pBuffer <= pEnd)
          {
            for (; (pDst = pEnd, pBuffer < pEnd && (*pEnd != '\\')); pEnd = pEnd - 1)
            {
            }
          }
          do
          {
            *pDst = *pSrc;
            c = *pSrc;
            pDst = pDst + 1;
            pCur = pBuffer;
            pSrc = pSrc + 1;
          } while (c != '\0');
        }
        pEnd = pCur + 1;
        c = pCur[1];
      }
    }
    // Recalculate length
    pBuffer = (char *)*this;
    pEnd = pBuffer;
    do
    {
      c = *pEnd;
      pEnd = pEnd + 1;
    } while (c != '\0');
    this[1] = (int)pEnd - (int)(pBuffer + 1);
    // If the first char was not a backslash but now is, call an error function?
    if (((c != '\\') && (pBuffer != (char *)0x0)) && (*pBuffer == '\\'))
    {
      FUN_004d3920(0);
    }
  }
  return;
}