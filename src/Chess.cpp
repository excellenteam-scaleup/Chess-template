#include "Chess.h"
#include <iostream>

#if defined(_WIN32)
  #include <Windows.h>
#endif

// ---------------------------------------------------------------------------
// Platform-specific: clear the terminal screen
// ---------------------------------------------------------------------------
void Chess::clear() const
{
#if defined(_WIN32)
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;
    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
#else
    std::cout << "\033[2J\033[3J\033[H";
#endif
}

// ---------------------------------------------------------------------------
// Platform-specific: build the ASCII-art board frame
//
// Input format: <col_letter><row_number>  (e.g. "a1", "b4")
//   - Letters A–H label COLUMNS (displayed on the top and bottom)
//             A = left-most column, H = right-most column
//   - Numbers 1–8 label ROWS    (displayed on the left and right sides)
//             1 = top row (white's back rank), 8 = bottom row (black's back rank)
//
// This is consistent with execute(), which maps:
//   col  = input[0] - 'a'   (0 = left)
//   row  = input[1] - '1'   (0 = top)
// ---------------------------------------------------------------------------

#if defined(_WIN32)
// Windows: use CP437 box-drawing characters for a nicer look
void Chess::setFrames()
{
    for (int row = 0; row < BOARD_DISPLAY_SIZE; ++row)
        for (int col = 0; col < BOARD_DISPLAY_SIZE; ++col)
            m_board[row][col] = 32;   // space

    // Outer border corners and edges
    m_board[0][0] = 201;  m_board[0][20] = 187;
    m_board[20][0] = 200; m_board[20][20] = 188;
    for (int i = 1; i < 20; ++i) {
        m_board[0][i]  = 205;
        m_board[20][i] = 205;
        m_board[i][0]  = 186;
        m_board[i][20] = 186;
    }

    // Inner board corners
    m_board[2][2] = 218;  m_board[2][18] = 191;
    m_board[18][2] = 192; m_board[18][18] = 217;

    // Inner T-junctions and crosses
    for (int i = 4; i < 17; i += 2) {
        m_board[2][i]  = 194; m_board[18][i] = 193;
        m_board[i][2]  = 195; m_board[i][18] = 180;
    }
    for (int i = 2; i < 19; i += 2)
        for (int j = 3; j < 19; j += 2)
            m_board[i][j] = 196;
    for (int i = 3; i < 18; i += 2)
        for (int j = 2; j < 19; j += 2)
            m_board[i][j] = 179;
    for (int i = 4; i < 17; i += 2)
        for (int j = 4; j < 17; j += 2)
            m_board[i][j] = 197;

    // Letters A–H on TOP and BOTTOM → label columns
    for (int i = 3, t = 0; i < 19; i += 2, ++t)
        m_board[1][i] = m_board[19][i] = static_cast<unsigned char>('A' + t);

    // Numbers 1–8 on LEFT and RIGHT → label rows
    for (int i = 3, t = 0; i < 19; i += 2, ++t)
        m_board[i][1] = m_board[i][19] = static_cast<unsigned char>('1' + t);
}

void Chess::setPieces()
{
    for (int row = 0, t = 0; row < 8; ++row)
        for (int col = 0; col < 8; ++col, ++t)
            m_board[3 + row * 2][3 + col * 2] =
                (m_boardString[t] == '#') ? 32 : static_cast<unsigned char>(m_boardString[t]);
}

#else  // Linux / macOS: plain ASCII

