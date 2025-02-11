#include "Board.h"
#include "Move.h"

int getColorIndex(const Piece::Color color)
{
	return color == Piece::Color::WHITE ? 0 : 1;
}

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
	this->blackKingPosition = Position(0, 4);

	// Add white king
	this->board[7][4] = Piece(Piece::Type::KING, Piece::Color::WHITE, Position(7, 4), false);
	this->whiteKingPosition = Position(7, 4);

	// Add remaining empty squares
	for (int i = 2; i <= 5; i++)
		for (int j = 0; j < 8; j++)
			this->board[i][j] = Piece(Piece::Type::NONE, Piece::Color::UNCOLORED, Position(i, j), false);

	// Store all occupied positions
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			Piece piece = this->board[i][j];
			if (piece.getType() != Piece::Type::NONE)
			{
				int index = getColorIndex(piece.getColor());
				this->occupiedSquares[index].insert(this->board[i][j].getPosition());
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

	if (square.getType() == Piece::Type::KING) // Return false if there is a king on the square
		return false;

	if (square.getColor() != color) // Return true if the square is not empty but the piece that is on the square is of the other color and is not a king
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
			if (square.getColor() != piece.getColor() && square.getType() != Piece::Type::KING) // If the other piece is not the same color and is not a king then we can capture it
				moves.push_back(Move(piece.getPosition(), position));

			return; // If we found another piece we must stop regardless of color or type
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
			// Check for promotion possibilty
			if (row - 1 == 0)
			{
				moves.push_back(Move(piece.getPosition(), Position(row - 1, column), Piece::Type::QUEEN));
				moves.push_back(Move(piece.getPosition(), Position(row - 1, column), Piece::Type::ROOK));
				moves.push_back(Move(piece.getPosition(), Position(row - 1, column), Piece::Type::BISHOP));
				moves.push_back(Move(piece.getPosition(), Position(row - 1, column), Piece::Type::KNIGHT));
			}
			else
			{
				moves.push_back(Move(piece.getPosition(), Position(row - 1, column)));
			}

			// If on first move then go one more square up
			if (!piece.hasMoved() && validPosition(row - 2, column) && this->board[row - 2][column].getType() == Piece::Type::NONE)
				moves.push_back(Move(piece.getPosition(), Position(row - 2, column)));
		}

		if (validPosition(row - 1, column - 1))
		{
			// Capture black piece up-left
			if (this->board[row - 1][column - 1].getType() != Piece::Type::NONE && this->board[row - 1][column - 1].getType() != Piece::Type::KING)
				if (this->board[row - 1][column - 1].getColor() != piece.getColor())
				{
					// Check for promotion possibilty
					if (row - 1 == 0)
					{
						moves.push_back(Move(piece.getPosition(), Position(row - 1, column - 1), Piece::Type::QUEEN));
						moves.push_back(Move(piece.getPosition(), Position(row - 1, column - 1), Piece::Type::ROOK));
						moves.push_back(Move(piece.getPosition(), Position(row - 1, column - 1), Piece::Type::BISHOP));
						moves.push_back(Move(piece.getPosition(), Position(row - 1, column - 1), Piece::Type::KNIGHT));
					}
					else
					{
						moves.push_back(Move(piece.getPosition(), Position(row - 1, column - 1)));
					}
				}

			// En passant
			if (row == 3)
			{
				Piece lastRemovedPiece = this->removedPieces.top();
				Piece lastAddedPiece = this->addedPieces.top();

				if (lastRemovedPiece.getType() == Piece::Type::PAWN && lastAddedPiece.getType() == Piece::Type::PAWN) // Check if the last moved piece is a pawn
					if (!lastRemovedPiece.hasMoved() && lastAddedPiece.getPosition() == Position(row, column - 1)) // Check if the pawn moved 2 pieces forward
						moves.push_back(Move(piece.getPosition(), Position(row - 1, column - 1)));
			}
		}

		
		if (validPosition(row - 1, column + 1))
		{
			// Capture black piece up-right
			if (this->board[row - 1][column + 1].getType() != Piece::Type::NONE && this->board[row - 1][column + 1].getType() != Piece::Type::KING)
				if (this->board[row - 1][column + 1].getColor() != piece.getColor())
				{
					// Check for promotion possibilty
					if (row - 1 == 0)
					{
						moves.push_back(Move(piece.getPosition(), Position(row - 1, column + 1), Piece::Type::QUEEN));
						moves.push_back(Move(piece.getPosition(), Position(row - 1, column + 1), Piece::Type::ROOK));
						moves.push_back(Move(piece.getPosition(), Position(row - 1, column + 1), Piece::Type::BISHOP));
						moves.push_back(Move(piece.getPosition(), Position(row - 1, column + 1), Piece::Type::KNIGHT));
					}
					else
					{
						moves.push_back(Move(piece.getPosition(), Position(row - 1, column + 1)));
					}
				}

			// En passant
			if (row == 3)
			{
				Piece lastRemovedPiece = this->removedPieces.top();
				Piece lastAddedPiece = this->addedPieces.top();

				if (lastRemovedPiece.getType() == Piece::Type::PAWN && lastAddedPiece.getType() == Piece::Type::PAWN) // Check if the last moved piece is a pawn
					if (!lastRemovedPiece.hasMoved() && lastAddedPiece.getPosition() == Position(row, column + 1)) // Check if the pawn moved 2 pieces forward
						moves.push_back(Move(piece.getPosition(), Position(row - 1, column + 1)));
			}
		}
	}
	else
	{
		// Go one square down
		if (validPosition(row + 1, column) && this->board[row + 1][column].getType() == Piece::Type::NONE)
		{
			// Check for promotion possibilty
			if (row + 1 == 7)
			{
				moves.push_back(Move(piece.getPosition(), Position(row + 1, column), Piece::Type::QUEEN));
				moves.push_back(Move(piece.getPosition(), Position(row + 1, column), Piece::Type::ROOK));
				moves.push_back(Move(piece.getPosition(), Position(row + 1, column), Piece::Type::BISHOP));
				moves.push_back(Move(piece.getPosition(), Position(row + 1, column), Piece::Type::KNIGHT));
			}
			else
			{
				moves.push_back(Move(piece.getPosition(), Position(row + 1, column)));
			}

			// If on first move then go one more square down
			if (!piece.hasMoved() && validPosition(row + 2, column) && this->board[row + 2][column].getType() == Piece::Type::NONE)
				moves.push_back(Move(piece.getPosition(), Position(row + 2, column)));
		}

		if (validPosition(row + 1, column - 1))
		{
			// Capture white piece down-left
			if (this->board[row + 1][column - 1].getType() != Piece::Type::NONE && this->board[row + 1][column - 1].getType() != Piece::Type::KING)
				if (this->board[row + 1][column - 1].getColor() != piece.getColor())
				{
					// Check for promotion possibilty
					if (row + 1 == 7)
					{
						moves.push_back(Move(piece.getPosition(), Position(row + 1, column - 1), Piece::Type::QUEEN));
						moves.push_back(Move(piece.getPosition(), Position(row + 1, column - 1), Piece::Type::ROOK));
						moves.push_back(Move(piece.getPosition(), Position(row + 1, column - 1), Piece::Type::BISHOP));
						moves.push_back(Move(piece.getPosition(), Position(row + 1, column - 1), Piece::Type::KNIGHT));
					}
					else
					{
						moves.push_back(Move(piece.getPosition(), Position(row + 1, column - 1)));
					}
				}

			// En passant
			if (row == 4)
			{
				Piece lastRemovedPiece = this->removedPieces.top();
				Piece lastAddedPiece = this->addedPieces.top();

				if (lastRemovedPiece.getType() == Piece::Type::PAWN && lastAddedPiece.getType() == Piece::Type::PAWN) // Check if the last moved piece is a pawn
					if (!lastRemovedPiece.hasMoved() && lastAddedPiece.getPosition() == Position(row, column - 1)) // Check if the pawn moved 2 pieces forward
						moves.push_back(Move(piece.getPosition(), Position(row + 1, column - 1)));
			}
		}

		if (validPosition(row + 1, column + 1))
		{
			// Capture white piece down-right
			if (this->board[row + 1][column + 1].getType() != Piece::Type::NONE && this->board[row + 1][column + 1].getType() != Piece::Type::KING)
				if (this->board[row + 1][column + 1].getColor() != piece.getColor())
				{
					// Check for promotion possibilty
					if (row + 1 == 7)
					{
						moves.push_back(Move(piece.getPosition(), Position(row + 1, column + 1), Piece::Type::QUEEN));
						moves.push_back(Move(piece.getPosition(), Position(row + 1, column + 1), Piece::Type::ROOK));
						moves.push_back(Move(piece.getPosition(), Position(row + 1, column + 1), Piece::Type::BISHOP));
						moves.push_back(Move(piece.getPosition(), Position(row + 1, column + 1), Piece::Type::KNIGHT));
					}
					else
					{
						moves.push_back(Move(piece.getPosition(), Position(row + 1, column + 1)));
					}
				}

			// En passant
			if (row == 4)
			{
				Piece lastRemovedPiece = this->removedPieces.top();
				Piece lastAddedPiece = this->addedPieces.top();

				if (lastRemovedPiece.getType() == Piece::Type::PAWN && lastAddedPiece.getType() == Piece::Type::PAWN) // Check if the last moved piece is a pawn
					if (!lastRemovedPiece.hasMoved() && lastAddedPiece.getPosition() == Position(row, column + 1)) // Check if the pawn moved 2 pieces forward
						moves.push_back(Move(piece.getPosition(), Position(row + 1, column + 1)));
			}
		}
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
	int row = piece.getPosition().row();
	int column = piece.getPosition().column();

	// Check all position surrounding the king
	for (int i = row - 1; i <= row + 1; i++)
		for (int j = column - 1; j <= column + 1; j++)
			if (i != row || j != column) // Check if the square we try to make the move on is not the current one
				if (this->availableSquare(piece.getColor(), i, j))
					moves.push_back(Move(piece.getPosition(), Position(i, j)));

	// Check if the king has moved
	if (!piece.hasMoved())
	{
		// Get the color opposing the color of the king
		auto otherColor = piece.getColor() == Piece::Color::WHITE ? Piece::Color::BLACK : Piece::Color::WHITE;
		
		// Check if the queenside rook has moved
		Piece possibleRook = this->getPiece(Position(row, 0));
		if (possibleRook.getType() == Piece::Type::ROOK && !possibleRook.hasMoved())
		{
			bool canCastle = true;

			// Check if the square between the king and the rook are empty
			for (int columnToCheck = 1; columnToCheck < column && canCastle; columnToCheck++)
				if (this->board[row][columnToCheck].getType() != Piece::Type::NONE)
					canCastle = false;

			// Check if the squares the king would travel are attacked by the other color
			for (int columnToCheck = column - 2; columnToCheck <= column && canCastle; columnToCheck++)
				if (this->isAttackedBy(Position(row, columnToCheck), otherColor))
					canCastle = false;
					
					
			if (canCastle)
			{
				moves.push_back(Move(piece.getPosition(), Position(row, column - 2)));
			}
		}

		// Check if the kingside rook has moved
		Piece possibleRook = this->getPiece(Position(row, 7));
		if (possibleRook.getType() == Piece::Type::ROOK && !possibleRook.hasMoved())
		{
			bool canCastle = true;

			// Check if the square between the king and the rook are empty
			for (int columnToCheck = column + 1; columnToCheck < 7 && canCastle; columnToCheck++)
				if (this->board[row][columnToCheck].getType() != Piece::Type::NONE)
					canCastle = false;

			// Check if the squares the king would travel are attacked by the other color
			for (int columnToCheck = column; columnToCheck <= column + 2 && canCastle; columnToCheck++)
				if (this->isAttackedBy(Position(row, columnToCheck), otherColor))
					canCastle = false;
					

			if (canCastle)
			{
				moves.push_back(Move(piece.getPosition(), Position(row, column + 2)));
			}
		}
	}
}

