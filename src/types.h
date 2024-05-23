
#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <unordered_map>
#include <vector>

typedef int Piece;
typedef int Square;
typedef int Color;

const std::string piece_to_char = " PNBRQKpnbrqk", STARTPOS = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

enum Pieces
{
  NO_PIECE, W_PAWN, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
            B_PAWN, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
};

enum Squares
{
  H1, G1, F1, E1, D1, C1, B1, A1,
  H2, G2, F2, E2, D2, C2, B2, A2,
  H3, G3, F3, E3, D3, C3, B3, A3,
  H4, G4, F4, E4, D4, C4, B4, A4,
  H5, G5, F5, E5, D5, C5, B5, A5,
  H6, G6, F6, E6, D6, C6, B6, A6,
  H7, G7, F7, E7, D7, C7, B7, A7,
  H8, G8, F8, E8, D8, C8, B8, A8,
  SQUARE_NB = 64
};

enum Colors { WHITE, BLACK };

class Board {
public:
  std::vector<std::string> generate_moves();
  void make_move(Square from, Square to);
  void set(const std::string& fen);
  Board();
  Board(const std::string& fen) { set(fen); }
  std::string to_string();
private:
  Piece pieces[SQUARE_NB];
  Color side_to_move;
};

typedef std::unordered_map<std::string, Board> VarMap;

#endif
