// Chess – Graphical engine entry point
// -----------------------------------------------------------------------
// DO NOT MODIFY THIS FILE (except lines marked below).
// Your chess logic goes in separate files (Board.h/.cpp, Piece.h/.cpp, etc.)
// -----------------------------------------------------------------------
#include "Chess.h"

int main()
{
    // You may change this string to test specific board positions.
    // Each character represents one square, left-to-right, top-to-bottom.
    // Capital = white piece, small = black piece, '#' = empty square.
    // Pieces: R/r=Rook  N/n=Knight  B/b=Bishop  Q/q=Queen  K/k=King  P/p=Pawn
    std::string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";

    Chess chess(board);

    /*
     * MoveResult values your logic must return:
     *
     *  Illegal moves:
     *   MoveResult::NO_PIECE_AT_SOURCE   – no piece at source square
     *   MoveResult::OPPONENT_PIECE       – source piece belongs to the opponent
     *   MoveResult::OWN_PIECE_AT_DEST    – destination occupied by your own piece
     *   MoveResult::ILLEGAL_MOVE         – movement pattern illegal (or path blocked)
     *   MoveResult::LEAVES_KING_IN_CHECK – move would leave your own king in check
     *
     *  Legal moves:
     *   MoveResult::LEGAL_MOVE           – legal move (normal)
     *   MoveResult::LEGAL_MOVE_CHECK     – legal move that puts the opponent in check
     */

    std::string move = chess.getInput();

    while (move != "exit")
    {
        // ---------------------------------------------------------------
        // PUT YOUR CODE HERE (replace the placeholder below):
        // Call your chess engine to validate `move` and set codeResponse.
        // ---------------------------------------------------------------
        MoveResult codeResponse = MoveResult::LEGAL_MOVE;
        // ---------------------------------------------------------------

        chess.setCodeResponse(codeResponse);
        move = chess.getInput();
    }

    std::cout << "\nGoodbye!\n";
    return 0;
}
