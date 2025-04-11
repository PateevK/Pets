#include "renderer.h"
// 0,0  - center.
// IDK how it works but to get valid result par\scrVal must be decrimented by 1;)
// otherwise out of bounds.
int MapToScreen(float val, int scrVal) {
    return round((val + 1.0f) * 0.5f * (scrVal - 1));
}

void Renderer::DrawPoint(wchar_t ch, int color, float x, float y) {
    uint32_t _x = MapToScreen(x, m_scrBufX);
    uint32_t _y = MapToScreen(y, m_scrBufY);
    if(_x > m_scrBufX || _y > m_scrBufY) {
        WARNING(throw WARNING_WRITING_VIOLATION;)
        return;
    }
    m_scrBuf_p[(_y * m_scrBufX) + _x].Char.UnicodeChar = ch;
    m_scrBuf_p[(_y * m_scrBufX) + _x].Attributes = color;
}
// Using Bresenham, think about implementing and testing Wu's.
// Credits to Adriel Jr. - https://stackoverflow.com/questions/10060046/drawing-lines-with-bresenhams-line-algorithm
void Renderer::DrawLine(wchar_t ch, int color, float x, float y, float x1, float y1) {
    
    int _x = MapToScreen(x, m_scrBufX);
    int _x1 = MapToScreen(x1, m_scrBufX);
    int _y = MapToScreen(y, m_scrBufY);
    int _y1 = MapToScreen(y1, m_scrBufY);
    int dx = _x1 - _x;
    int dy = _y1 - _y;
    if (_x >= m_scrBufX || _y >= m_scrBufY || _x1 >= m_scrBufX || _y1 >= m_scrBufY) {
        WARNING(throw WARNING_WRITING_VIOLATION;)
            return;
    }

    int dLong = abs(dx);
    int dShort = abs(dy);

    int offsetLong = dx > 0 ? 1 : -1;
    int offsetShort = dy > 0 ? m_scrBufX : -(int)m_scrBufX;

    if (dLong < dShort)
    {
        std::swap(dShort, dLong);
        std::swap(offsetShort, offsetLong);
    }

    int error = 2 * dShort - dLong;
    int index = _y * m_scrBufX + _x;
    const int offset[] = { offsetLong, offsetLong + offsetShort };
    const int abs_d[] = { 2 * dShort, 2 * (dShort - dLong) };
    for (int i = 0; i <= dLong; ++i)
    {   
        m_scrBuf_p[index].Char.UnicodeChar = ch;
        m_scrBuf_p[index].Attributes = color;  // or a call to your painting method
        const int errorIsTooBig = error >= 0;
        index += offset[errorIsTooBig];
        error += abs_d[errorIsTooBig];
    }
}

void Renderer::DrawTriangle(wchar_t ch, int color, float x, float y, float x1, float y1, float x2, float y2) {
    DrawLine(ch, color, x, y, x1, y1);
    DrawLine(ch, color, x1, y1, x2, y2);
    DrawLine(ch, color, x2, y2, x, y);
}

// Mapping to screen shall be made in the Draw functions above.
void Renderer::DrawVertices(wchar_t ch, int color, float* vertices, size_t nm_vertices, int step, DRAW_MODE mode) {
    ERROR(if (nm_vertices <= 0) { throw ERROR_BUFFER_SZ; })

        float x = 0, y = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        switch (mode) {
            case PK_POINTS:
                for (size_t i = 0; i < nm_vertices; i += step) {
                    WARNING(if (vertices[i + 1] > nm_vertices) throw WARNING_BUFFER_ACCES;)
                    x = vertices[i];
                    y = vertices[i + 1];
                    DrawPoint(ch, color, x, y);
                }
                break;
            case PK_LINES:
                for (size_t i = 0; i < nm_vertices; i += step) {
                    WARNING(if (vertices[i + 3] > nm_vertices) throw WARNING_BUFFER_ACCES;)
                    x = vertices[i];
                    y = vertices[i + 1];
                    x1 = vertices[i + 2];
                    y1 = vertices[i + 3];
                    DrawLine(ch, color, x, y, x1, y1);
                }
                break;
            case PK_TRIANGLES:
                for (size_t i = 0; i < nm_vertices; i += step) {
                    WARNING(if (vertices[i + 3] > nm_vertices) throw WARNING_BUFFER_ACCES;)
                    x = vertices[i];
                    y = vertices[i + 1];
                    x1 = vertices[i + 2];
                    y1 = vertices[i + 3];
                    x2 = vertices[i + 4];
                    y2 = vertices[i + 5];
                    DrawTriangle(ch, color, x, y, x1, y1, x2, y2);
                }
                break;
        }


}

void Renderer::Fill(wchar_t ch, int color) {
    for (int i = 0; i < m_scrBuf_sz; i++) {
        m_scrBuf_p[i].Char.UnicodeChar = ch;
        m_scrBuf_p[i].Attributes = color;
    }
}

void Renderer::UpdateScreen() {
    // Maybe - 1 is dull.
    SMALL_RECT rect = { 0, 0, (short)m_scrBufX - 1, (short)m_scrBufY - 1 };
    // must be W(wide) to support unicode
    WriteConsoleOutputW(m_hConsoleOut, m_scrBuf_p, { (short)m_scrBufX, (short)m_scrBufY }, { 0,0 }, &rect);
}

// Maybe asserts were nor the best choice.
// var\scrBufX, var\scrBufY - in chars. var\fontX, var\fontY - in px.
// Estimated size of console's window in px = (var\scrBufX * var\fontX) * Display Scale, (var\scrBufY * var\fontY)  * Display Scale. 
void Renderer::SetUpConsole(short scrBufX, short scrBufY, int fontX, int fontY) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    assert(handle != INVALID_HANDLE_VALUE);
    //Font
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = fontX;
    cfi.dwFontSize.Y = fontY;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas");
    assert(SetCurrentConsoleFontEx(handle, false, &cfi) && "ERROR:: Font parametrs are invalid");

    SMALL_RECT win = { 0, 0, 1, 1 };
    // If commeòted the X and Y cannot be less the default console size in my case - (120,30); 
    assert(SetConsoleWindowInfo(handle, TRUE, &win));

    assert(SetConsoleScreenBufferSize(handle, { scrBufX, scrBufY }) && "ERROR:: Screen Buffer parametrs are invalid");

    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    assert(info.dwMaximumWindowSize.X > scrBufX - 1 && "ERROR:: Screen Buffer X is too Large");
    assert(info.dwMaximumWindowSize.Y > scrBufY - 1 && "ERROR:: Screen Buffer Y is too Large");

    // func\SetConsoleWindowInfo - var\win must not be more then Screen Buffer Size.
    // The ration of scren x to screen y must be equal to the font x to font y ration set by func\SetCurrentConsoleFontEx
    win = { 0, 0, (short)(scrBufX - 1), (short)(scrBufY - 1) };
    assert(SetConsoleWindowInfo(handle, 1, &win) && "ERROR:: Couldn't resize window");

    m_scrBuf_p = new CHAR_INFO[scrBufX * scrBufY];
    memset(m_scrBuf_p, 0, sizeof(CHAR_INFO) * scrBufX * scrBufY);

    m_scrBuf_sz = scrBufX * scrBufY;
    m_hConsoleOut = handle;
    m_scrBufX = scrBufX;
    m_scrBufY = scrBufY;
    m_fontX = m_fontX;
    m_fontY = m_fontY;
}



