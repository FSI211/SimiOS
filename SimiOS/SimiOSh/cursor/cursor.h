#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define MAXC 2407
#define ATTRIBUTE 0x0F // Beispielattribut für hellen Text auf dunklem Hintergrund

// Array zur Zuordnung von Scancodes zu ASCII-Zeichen
char kbdus[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 0-15
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', // 16-28
    0, // Ctrl
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', // 30-43
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, // Shift
    '*',
    0, // Alt
    ' ', // Spacebar
    0, // CapsLock
    0, // F1
    0, // F2
    0, // F3
    0, // F4
    0, // F5
    0, // F6
    0, // F7
    0, // F8
    0, // F9
    0, // F10
    0, // NumLock
    0, // ScrollLock
    0, // Home key
    0, // Up arrow
    0, // PageUp
    '-',
    0, // Left arrow
    0,
    0, // Right arrow
    '+',
    0, // End key
    0, // Down arrow
    0, // PageDown
    0, // Insert key
    0, // Delete key
    0, 0, 0,
    0, // F11
    0, // F12
    0, // All other keys are undefined
};


// Funktion zum Zeichnen eines Zeichens mit Attributen an einer bestimmten Position auf dem Bildschirm
void draw_character(char character, int x, int y, char attribute) {
    // Berechnen Sie den Speicherort des Bildschirms für das Zeichen
    char *screen = (char*)0xB8000;
    int offset = y * SCREEN_WIDTH + x;

    // Schreiben Sie das Zeichen an die entsprechende Position im Speicher mit den angegebenen Attributen
    screen[offset * 2] = character;
    screen[offset * 2 + 1] = attribute;
}

// Struktur, um die Cursorposition zu speichern
typedef struct {
    int x;
    int y;
} CursorPosition;

// Globale Variable, um die aktuelle Cursorposition zu speichern
CursorPosition cursor;

// Funktion zum Setzen der Cursorposition
void setCursorPosition(int x, int y) {
    cursor.x = x;
    cursor.y = y;
}

void drawCursor() {
    // Stellen Sie sicher, dass der Cursor innerhalb der Bildschirmgrenzen liegt
    if (cursor.x >= 0 && cursor.x < SCREEN_WIDTH && cursor.y >= 0 && cursor.y < SCREEN_HEIGHT) {
        // Setzen Sie die Position des Cursors
        setCursorPosition(cursor.x, cursor.y);

        // Zeichnen Sie das Zeichen des Cursors an der aktuellen Position mit einem Attribut
        draw_character('|', cursor.x, cursor.y, ATTRIBUTE); // 'ATTRIBUTE' muss entsprechend definiert sein
    }
}

char k_get_char() {
    // Warten bis ein Zeichen verfügbar ist
    while (!(inb(0x64) & 0x01)) {
        // Hier könnten Sie optional eine Pause einfügen, um die CPU zu entlasten
    }

    // Zeichen von der Tastatur lesen
    char character = inb(0x60); // Zeichen von Tastaturport lesen (PS/2-Tastatur)

    // Überprüfen, ob die oberen Bits (Bit 7) gesetzt sind, was auf ein Tastaturereignis hinweist
    if (character & 0x80) {
        // Ein spezielles Tastaturereignis, keine normale Taste
        return '\0';
    } else {
        // Wenn Bit 7 nicht gesetzt ist, handelt es sich um ein normales Zeichen
        // Konvertieren Sie den Scancode in einen ASCII-Wert und geben Sie ihn zurück
        return kbdus[character];
    }
}

// Beispiel-Funktion zum Bewegen des Cursors nach rechts
void moveCursorRight() {
    char *c = k_get_char();
    if(k_get_char) {
        cursor.x++;
    }
    k_printf(c, 24);
}