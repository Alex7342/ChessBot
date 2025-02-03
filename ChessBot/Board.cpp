#include "Board.h"
#include "Move.h"

Board::Board()
{
	// Add pawns
	for (int j = 0; j < 8; j++)
	{
		// Black
		this->board[1][j] = Piece(Piece::Type::PAWN, Piece::Color::BLACK, Position(1, j), false);

		// White
		this->board[6][j] = Piece(Piece::Type::PAWN, Piece::Color::WHITE, Position(6, j), false);
	}

	// Add black rooks
	this->board[0][0] = Piece(Piece::Type::ROOK, Piece::Color::BLACK, Position(0, 0), false);

	this->board[0][7] = Piece(Piece::Type::ROOK, Piece::Color::BLACK, Position(0, 7), false);

	// Add white rooks
	this->board[7][0] = Piece(Piece::Type::ROOK, Piece::Color::WHITE, Position(7, 0), false);
	this->board[7][7] = Piece(Piece::Type::ROOK, Piece::Color::WHITE, Position(7, 7), false);

	// Add black knights
	this->board[0][1] = Piece(Piece::Type::KNIGHT, Piece::Color::BLACK, Position(0, 1), false);
	this->board[0][6] = Piece(Piece::Type::KNIGHT, Piece::Color::BLACK, Position(0, 6), false);

	// Add white knights
	this->board[7][1] = Piece(Piece::Type::KNIGHT, Piece::Color::WHITE, Position(7, 1), false);
	this->board[7][6] = Piece(Piece::Type::KNIGHT, Piece::Color::WHITE, Position(7, 6), false);

	// Add black bishops
	this->board[0][2] = Piece(Piece::Type::BISHOP, Piece::Color::BLACK, Position(0, 2), false);
	this->board[0][5] = Piece(Piece::Type::BISHOP, Piece::Color::BLACK, Position(0, 5), false);

	// Add white bishops
	this->board[7][2] = Piece(Piece::Type::BISHOP, Piece::Color::WHITE, Position(7, 2), false);
	this->board[7][5] = Piece(Piece::Type::BISHOP, Piece::Color::WHITE, Position(7, 5), false);

	// Add black queen
	this->board[0][3] = Piece(Piece::Type::QUEEN, Piece::Color::BLACK, Position(0, 3), false);

	// Add white queen
	this->board[7][3] = Piece(Piece::Type::QUEEN, Piece::Color::WHITE, Position(7, 3), false);

	// Add black king
	this->board[0][4] = Piece(Piece::Type::KING, Piece::Color::BLACK, Position(0, 4), false);

	// Add white king
	this->board[7][4] = Piece(Piece::Type::KING, Piece::Color::WHITE, Position(7, 4), false);

	// Add remaining empty squares
	for (int i = 2; i <= 5; i++)
		for (int j = 0; j < 8; j++)
			this->board[i][j] = Piece(Piece::Type::NONE, Piece::Color::UNCOLORED, Position(i, j), false);

	// Store all occupied positions
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (this->board[i][j].getColor() == Piece::Color::WHITE)
			{
				this->whiteSquares.insert(this->board[i][j].getPosition());
			}
			else if (this->board[i][j].getColor() == Piece::Color::BLACK)
			{
				this->blackSquares.insert(this->board[i][j].getPosition());
			}
		}
}

