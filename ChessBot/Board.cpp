#include "Board.h"
#include "Move.h"

Board::Board()
{
	// Add pawns
	for (int j = 0; j < 8; j++)
	{
		// Black
		this->blackPieces.push_back(Piece(Piece::Type::PAWN, Piece::Color::BLACK, Position(1, j), false));
		this->board[1][j] = { Piece::Type::PAWN, Piece::Color::BLACK };

		// White
		this->whitePieces.push_back(Piece(Piece::Type::PAWN, Piece::Color::WHITE, Position(6, j), false));
		this->board[6][j] = { Piece::Type::PAWN, Piece::Color::WHITE };
	}

	// Add black rooks
	this->blackPieces.push_back(Piece(Piece::Type::ROOK, Piece::Color::BLACK, Position(0, 0), false));
	this->board[0][0] = { Piece::Type::ROOK, Piece::Color::BLACK };

	this->blackPieces.push_back(Piece(Piece::Type::ROOK, Piece::Color::BLACK, Position(0, 7), false));
	this->board[0][7] = { Piece::Type::ROOK, Piece::Color::BLACK };

	// Add white rooks
	this->whitePieces.push_back(Piece(Piece::Type::ROOK, Piece::Color::WHITE, Position(7, 0), false));
	this->board[7][0] = { Piece::Type::ROOK, Piece::Color::WHITE };

	this->whitePieces.push_back(Piece(Piece::Type::ROOK, Piece::Color::WHITE, Position(7, 7), false));
	this->board[7][7] = { Piece::Type::ROOK, Piece::Color::WHITE };

	// Add black knights
	this->blackPieces.push_back(Piece(Piece::Type::KNIGHT, Piece::Color::BLACK, Position(0, 1), false));
	this->board[0][1] = { Piece::Type::KNIGHT, Piece::Color::BLACK };

	this->blackPieces.push_back(Piece(Piece::Type::KNIGHT, Piece::Color::BLACK, Position(0, 6), false));
	this->board[0][6] = { Piece::Type::KNIGHT, Piece::Color::BLACK };

	// Add white knights
	this->whitePieces.push_back(Piece(Piece::Type::KNIGHT, Piece::Color::WHITE, Position(7, 1), false));
	this->board[7][1] = { Piece::Type::KNIGHT, Piece::Color::WHITE };

	this->whitePieces.push_back(Piece(Piece::Type::KNIGHT, Piece::Color::WHITE, Position(7, 6), false));
	this->board[7][6] = { Piece::Type::KNIGHT, Piece::Color::WHITE };

	// Add black bishops
	this->blackPieces.push_back(Piece(Piece::Type::BISHOP, Piece::Color::BLACK, Position(0, 2), false));
	this->board[0][2] = { Piece::Type::BISHOP, Piece::Color::BLACK };

	this->blackPieces.push_back(Piece(Piece::Type::BISHOP, Piece::Color::BLACK, Position(0, 5), false));
	this->board[0][5] = { Piece::Type::BISHOP, Piece::Color::BLACK };

	// Add white bishops
	this->whitePieces.push_back(Piece(Piece::Type::BISHOP, Piece::Color::WHITE, Position(7, 2), false));
	this->board[7][2] = { Piece::Type::BISHOP, Piece::Color::WHITE };

	this->whitePieces.push_back(Piece(Piece::Type::BISHOP, Piece::Color::WHITE, Position(7, 5), false));
	this->board[7][5] = { Piece::Type::BISHOP, Piece::Color::WHITE };

	// Add black queen
	this->blackPieces.push_back(Piece(Piece::Type::QUEEN, Piece::Color::BLACK, Position(0, 3), false));
	this->board[0][3] = { Piece::Type::QUEEN, Piece::Color::BLACK };

	// Add white queen
	this->whitePieces.push_back(Piece(Piece::Type::QUEEN, Piece::Color::WHITE, Position(7, 3), false));
	this->board[7][3] = { Piece::Type::QUEEN, Piece::Color::WHITE };

	// Add black king
	this->blackPieces.push_back(Piece(Piece::Type::KING, Piece::Color::BLACK, Position(0, 4), false));
	this->board[0][4] = { Piece::Type::KING, Piece::Color::BLACK };

	// Add white king
	this->whitePieces.push_back(Piece(Piece::Type::KING, Piece::Color::WHITE, Position(7, 4), false));
	this->board[7][4] = { Piece::Type::KING, Piece::Color::WHITE };

	// Add remaining empty squares
	for (int i = 2; i <= 5; i++)
		for (int j = 0; j < 8; j++)
			this->board[i][j] = { Piece::Type::NONE, Piece::Color::UNCOLORED };
}