void Board::addPiece(const Piece piece, const bool silent)
{
	// Only mark changes on the helper stacks if silent is false
	if (!silent)
	{
		this->actionsMade.push(Action::ADD_PIECE); // Mark adding a piece on the board
		this->addedPieces.push(piece);
	}

	Position position = piece.getPosition();
	this->board[position.row()][position.column()] = piece; // Store the piece on the board

	// Mark the piece position as occupied by the piece color
	int colorIndex = getColorIndex(piece.getColor());
	this->occupiedSquares[colorIndex].insert(position);

	// If the added piece is a king then update its stored position
	if (piece.getType() == Piece::Type::KING)
	{
		if (piece.getColor() == Piece::Color::WHITE)
			this->whiteKingPosition = position;
		else
			this->blackKingPosition = position;
	}
}

void Board::removePiece(const Piece piece, const bool silent)
{
	// Only mark changes on the helper stacks if silent is false
	if (!silent)
	{
		this->actionsMade.push(Action::REMOVE_PIECE); // Mark the removal of a piece
		this->removedPieces.push(piece); // Store the removed piece on a separate stack
	}

	Position position = piece.getPosition();
	this->board[position.row()][position.column()] = Piece(position); // Empty the board square

	// Unmark the previously occupied square
	int colorIndex = getColorIndex(piece.getColor());
	this->occupiedSquares[colorIndex].erase(position);
}

