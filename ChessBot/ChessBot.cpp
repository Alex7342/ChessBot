#include <iostream>
#include "Board.h"


int main()
{
    Board board;

    Piece::Color playerToMove = Piece::Color::WHITE;
    while (true)
    {
        std::cout << board.toString() << "\n";

        std::vector<Move> moves = board.getMoves(playerToMove);

        for (auto move : moves)
        {
            std::cout << "(" << move.getInitialPosition().row() << ", " << move.getInitialPosition().column() << ") -> " <<
                "(" << move.getTargetPosition().row() << ", " << move.getTargetPosition().column() << ")\n";
        }
        
        std::cout << "Undo? (y/n)\n";
        char c; std::cin >> c;
        if (c == 'y')
        {
            board.undoMove();
        }
        else
        {
            std::cout << "Enter move for " << ((playerToMove == Piece::Color::WHITE) ? "White" : "Black") << ": ";

            int initialRow, initialColumn;
            int targetRow, targetColumn;

            std::cin >> initialRow >> initialColumn >> targetRow >> targetColumn;

            board.makeMove(Move(Position(initialRow, initialColumn), Position(targetRow, targetColumn)));
        }

        if (playerToMove == Piece::Color::WHITE)
            playerToMove = Piece::Color::BLACK;
        else
            playerToMove = Piece::Color::WHITE;
    }
}