// Check if a position is on the board given its coordinates
bool validPosition(const int row, const int column)
{
	return 0 <= row && row < 8 && 0 <= column && column < 8;
}


// Check if a given position is on the board
bool validPosition(const Position position)
{
	return 0 <= position.row() && position.row() < 8 && 0 <= position.column() && position.column() < 8;
}

// Check if any piece of the given color can move the given square assuming it has access to it (NOT SUITABLE FOR PAWNS)
bool Board::availableSquare(const Piece::Color color, const int row, const int column)
{
	if (!validPosition(row, column)) // Return false if the position is out of the board
		return false;

	auto square = this->board[row][column];

	if (square.type == Piece::Type::NONE) // Return true if the square is empty
		return true;

	if (square.color != color) // Return true if the square is not empty but the piece that is on the square is of the other color
		return true;

	return false;
}

// Add all possible moves of a piece in a direction to a container reference given as a parameter
void Board::addAllMovesInDirection(std::vector<Move>& moves, const Piece piece, const int rowChange, const int columnChange)
{
	Position position = piece.getPosition();
	while (true) // Loop until finding a stop condition
	{
		position.GoTowards(rowChange, columnChange); // Go in the given direction
		if (!validPosition(position)) // Stop if we get out of the board
			return;

		auto square = this->board[position.row()][position.column()]; // Get the current square

		if (square.type != Piece::Type::NONE)
		{
			if (square.color != piece.getColor()) // If the other piece of not the same color then we can capture it
				moves.push_back(Move(piece.getPosition(), position));

			return; // If we found another piece we must stop regardless of color
		}

		// If the square is empty then we can move there
		moves.push_back(Move(piece.getPosition(), position));
	}
}

// Add all possible moves of a given pawn to a container reference given as a parameter
void Board::addPawnMoves(std::vector<Move>& moves, Piece piece)
{
	int row = piece.getPosition().row();
	int column = piece.getPosition().column();

	if (piece.getColor() == Piece::Color::WHITE)
	{
		// Go one square up
		if (validPosition(row - 1, column) && this->board[row - 1][column].type == Piece::Type::NONE)
		{
			moves.push_back(Move(piece.getPosition(), Position(row - 1, column)));

			// If on first move then go one more square up
			if (!piece.hasMoved() && validPosition(row - 2, column) && this->board[row - 2][column].type == Piece::Type::NONE)
				moves.push_back(Move(piece.getPosition(), Position(row - 2, column)));
		}

		// Capture black piece up-left
		if (validPosition(row - 1, column - 1))
			if (this->board[row - 1][column - 1].type != Piece::Type::NONE && this->board[row - 1][column - 1].color != piece.getColor())
				moves.push_back(Move(piece.getPosition(), Position(row - 1, column - 1)));

		// Capture black piece up-right
		if (validPosition(row - 1, column + 1))
			if (this->board[row - 1][column + 1].type != Piece::Type::NONE && this->board[row - 1][column + 1].color != piece.getColor())
				moves.push_back(Move(piece.getPosition(), Position(row - 1, column + 1)));

		// TODO Implement en passant
	}
	else
	{
		// Go one square down
		if (validPosition(row + 1, column) && this->board[row + 1][column].type == Piece::Type::NONE)
		{
			moves.push_back(Move(piece.getPosition(), Position(row + 1, column)));

			// If on first move then go one more square down
			if (!piece.hasMoved() && validPosition(row + 2, column) && this->board[row + 2][column].type == Piece::Type::NONE)
				moves.push_back(Move(piece.getPosition(), Position(row + 2, column)));
		}

		// Capture white piece down-left
		if (validPosition(row + 1, column - 1))
			if (this->board[row + 1][column - 1].type != Piece::Type::NONE && this->board[row + 1][column - 1].color != piece.getColor())
				moves.push_back(Move(piece.getPosition(), Position(row + 1, column - 1)));

		// Capture white piece down-right
		if (validPosition(row + 1, column + 1))
			if (this->board[row + 1][column + 1].type != Piece::Type::NONE && this->board[row + 1][column + 1].color != piece.getColor())
				moves.push_back(Move(piece.getPosition(), Position(row + 1, column + 1)));

		// TODO Implement en passant
	}
}