void Chess::setFrames()
{
    for (int row = 0; row < BOARD_DISPLAY_SIZE; ++row)
        for (int col = 0; col < BOARD_DISPLAY_SIZE; ++col)
            m_board[row][col] = ' ';

    // Outer border
    m_board[0][0] = m_board[0][20] = m_board[20][0] = m_board[20][20] = '+';
    for (int i = 1; i < 20; ++i) {
        m_board[0][i]  = '-';
        m_board[20][i] = '-';
        m_board[i][0]  = '|';
        m_board[i][20] = '|';
    }

    // Inner board corners and junctions (all become '+')
    m_board[2][2] = m_board[2][18] = m_board[18][2] = m_board[18][18] = '+';
    for (int i = 4; i < 17; i += 2) {
        m_board[2][i]  = '+'; m_board[18][i] = '+';
        m_board[i][2]  = '+'; m_board[i][18] = '+';
    }

    // Horizontal and vertical lines inside the board
    for (int i = 2; i < 19; i += 2)
        for (int j = 3; j < 19; j += 2)
            m_board[i][j] = '-';
    for (int i = 3; i < 18; i += 2)
        for (int j = 2; j < 19; j += 2)
            m_board[i][j] = '|';
    for (int i = 4; i < 17; i += 2)
        for (int j = 4; j < 17; j += 2)
            m_board[i][j] = '+';

    // Letters A–H on TOP and BOTTOM → label columns
    for (int i = 3, t = 0; i < 19; i += 2, ++t)
        m_board[1][i] = m_board[19][i] = static_cast<unsigned char>('A' + t);

    // Numbers 1–8 on LEFT and RIGHT → label rows
    for (int i = 3, t = 0; i < 19; i += 2, ++t)
        m_board[i][1] = m_board[i][19] = static_cast<unsigned char>('1' + t);
}

void Chess::setPieces()
{
    for (int row = 0, t = 0; row < 8; ++row)
        for (int col = 0; col < 8; ++col, ++t)
            m_board[3 + row * 2][3 + col * 2] =
                (m_boardString[t] == '#') ? ' ' : static_cast<unsigned char>(m_boardString[t]);
}

#endif  // _WIN32

// ---------------------------------------------------------------------------
// Display helpers
// ---------------------------------------------------------------------------

// Maps a piece letter to its Unicode chess symbol (UTF-8)
static const char* pieceToUnicode(unsigned char c)
{
    switch (c) {
    // White pieces (uppercase) → hollow Unicode symbols U+2654–U+2659
    case 'K': return "\u2654"; case 'Q': return "\u2655";
    case 'R': return "\u2656"; case 'B': return "\u2657";
    case 'N': return "\u2658"; case 'P': return "\u2659";
    // Black pieces (lowercase) → filled Unicode symbols U+265A–U+265F
    case 'k': return "\u265A"; case 'q': return "\u265B";
    case 'r': return "\u265C"; case 'b': return "\u265D";
    case 'n': return "\u265E"; case 'p': return "\u265F";
    default:  return nullptr;
    }
}

void Chess::show() const
{
    for (int row = 0; row < BOARD_DISPLAY_SIZE; ++row) {
        for (int col = 0; col < BOARD_DISPLAY_SIZE; ++col) {
            unsigned char c = m_board[row][col];
            // Piece cells are at odd display indices in [3,17] on both axes
            bool isPieceCell = (row >= 3 && row <= 17 && row % 2 == 1 &&
                                col >= 3 && col <= 17 && col % 2 == 1);
            if (isPieceCell) {
                const char* symbol = pieceToUnicode(c);
                if (symbol) {
                    bool isWhite = ('A' <= c && c <= 'Z');
                    std::cout << (isWhite ? "\033[1;97m" : "\033[1;33m") << symbol << "\033[0m";
                } else {
                    std::cout << ' ';
                }
            } else {
                std::cout << c;
            }
        }
        std::cout << '\n';
    }
}

void Chess::displayBoard() const
{
    clear();
    show();
    std::cout << m_msg << m_errorMsg;
}

void Chess::showAskInput() const
{
    if (m_turn)
        std::cout << "Player 1 (White - Capital letters) >> ";
    else
        std::cout << "Player 2 (Black - Small letters)   >> ";
}

// ---------------------------------------------------------------------------
// Input validation
// ---------------------------------------------------------------------------

