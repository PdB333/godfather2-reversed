// FUNC_NAME: updateMouseCursorPosition
// Function address: 0x0069e680
// Role: Updates mouse cursor position relative to game window; normalizes coordinates and invokes callback.

// External globals (defined elsewhere, names extracted from Ghidra analysis)
extern HWND getGameWindowHandle();          // FUN_0069d500
extern unsigned int s_windowWidth;          // DAT_0120587c
extern unsigned int s_windowHeight;         // DAT_01205880
extern unsigned char s_disableCursorCenter; // DAT_0112a06d (if 0, cursor gets centered when outside window)
extern int s_cursorScreenX;                // DAT_00e50b7c
extern int s_cursorScreenY;                // DAT_00e50b80
extern float s_defaultNormalizedValue;     // DAT_00d5c458 (used when window minimized)
extern void (*s_mouseCallback)(int param, float* normalizedX, float* normalizedY); // DAT_0112a070

void updateMouseCursorPosition()
{
	HWND hWnd;
	BOOL isMinimized;
	float normalizedX;
	float normalizedY;
	POINT cursorPos;
	POINT screenPos;

	hWnd = getGameWindowHandle();
	isMinimized = IsIconic(hWnd);

	if (isMinimized == FALSE)
	{
		GetCursorPos(&cursorPos);
		ScreenToClient(hWnd, &cursorPos);

		// If cursor is outside the window client area, clamp to center
		if ((cursorPos.x < 0) || ((int)(unsigned int)s_windowWidth < cursorPos.x) ||
			(cursorPos.y < 0) || ((int)(unsigned int)s_windowHeight < cursorPos.y))
		{
			// Set to center of window
			cursorPos.x = (LONG)(s_windowWidth >> 1);
			cursorPos.y = (LONG)(s_windowHeight >> 1);

			// Only physically move cursor if auto-centering is not disabled
			if (s_disableCursorCenter == '\0')
			{
				screenPos.x = cursorPos.x;
				screenPos.y = cursorPos.y;
				ClientToScreen(hWnd, &screenPos);
				SetCursorPos(screenPos.x, screenPos.y);
			}
		}

		// Store raw cursor position (client coords)
		s_cursorScreenX = cursorPos.x;
		s_cursorScreenY = cursorPos.y;

		// Compute normalized coordinates (0.0 to 1.0)
		normalizedX = (float)cursorPos.x / (float)s_windowWidth;
		normalizedY = (float)cursorPos.y / (float)s_windowHeight;
	}
	else
	{
		// Window minimized: keep previous normalized values (stored in s_defaultNormalizedValue)
		normalizedX = s_defaultNormalizedValue;
		normalizedY = s_defaultNormalizedValue;
	}

	// Invoke external callback with normalized mouse position (if registered)
	if (s_mouseCallback != (void*)0)
	{
		(*s_mouseCallback)(0, &normalizedX, &normalizedY);
	}
}