// Add all possible moves of a given bishop to a container reference given as a parameter
void Board::addBishopMoves(std::vector<Move>& moves, Piece piece)
{
	// Get all moves in the up-left direction
	this->addAllMovesInDirection(moves, piece, -1, -1);
	
	// Get all moves in the up-right direction
	this->addAllMovesInDirection(moves, piece, -1, 1);

	// Get all moves in the down-left direction
	this->addAllMovesInDirection(moves, piece, 1, -1);

	// Get all moves in the down-right direction
	this->addAllMovesInDirection(moves, piece, 1, 1);
}

// Add all possible moves of a given knight to a container reference given as a parameter
void Board::addKnightMoves(std::vector<Move>& moves, Piece piece)
{
	int row = piece.getPosition().row();
	int column = piece.getPosition().column();

	// Check squares in the up-left direction
	if (this->availableSquare(piece.getColor(), row - 1, column - 2))
		moves.push_back(Move(piece.getPosition(), Position(row - 1, column - 2)));

	if (this->availableSquare(piece.getColor(), row - 2, column - 1))
		moves.push_back(Move(piece.getPosition(), Position(row - 2, column - 1)));

	// Check squares in the up-right direction
	if (this->availableSquare(piece.getColor(), row - 2, column + 1))
		moves.push_back(Move(piece.getPosition(), Position(row - 2, column + 1)));

	if (this->availableSquare(piece.getColor(), row - 1, column + 2))
		moves.push_back(Move(piece.getPosition(), Position(row - 1, column + 2)));

	// Check squares in the down-left direction
	if (this->availableSquare(piece.getColor(), row + 1, column - 2))
		moves.push_back(Move(piece.getPosition(), Position(row + 1, column - 2)));

	if (this->availableSquare(piece.getColor(), row + 2, column - 1))
		moves.push_back(Move(piece.getPosition(), Position(row + 2, column - 1)));

	// Check squares in the down-right direction
	if (this->availableSquare(piece.getColor(), row + 2, column + 1))
		moves.push_back(Move(piece.getPosition(), Position(row + 2, column + 1)));

	if (this->availableSquare(piece.getColor(), row + 1, column + 2))
		moves.push_back(Move(piece.getPosition(), Position(row + 1, column + 2)));
}

// Add all possible moves of a given rook to a container reference given as a parameter
void Board::addRookMoves(std::vector<Move>& moves, Piece piece)
{
	// Get all moves in the up direction
	this->addAllMovesInDirection(moves, piece, -1, 0);

	// Get all moves in the down direction
	this->addAllMovesInDirection(moves, piece, 1, 0);

	// Get all moves in the left direction
	this->addAllMovesInDirection(moves, piece, 0, -1);

	// Get all moves in the right direction
	this->addAllMovesInDirection(moves, piece, 0, 1);
}

// Add all possible moves of a given queen to a container reference given as a parameter
void Board::addQueenMoves(std::vector<Move>& moves, Piece piece)
{
	// The queen can move in every square that a rook and a bishop can move
	this->addRookMoves(moves, piece);
	this->addBishopMoves(moves, piece);
}