bool Board::isAttackedBy(Position position, const Piece::Color attackingColor)
{
	if (attackingColor == Piece::Color::BLACK)
	{
		// Check for a pawn in the up-left direction
		if (validPosition(position.UpLeft()) && this->getPiece(position.UpLeft()).getType() == Piece::Type::PAWN && this->getPiece(position.UpLeft()).getColor() == attackingColor)
			return true;

		// Check for a pawn in the up-right direction
		if (validPosition(position.UpRight()) && this->getPiece(position.UpRight()).getType() == Piece::Type::PAWN && this->getPiece(position.UpRight()).getColor() == attackingColor)
			return true;
	}
	else
	{
		// Check for a pawn in the down-left direction
		if (validPosition(position.DownLeft()) && this->getPiece(position.DownLeft()).getType() == Piece::Type::PAWN && this->getPiece(position.DownLeft()).getColor() == attackingColor)
			return true;

		// Check for a pawn in the down-right direction
		if (validPosition(position.DownRight()) && this->getPiece(position.DownRight()).getType() == Piece::Type::PAWN && this->getPiece(position.DownRight()).getColor() == attackingColor)
			return true;
	}

	Position positionToCheck;

	// Check in the up direction
	positionToCheck = position.Up();
	while (validPosition(positionToCheck))
	{
		Piece::Type pieceType = this->getPiece(positionToCheck).getType();
		Piece::Color pieceColor = this->getPiece(positionToCheck).getColor();

		// If the first piece we encounter is not of the attacking color then the piece can't be attacked from this direction
		if (pieceType != Piece::Type::NONE && pieceColor != attackingColor)
			break;

		// If the first piece we encounter is a rook or queen of attacking color then the piece is attacked
		if (pieceColor == attackingColor && (pieceType == Piece::Type::ROOK || pieceType == Piece::Type::QUEEN))
			return true;

		positionToCheck = positionToCheck.Up();
	}

	// Check in the down direction
	positionToCheck = position.Down();
	while (validPosition(positionToCheck))
	{
		Piece::Type pieceType = this->getPiece(positionToCheck).getType();
		Piece::Color pieceColor = this->getPiece(positionToCheck).getColor();

		// If the first piece we encounter is not of the attacking color then the piece can't be attacked from this direction
		if (pieceType != Piece::Type::NONE && pieceColor != attackingColor)
			break;

		// If the first piece we encounter is a rook or queen of attacking color then the piece is attacked
		if (pieceColor == attackingColor && (pieceType == Piece::Type::ROOK || pieceType == Piece::Type::QUEEN))
			return true;

		positionToCheck = positionToCheck.Down();
	}

	// Check in the left direction
	positionToCheck = position.Left();
	while (validPosition(positionToCheck))
	{
		Piece::Type pieceType = this->getPiece(positionToCheck).getType();
		Piece::Color pieceColor = this->getPiece(positionToCheck).getColor();

		// If the first piece we encounter is not of the attacking color then the piece can't be attacked from this direction
		if (pieceType != Piece::Type::NONE && pieceColor != attackingColor)
			break;

		// If the first piece we encounter is a rook or queen of attacking color then the piece is attacked
		if (pieceColor == attackingColor && (pieceType == Piece::Type::ROOK || pieceType == Piece::Type::QUEEN))
			return true;

		positionToCheck = positionToCheck.Left();
	}

	// Check in the right direction
	positionToCheck = position.Right();
	while (validPosition(positionToCheck))
	{
		Piece::Type pieceType = this->getPiece(positionToCheck).getType();
		Piece::Color pieceColor = this->getPiece(positionToCheck).getColor();

		// If the first piece we encounter is not of the attacking color then the piece can't be attacked from this direction
		if (pieceType != Piece::Type::NONE && pieceColor != attackingColor)
			break;

		// If the first piece we encounter is a rook or queen of attacking color then the piece is attacked
		if (pieceColor == attackingColor && (pieceType == Piece::Type::ROOK || pieceType == Piece::Type::QUEEN))
			return true;

		positionToCheck = positionToCheck.Right();
	}

	// Check in the up-left direction
	positionToCheck = position.UpLeft();
	while (validPosition(positionToCheck))
	{
		Piece::Type pieceType = this->getPiece(positionToCheck).getType();
		Piece::Color pieceColor = this->getPiece(positionToCheck).getColor();

		// If the first piece we encounter is not of the attacking color then the piece can't be attacked from this direction
		if (pieceType != Piece::Type::NONE && pieceColor != attackingColor)
			break;

		// If the first piece we encounter is a bishop or queen of attacking color then the piece is attacked
		if (pieceColor == attackingColor && (pieceType == Piece::Type::BISHOP || pieceType == Piece::Type::QUEEN))
			return true;

		positionToCheck = positionToCheck.UpLeft();
	}

	// Check in the up-right direction
	positionToCheck = position.UpRight();
	while (validPosition(positionToCheck))
	{
		Piece::Type pieceType = this->getPiece(positionToCheck).getType();
		Piece::Color pieceColor = this->getPiece(positionToCheck).getColor();

		// If the first piece we encounter is not of the attacking color then the piece can't be attacked from this direction
		if (pieceType != Piece::Type::NONE && pieceColor != attackingColor)
			break;

		// If the first piece we encounter is a bishop or queen of attacking color then the piece is attacked
		if (pieceColor == attackingColor && (pieceType == Piece::Type::BISHOP || pieceType == Piece::Type::QUEEN))
			return true;

		positionToCheck = positionToCheck.UpRight();
	}

	// Check in the down-left direction
	positionToCheck = position.DownLeft();
	while (validPosition(positionToCheck))
	{
		Piece::Type pieceType = this->getPiece(positionToCheck).getType();
		Piece::Color pieceColor = this->getPiece(positionToCheck).getColor();

		// If the first piece we encounter is not of the attacking color then the piece can't be attacked from this direction
		if (pieceType != Piece::Type::NONE && pieceColor != attackingColor)
			break;

		// If the first piece we encounter is a bishop or queen of attacking color then the piece is attacked
		if (pieceColor == attackingColor && (pieceType == Piece::Type::BISHOP || pieceType == Piece::Type::QUEEN))
			return true;

		positionToCheck = positionToCheck.DownLeft();
	}

	// Check in the down-right direction
	positionToCheck = position.DownRight();
	while (validPosition(positionToCheck))
	{
		Piece::Type pieceType = this->getPiece(positionToCheck).getType();
		Piece::Color pieceColor = this->getPiece(positionToCheck).getColor();

		// If the first piece we encounter is not of the attacking color then the piece can't be attacked from this direction
		if (pieceType != Piece::Type::NONE && pieceColor != attackingColor)
			break;

		// If the first piece we encounter is a bishop or queen of attacking color then the piece is attacked
		if (pieceColor == attackingColor && (pieceType == Piece::Type::BISHOP || pieceType == Piece::Type::QUEEN))
			return true;

		positionToCheck = positionToCheck.DownRight();
	}

	// Check for knights
	int row = position.row();
	int column = position.column();

	// All possible positions from which a knight can attack the piece
	Piece pieces[8] =
	{
		validPosition(row - 1, column - 2) ? this->board[row - 1][column - 2] : Piece(),
		validPosition(row - 2, column - 1) ? this->board[row - 2][column - 1] : Piece(),
		validPosition(row - 2, column + 1) ? this->board[row - 2][column + 1] : Piece(),
		validPosition(row - 1, column + 2) ? this->board[row - 1][column + 2] : Piece(),
		validPosition(row + 1, column - 2) ? this->board[row + 1][column - 2] : Piece(),
		validPosition(row + 2, column - 1) ? this->board[row + 2][column - 1] : Piece(),
		validPosition(row + 2, column + 1) ? this->board[row + 2][column + 1] : Piece(),
		validPosition(row + 1, column + 2) ? this->board[row + 1][column + 2] : Piece()
	};

	// Check if there is a knight of the attacking color on each of the possible positions
	for (int i = 0; i < 8; i++)
		if (pieces[i].getType() == Piece::KNIGHT && pieces[i].getColor() == attackingColor)
			return true;

	// Check for kings
	row = position.row();
	column = position.column();

	for (int i = row - 1; i <= row + 1; i++)
		for (int j = column - 1; j <= column + 1; j++)
			if (i != row || j != column && validPosition(i, j))
				if (this->board[i][j].getType() == Piece::Type::KING && this->board[i][j].getColor() == attackingColor)
					return true;

	return false;
}

