#include <iostream>
#include "Board.h"
#include <chrono>


int main()
{
    Board board;

    Piece::Color playerToMove = Piece::Color::WHITE;
    while (true)
    {
        std::cout << "Evaluation: " << board.evaluate() << "\n";
        std::cout << board.toString() << "\n\n";

        std::vector<Move> moves = board.getMoves(playerToMove);
        for (auto move : moves)
            std::cout << move.toString() << "\n";

        if (playerToMove == Piece::Color::WHITE)
        {
            std::cout << "Enter move for white: ";

            int initialRow, initialColumn;
            int targetRow, targetColumn;

            std::cin >> initialRow >> initialColumn >> targetRow >> targetColumn;

            board.makeMove(Move(Position(initialRow, initialColumn), Position(targetRow, targetColumn)));

            playerToMove = Piece::Color::BLACK;
        }
        else
        {
           auto start = std::chrono::high_resolution_clock::now();
            Move move = board.getBestMove(playerToMove);
            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << "Time to get best move: " << duration.count() << "ms\n";

            board.makeMove(move);
            std::cout << "Black moved: " << move.toString() << "\n";

            /*std::cout << "Enter move for black: ";

            int initialRow, initialColumn;
            int targetRow, targetColumn;

            std::cin >> initialRow >> initialColumn >> targetRow >> targetColumn;

            board.makeMove(Move(Position(initialRow, initialColumn), Position(targetRow, targetColumn)));*/

            playerToMove = Piece::Color::WHITE;
        }

        std::cout << "\n";
    }

    if (playerToMove == Piece::Color::WHITE)
        playerToMove = Piece::Color::BLACK;
    else
        playerToMove = Piece::Color::WHITE;
}