// Add all possible moves of a given king to a container reference given as a parameter
void Board::addKingMoves(std::vector<Move>& moves, Piece piece)
{
	// TODO Check if each move would put the king in check (NOT ONLY THE MOVES OF THE KING)
	
	int row = piece.getPosition().row();
	int column = piece.getPosition().column();

	// Check all position surrounding the king
	for (int i = row - 1; i <= row + 1; i++)
		for (int j = column - 1; j <= column + 1; j++)
			if (i != row || j != row) // Check if the square we try to make the move on is not the current one
				if (this->availableSquare(piece.getColor(), i, j))
					moves.push_back(Move(piece.getPosition(), Position(i, j)));

	// TODO Implement castle
}

std::vector<Move> Board::getWhiteMoves()
{
	std::vector<Move> moves;

	for (auto piece : this->whitePieces)
	{
		switch (piece.getType())
		{
		case Piece::Type::PAWN:
			this->addPawnMoves(moves, piece);
			break;
			
		case Piece::Type::BISHOP:
			this->addBishopMoves(moves, piece);
			break;

		case Piece::Type::KNIGHT:
			this->addKnightMoves(moves, piece);
			break;

		case Piece::Type::ROOK:
			this->addRookMoves(moves, piece);
			break;

		case Piece::Type::QUEEN:
			this->addRookMoves(moves, piece);
			break;
			
		case Piece::Type::KING:
			this->addKingMoves(moves, piece);
			break;

		default:
			break;
		}
	}

	return moves;
}

std::vector<Move> Board::getBlackMoves()
{
	std::vector<Move> moves;

	for (auto piece : this->blackPieces)
	{
		switch (piece.getType())
		{
		case Piece::Type::PAWN:
			this->addPawnMoves(moves, piece);
			break;

		case Piece::Type::BISHOP:
			this->addBishopMoves(moves, piece);
			break;

		case Piece::Type::KNIGHT:
			this->addKnightMoves(moves, piece);
			break;

		case Piece::Type::ROOK:
			this->addRookMoves(moves, piece);
			break;

		case Piece::Type::QUEEN:
			this->addRookMoves(moves, piece);
			break;

		case Piece::Type::KING:
			this->addKingMoves(moves, piece);
			break;

		default:
			break;
		}
	}

	return moves;
}

Piece& Board::getPiece(const Position position, const Piece::Color color)
{
	if (color == Piece::Color::WHITE)
	{
		for (Piece& piece : this->whitePieces)
			if (piece.getPosition() == position)
				return piece;
	}
	else
	{
		for (Piece& piece : this->blackPieces)
			if (piece.getPosition() == position)
				return piece;
	}
}

void Board::removePiece(const Position position, const Piece::Color color)
{
	if (color == Piece::Color::WHITE)
	{
		for (std::vector<Piece>::iterator it = this->whitePieces.begin(); it != this->whitePieces.end(); it++)
			if ((*it).getPosition() == position)
			{
				this->whitePieces.erase(it);
				return;
			}
	}
	else
	{
		for (std::vector<Piece>::iterator it = this->blackPieces.begin(); it != this->blackPieces.end(); it++)
			if ((*it).getPosition() == position)
			{
				this->blackPieces.erase(it);
				return;
			}
	}
}

void Board::makeMove(Move move)
{
	Position initialPosition = move.getInitialPosition();
	Position targetPosition = move.getTargetPosition();

	auto& initialSquare = this->board[initialPosition.row()][initialPosition.column()];
	auto& targetSquare = this->board[targetPosition.row()][targetPosition.column()];

	// If the target square is occupied by another piece, then remove it
	if (targetSquare.type != Piece::Type::NONE)
	{
		this->actionsMade.push(Actions::REMOVE_PIECE); // Mark the removal of a piece
		this->removedPieces.push(this->getPiece(targetPosition, targetSquare.color));
		this->removePiece(targetPosition, targetSquare.color);
	}

	// The target square gets the piece from the initial one
	targetSquare = initialSquare;

	// Move the piece object stored in one of the vectors
	Piece& piece = this->getPiece(initialPosition, initialSquare.color);
	piece.move(targetPosition);

	// Empty the initial square
	initialSquare = { Piece::Type::NONE, Piece::Color::UNCOLORED };
}

void Board::undoMove()
{
}
