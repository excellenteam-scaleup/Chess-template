#pragma once
#include <iostream>
#include <string>

// NOTE FOR STUDENTS:
// Do NOT modify this file. This is the graphical engine.
// Your task is to implement the chess logic in separate files.

enum class MoveResult {
    NO_PIECE_AT_SOURCE   = 11,
    OPPONENT_PIECE       = 12,
    OWN_PIECE_AT_DEST    = 13,
    ILLEGAL_MOVE         = 21,
    LEAVES_KING_IN_CHECK = 31,
    LEGAL_MOVE_CHECK     = 41,
    LEGAL_MOVE           = 42
};

inline constexpr int BOARD_DISPLAY_SIZE = 21;

class Chess {
    unsigned char m_board[BOARD_DISPLAY_SIZE][BOARD_DISPLAY_SIZE] = {};
    bool m_turn = true;
    std::string m_boardString;
    std::string m_input;
    std::string m_msg = "\n";
    std::string m_errorMsg = "\n";
    MoveResult m_codeResponse;
    bool m_isFirst = true;   // replaces the old static-local in getInput()

    void clear() const;
    void setFrames();
    void setPieces();
    void show() const;
    void displayBoard() const;
    void showAskInput() const;
    bool isSame() const;
    bool isValid() const;
    bool isExit() const;
    void execute();
    void doTurn();

public:
    Chess(const std::string& start = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr");
    Chess(const Chess&) = delete;
    Chess& operator=(const Chess&) = delete;
    std::string getInput();
    void setCodeResponse(MoveResult codeResponse);
};