bool Board::isInCheck(const Piece::Color color)
{
	if (color == Piece::Color::WHITE)
		return this->isAttackedBy(this->whiteKingPosition, Piece::Color::BLACK);
	return this->isAttackedBy(this->blackKingPosition, Piece::Color::WHITE);
}

bool Board::checkmate(const Piece::Color color)
{
	// Check if the king is in check or not
	if (!this->isInCheck(color))
		return false;

	// Get all possible moves
	std::vector<Move> moves = this->getMoves(color);

	// Check each move and if the king gets out of check after it then it is not checkmate
	for (Move move : moves)
	{
		// Make the move on the board
		this->makeMove(move);

		// Check if the king escaped check
		if (!this->isInCheck(color))
		{
			// If so, undo the move and return false
			this->undoMove();
			return false;
		}
		
		// If this line is reached then the current move did not get the king out of check and has to be undone
		this->undoMove();
	}

	// Return true if no move got the king out of check
	return true;
}

std::vector<Move> Board::getMoves(const Piece::Color playerColor)
{
	int index = getColorIndex(playerColor);
	std::vector<Move> moves;

	for (Position position : this->occupiedSquares[index])
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
			this->addQueenMoves(moves, piece);
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

void Board::castle(Move move)
{
	Position kingInitialPosition = move.getInitialPosition();
	Position kingTargetPosition = move.getTargetPosition();
	Piece king = this->getPiece(kingInitialPosition);
	
	Position rookTargetPosition;
	Piece rook;

	// Get rook information
	if (king.getColor() == Piece::Color::WHITE) // White king castles
	{
		if (kingTargetPosition == Position(7, 6)) // Kingside
		{
			rookTargetPosition = Position(7, 5);
			rook = this->getPiece(Position(7, 7));
		}
		else // Queenside
		{
			rookTargetPosition = Position(7, 3);
			rook = this->getPiece(Position(7, 0));
		}
	}
	else // Black king castles
	{
		if (kingTargetPosition == Position(0, 6)) // Kingside
		{
			rookTargetPosition = Position(0, 5);
			rook = this->getPiece(Position(0, 7));
		}
		else // Queenside
		{
			rookTargetPosition = Position(0, 3);
			rook = this->getPiece(Position(0, 0));
		}
	}

	// Remove the king from his position
	this->removePiece(king);

	// Create a new king piece at the target position with hasMoved = true
	Piece movedKing = Piece(king.getType(), king.getColor(), kingTargetPosition, true);
	this->addPiece(movedKing);

	// Remove the rook from his position
	this->removePiece(rook);

	// Create a new rook piece at the target position with hasMoved = true
	Piece movedRook = Piece(rook.getType(), rook.getColor(), rookTargetPosition, true);
	this->addPiece(movedRook);

	// Add a separator at the end of the move
	this->actionsMade.push(Action::SEPARATOR);
}

void Board::enPassant(Move move)
{
	Position initialPosition = move.getInitialPosition();
	Position targetPosition = move.getTargetPosition();
	Piece pawn = this->getPiece(initialPosition);

	// Remove the captured pawn below targetPosition
	this->removePiece(this->getPiece(targetPosition.Down()));

	// Remove the pawn from its initial position
	this->removePiece(pawn);

	// Create a new pawn piece at the target position with hasMoved = true
	Piece movedPawn = Piece(pawn.getType(), pawn.getColor(), targetPosition, true);
	this->addPiece(movedPawn);

	this->actionsMade.push(Action::SEPARATOR);
}

void Board::makeMove(Move move)
{
	Position initialPosition = move.getInitialPosition();
	Position targetPosition = move.getTargetPosition();

	// Check if the move is a castle
	if (initialPosition == this->whiteKingPosition && !this->getPiece(initialPosition).hasMoved())
	{
		if (targetPosition == Position(7, 6) || targetPosition == Position(7, 2))
		{
			this->castle(move);
			return;
		}
	}
	else if (initialPosition == this->blackKingPosition && !this->getPiece(initialPosition).hasMoved())
	{
		if (targetPosition == Position(0, 6) || targetPosition == Position(0, 2))
		{
			this->castle(move);
			return;
		}
	}

	// Check if the move is an en passant move
	if (this->getPiece(initialPosition).getType() == Piece::Type::PAWN && this->getPiece(targetPosition).getType() == Piece::Type::NONE)
	{
		if (targetPosition.column() != initialPosition.column()) // Check if the pawn moves diagonally
		{
			this->enPassant(move);
			return;
		}
	}

	Piece pieceToMove = this->board[initialPosition.row()][initialPosition.column()];
	Piece pieceToGetCaptured = this->board[targetPosition.row()][targetPosition.column()];

	// If the target square is occupied by another piece, then remove it
	if (pieceToGetCaptured.getType() != Piece::Type::NONE)
	{
		this->removePiece(pieceToGetCaptured);
	}

	// Remove the piece to move from its square
	this->removePiece(pieceToMove);

	// Add the piece to move to the target square
	Piece movedPiece = Piece(pieceToMove.getType(), pieceToMove.getColor(), targetPosition, true); // Get a new piece with correct position and hasMoved
	if (move.getPromotionType() != Piece::Type::NONE && pieceToMove.getType() == Piece::Type::PAWN) // Check if the move is a pawn promotion
		movedPiece.setType(move.getPromotionType());
	this->addPiece(movedPiece);

	// Add a separator to the stack to mark the end of the move
	this->actionsMade.push(Action::SEPARATOR);
}

void Board::undoMove()
{
	if (this->actionsMade.empty())
		return;

	// Pop the separator
	if (this->actionsMade.top() == Action::SEPARATOR)
		this->actionsMade.pop();
	
	while (!this->actionsMade.empty())
	{
		Action action = this->actionsMade.top();
		if (action == Action::SEPARATOR) // The undo is complete, leave a separator on top of stack
			break;

		// Remove action from stack
		this->actionsMade.pop();

		if (action == Action::REMOVE_PIECE)
		{
			// Get the last removed piece
			Piece removedPiece = this->removedPieces.top();
			this->removedPieces.pop();

			// Add the piece back with silent = true to avoid modifying the helper stacks
			this->addPiece(removedPiece, true);
		}
		else if (action == Action::ADD_PIECE)
		{
			// Get the last added piece
			Piece addedPiece = this->addedPieces.top();
			this->addedPieces.pop();

			// Remove the piece with silent = true to avoid modifying the helper stacks
			this->removePiece(addedPiece, true);
		}
	}
}

// Compute the value of the current state of the board (positive values are better for white and negative values are better for black)
int Board::evaluate() const
{
	int result = 0;

	for (int colorIndex = 0; colorIndex < 2; colorIndex++) // 0 for white and 1 for black
		for (Position position : this->occupiedSquares[colorIndex])
		{
			int row = position.row();
			int column = position.column();

			int pieceType = this->board[row][column].getType();
			int pieceColor = this->board[row][column].getColor();

			int squareValue = pieceValue[pieceType]; // Initialize the value of the square with the value of the piece belonging to that square

			if (pieceColor == Piece::Color::BLACK)
			{
				// The position value table must be inverted for black pieces
				squareValue += positionValue[pieceType][7 - row][column];

				// The value of the square is negative for black pieces
				squareValue = -squareValue;
			}
			else
			{
				// Simply add the positional value for a white piece
				squareValue += positionValue[pieceType][row][column];
			}

			result += squareValue;
		}

	return result;
}

Move Board::getBestMove(const Piece::Color playerToMove)
{
	return this->minimax(searchDepth, INT_MIN, INT_MAX, playerToMove == Piece::Color::WHITE).move;
}

Board::minimaxResult Board::minimax(int depth, int alpha, int beta, bool whiteToMove)
{
	// Check if the game is over
	if (this->checkmate(whiteToMove ? Piece::Color::WHITE : Piece::Color::BLACK))
		return whiteToMove ? Board::minimaxResult(Move(), INT_MIN + 1) : Board::minimaxResult(Move(), INT_MAX - 1);

	if (depth == 0)
		return Board::minimaxResult(Move(), this->evaluate());

	if (whiteToMove)
	{
		// Initialize the result with an empty move and the smallest possible value
		Board::minimaxResult result(Move(), INT_MIN);

		// Get all the possible moves of the white player
		std::vector<Move> moves = this->getMoves(Piece::Color::WHITE);

		for (Move move : moves)
		{
			this->makeMove(move); // Make the current move

			if (!this->isInCheck(Piece::Color::WHITE)) // Check if the move is valid
			{
				Board::minimaxResult child = this->minimax(depth - 1, alpha, beta, false); // Evaluate the result of the current move and go deeper in the recursion tree
				if (child.value > result.value) // If the current result is better then store it
				{
					result.move = move;
					result.value = child.value;
				}
				alpha = std::max(alpha, child.value);
			}

			this->undoMove(); // Undo the current move to bring the table back to its original state

			if (beta <= alpha)
				break;
		}

		return result;
	}
	else
	{
		// Initialize the result with an empty move and the biggest possible value
		Board::minimaxResult result(Move(), INT_MAX);

		// Get all the possible moves of the black player
		std::vector<Move> moves = this->getMoves(Piece::Color::BLACK);

		for (Move move : moves)
		{
			this->makeMove(move); // Make the current move

			if (!this->isInCheck(Piece::Color::BLACK)) // Check if the move is valid
			{
				Board::minimaxResult child = this->minimax(depth - 1, alpha, beta, true); // Evaluate the result of the current move and go deeper in recursion tree
				if (child.value < result.value) // If the current result is better then store it
				{
					result.move = move;
					result.value = child.value;
				}
				beta = std::min(beta, child.value);
			}

			this->undoMove(); // Undo the current move to bring the table back to its original state

			if (beta <= alpha)
				break;
		}

		return result;
	}
}

std::string Board::toString()
{
	std::string boardString;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			switch (this->board[i][j].getType())
			{
			case Piece::Type::PAWN:
				boardString += "P";
				break;
			case Piece::Type::BISHOP:
				boardString += "B";
				break;
			case Piece::Type::KNIGHT:
				boardString += "K";
				break;
			case Piece::Type::ROOK:
				boardString += "R";
				break;
			case Piece::Type::QUEEN:
				boardString += "Q";
				break;
			case Piece::Type::KING:
				boardString += "X";
				break;
			default:
				boardString += "O";
				break;
			}

		boardString += "\n";
	}

	return boardString;
}

Board::minimaxResult::minimaxResult(const Move move, const int value) : move(move), value(value) {}
