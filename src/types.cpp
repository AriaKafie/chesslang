
#include "types.h"

#include <sstream>

std::string square_to_uci(Square sq) { return std::string(1, "hgfedcba"[sq % 8]) + std::string(1, "12345678"[sq / 8]); }

std::string move_to_uci(Square from, Square to) { return square_to_uci(from) + square_to_uci(to); }

void Board::make_move(Square from, Square to)
{
  pieces[to] = pieces[from];
  pieces[from] = NO_PIECE;
}

Board::Board() { memset(pieces, NO_PIECE, sizeof(pieces)); }

void Board::set(const std::string& fen)
{
  memset(pieces, NO_PIECE, sizeof(pieces));

  char token;
  Square sq = A8;
  size_t piece;

  std::istringstream is(fen);
  is >> std::noskipws;

  while (is >> token && !std::isspace(token))
  {
    if (std::isdigit(token))
      sq -= token - '0';
    else if ((piece = piece_to_char.find(token)) != std::string::npos)
      pieces[sq--] = piece;
  }

  is >> std::skipws;
  is >> token;
  side_to_move = token == 'w' ? WHITE : BLACK;
}

std::string Board::to_string()
{
  std::stringstream ss;
  ss << "\n+---+---+---+---+---+---+---+---+\n";
  for (Square sq = A8; sq >= H1; sq--) {
    ss << "| " << piece_to_char[pieces[sq]] << " ";
    if (sq % 8 == 0)
      ss << "| " << (sq / 8 + 1) << "\n+---+---+---+---+---+---+---+---+\n";
  }
  ss << "  a   b   c   d   e   f   g   h\n";
  return ss.str();
}

std::vector<std::string> Board::generate_moves()
{
  std::vector<std::string> moves;

  for (Square sq = H1; sq <= A8; sq++)
  {
    Piece pc = pieces[sq];

    if (pc == W_PAWN) {
      moves.push_back(move_to_uci(sq, sq + 8));
      moves.push_back(move_to_uci(sq, sq + 16));
    } else if (pc == W_KNIGHT) {
      moves.push_back(move_to_uci(sq, sq + 15));
      moves.push_back(move_to_uci(sq, sq + 17));
    } else if (pc == W_BISHOP) {
      for (Square s = sq + 9; s % 8 != 7 && pieces[s] == NO_PIECE; s += 9)
        moves.push_back(move_to_uci(sq, s));
    } else if (pc == W_QUEEN) {
      for (Square s = sq + 8; !pieces[s]; s += 8)
        moves.push_back(move_to_uci(sq, s));
    } else if (pc == W_KING) {
      if (!pieces[sq + 8])
        moves.push_back(move_to_uci(sq, sq + 8));
    }
  }

  return moves;
}