Piece Board::getPiece(const Position position)
{
	return this->board[position.row()][position.column()];
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

	Piece square = this->board[row][column];

	if (square.getType() == Piece::Type::NONE) // Return true if the square is empty
		return true;

	if (square.getColor() != color) // Return true if the square is not empty but the piece that is on the square is of the other color
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

		Piece square = this->board[position.row()][position.column()]; // Get the current square

		if (square.getType() != Piece::Type::NONE)
		{
			if (square.getColor() != piece.getColor()) // If the other piece of not the same color then we can capture it
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
		if (validPosition(row - 1, column) && this->board[row - 1][column].getType() == Piece::Type::NONE)
		{
			moves.push_back(Move(piece.getPosition(), Position(row - 1, column)));

			// If on first move then go one more square up
			if (!piece.hasMoved() && validPosition(row - 2, column) && this->board[row - 2][column].getType() == Piece::Type::NONE)
				moves.push_back(Move(piece.getPosition(), Position(row - 2, column)));
		}

		// Capture black piece up-left
		if (validPosition(row - 1, column - 1))
			if (this->board[row - 1][column - 1].getType() != Piece::Type::NONE && this->board[row - 1][column - 1].getColor() != piece.getColor())
				moves.push_back(Move(piece.getPosition(), Position(row - 1, column - 1)));

		// Capture black piece up-right
		if (validPosition(row - 1, column + 1))
			if (this->board[row - 1][column + 1].getType() != Piece::Type::NONE && this->board[row - 1][column + 1].getColor() != piece.getColor())
				moves.push_back(Move(piece.getPosition(), Position(row - 1, column + 1)));

		// TODO Implement en passant
	}
	else
	{
		// Go one square down
		if (validPosition(row + 1, column) && this->board[row + 1][column].getType() == Piece::Type::NONE)
		{
			moves.push_back(Move(piece.getPosition(), Position(row + 1, column)));

			// If on first move then go one more square down
			if (!piece.hasMoved() && validPosition(row + 2, column) && this->board[row + 2][column].getType() == Piece::Type::NONE)
				moves.push_back(Move(piece.getPosition(), Position(row + 2, column)));
		}

		// Capture white piece down-left
		if (validPosition(row + 1, column - 1))
			if (this->board[row + 1][column - 1].getType() != Piece::Type::NONE && this->board[row + 1][column - 1].getColor() != piece.getColor())
				moves.push_back(Move(piece.getPosition(), Position(row + 1, column - 1)));

		// Capture white piece down-right
		if (validPosition(row + 1, column + 1))
			if (this->board[row + 1][column + 1].getType() != Piece::Type::NONE && this->board[row + 1][column + 1].getColor() != piece.getColor())
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

	for (Position position : this->whiteSquares)
	{
		Piece piece = this->getPiece(position);
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

	for (Position position : this->blackSquares)
	{
		Piece piece = this->getPiece(position);
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

void Board::makeMove(Move move)
{
	Position initialPosition = move.getInitialPosition();
	Position targetPosition = move.getTargetPosition();

	auto pieceToMove = this->board[initialPosition.row()][initialPosition.column()];
	auto pieceToGetRemoved = this->board[targetPosition.row()][targetPosition.column()];

	// If the target square is occupied by another piece, then remove it
	if (pieceToGetRemoved.getType() != Piece::Type::NONE)
	{
		this->actionsMade.push(Actions::REMOVE_PIECE); // Mark the removal of a piece
		this->removedPieces.push(pieceToGetRemoved); // Store the removed piece on a separate stack

		this->board[targetPosition.row()][targetPosition.column()] = Piece(targetPosition); // Empty the board square
		
		// Unmark the previously occupied square
		if (pieceToGetRemoved.getColor() == Piece::Color::WHITE)
			this->whiteSquares.erase(pieceToGetRemoved.getPosition());
		else
			this->blackSquares.erase(pieceToGetRemoved.getPosition());
	}

	// The target square gets the piece from the initial one
	this->actionsMade.push(Actions::MOVE_PIECE); // Mark the movement of a piece
	pieceToMove.move(targetPosition); // Perform the move on the piece object
	this->board[targetPosition.row()][targetPosition.column()] = pieceToMove; // Store the move on the board

	// Empty the initial square
	this->board[initialPosition.row()][initialPosition.column()] = Piece(initialPosition); // Empty the square from which the piece moved

	// Add a separator to the stack to mark the end of the move
	this->actionsMade.push(Actions::SEPARATOR);
}