bool Chess::isSame() const
{
    return (m_input[0] == m_input[2]) && (m_input[1] == m_input[3]);
}

bool Chess::isValid() const
{
    if (m_input.size() < 4)
        return false;

    bool srcRow = (('A' <= m_input[0] && m_input[0] <= 'H') || ('a' <= m_input[0] && m_input[0] <= 'h'));
    bool srcCol = ('1' <= m_input[1] && m_input[1] <= '8');
    bool dstRow = (('A' <= m_input[2] && m_input[2] <= 'H') || ('a' <= m_input[2] && m_input[2] <= 'h'));
    bool dstCol = ('1' <= m_input[3] && m_input[3] <= '8');

    return srcRow && srcCol && dstRow && dstCol;
}

bool Chess::isExit() const
{
    return (m_input == "exit" || m_input == "quit" ||
            m_input == "EXIT" || m_input == "QUIT");
}

// ---------------------------------------------------------------------------
// Game logic
// ---------------------------------------------------------------------------

// Apply a validated move to the internal board string
// input[0] = col letter ('a'–'h'), input[1] = row digit ('1'–'8')
void Chess::execute()
{
    int srcCol = (m_input[0] - 'a');
    int srcRow = (m_input[1] - '1');
    char piece = m_boardString[srcRow * 8 + srcCol];
    m_boardString[srcRow * 8 + srcCol] = '#';

    int dstCol = (m_input[2] - 'a');
    int dstRow = (m_input[3] - '1');
    m_boardString[dstRow * 8 + dstCol] = piece;

    setPieces();
}

void Chess::doTurn()
{
    m_errorMsg = "\n";
    switch (m_codeResponse) {
    case MoveResult::NO_PIECE_AT_SOURCE:   m_msg = "There is no piece at the source.\n";                  break;
    case MoveResult::OPPONENT_PIECE:       m_msg = "The piece at the source belongs to your opponent.\n"; break;
    case MoveResult::OWN_PIECE_AT_DEST:    m_msg = "One of your own pieces is at the destination.\n";     break;
    case MoveResult::ILLEGAL_MOVE:         m_msg = "Illegal movement for that piece.\n";                  break;
    case MoveResult::LEAVES_KING_IN_CHECK: m_msg = "This move would put your own king in check.\n";       break;
    case MoveResult::LEGAL_MOVE_CHECK:
        execute();
        m_turn = !m_turn;
        m_msg = "Legal move — check!\n";
        break;
    case MoveResult::LEGAL_MOVE:
        execute();
        m_turn = !m_turn;
        m_msg = "Legal move.\n";
        break;
    }
}

// ---------------------------------------------------------------------------
// Constructor & public interface
// ---------------------------------------------------------------------------

Chess::Chess(const std::string& start)
    : m_boardString(start), m_codeResponse(MoveResult::LEGAL_MOVE)
{
#if defined(_WIN32)
    // Enable ANSI escape codes and UTF-8 output on Windows 10+
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
    setFrames();
    setPieces();
}

std::string Chess::getInput()
{
    if (m_isFirst)
        m_isFirst = false;
    else
        doTurn();

    displayBoard();
    showAskInput();

    std::cin >> m_input;
    if (isExit()) return "exit";

    while (!isValid() || isSame()) {
        m_errorMsg = (!isValid())
            ? "Invalid input — please enter two valid squares (e.g. A2B4 or a2b4).\n"
            : "Source and destination are the same square.\n";
        displayBoard();
        showAskInput();
        std::cin >> m_input;
        if (isExit()) return "exit";
    }

    // Normalise to lowercase row letter
    if ('A' <= m_input[0] && m_input[0] <= 'H') m_input[0] = m_input[0] - 'A' + 'a';
    if ('A' <= m_input[2] && m_input[2] <= 'H') m_input[2] = m_input[2] - 'A' + 'a';

    return m_input;
}

void Chess::setCodeResponse(MoveResult codeResponse)
{
    m_codeResponse = codeResponse;
}
