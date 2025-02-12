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

        std::cout << "Attacked by white: " << "\n";
        std::cout << board.attackedSquaresToString(Piece::Color::WHITE) << "\n\n";

        std::cout << "Attacked by black: " << "\n";
        std::cout << board.attackedSquaresToString(Piece::Color::BLACK) << "\n\n";

        std::vector<Move> moves = board.getMoves(playerToMove);
        for (auto move : moves)
            std::cout << move.toString() << "\n";

        if (playerToMove == Piece::Color::WHITE)
        {
            std::cout << "Enter move for white: ";

            int initialRow, initialColumn;
            int targetRow, targetColumn;

            std::cin >> initialRow >> initialColumn >> targetRow >> targetColumn;

            Move move = Move(Position(initialRow, initialColumn), Position(targetRow, targetColumn));

            if (targetRow == 0)
            {
                std::cout << "Promote pawn to (Q, R, B, K): ";
                char promotionType;
                std::cin >> promotionType;
                switch (promotionType)
                {
                case 'Q':
                    move.setPromotionType(Piece::Type::QUEEN);
                    break;
                case 'q':
                    move.setPromotionType(Piece::Type::QUEEN);
                    break;
                case 'R':
                    move.setPromotionType(Piece::Type::ROOK);
                    break;
                case 'r':
                    move.setPromotionType(Piece::Type::ROOK);
                    break;
                case 'B':
                    move.setPromotionType(Piece::Type::BISHOP);
                    break;
                case 'b':
                    move.setPromotionType(Piece::Type::BISHOP);
                    break;
                case 'K':
                    move.setPromotionType(Piece::Type::KNIGHT);
                    break;
                case 'k':
                    move.setPromotionType(Piece::Type::KNIGHT);
                    break;
                default:
                    move.setPromotionType(Piece::Type::QUEEN);
                }
            }

            board.makeMove(move);

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

            playerToMove = Piece::Color::WHITE;
        }

        std::cout << "\n";
    }

    if (playerToMove == Piece::Color::WHITE)
        playerToMove = Piece::Color::BLACK;
    else
        playerToMove = Piece::Color::WHITE;
}