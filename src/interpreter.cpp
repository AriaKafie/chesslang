
#include "interpreter.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

std::string trim(const std::string& str);
Square uci_to_square(const std::string& uci);

VarMap varmap;

void Interpreter::parse(const std::string& path)
{
  std::ifstream program(path);
  std::string   line;

  while (std::getline(program, line))
  {
    std::istringstream is(line);

    if (std::regex_search(line, std::regex("^\\s*Board\\s+"))) {
      std::string board_name = trim(line.substr(line.find("Board") + 5, line.substr(line.find("Board") + 5).find("(")));
      std::string fen = line.substr(line.find("(") + 1, line.substr(line.find("(") + 1).find(")"));
      if (fen == "startpos")
        fen = STARTPOS;

      varmap[board_name] = Board(fen);

    } else if (std::regex_search(line, std::regex("^\\s*print\\(.*\\)"))) {
      std::string board_name = trim(line.substr(line.find("(") + 1, line.substr(line.find("(") + 1).find(")")));

      std::cout << varmap[board_name].to_string();

    } else if (std::regex_search(line, std::regex("\\.set\\(.*\\)"))) {
      std::string board_name = trim(line.substr(0, line.find(".")));
      std::string fen = line.substr(line.find("(") + 1, line.substr(line.find("(") + 1).find(")"));
      if (fen == "startpos")
        fen = STARTPOS;

      varmap[board_name].set(fen);

    } else if (std::regex_search(line, std::regex("\\.make_move"))) {
      std::string board_name = trim(line.substr(0, line.find(".")));

      std::vector<std::string> moves;
      std::string token;
      char c;
      std::istringstream is(trim(line.substr(line.find("(") + 1, line.substr(line.find("(") + 1).find(")"))));
      is >> std::skipws;

      while (is >> c) {
        if (c == ',') {
          moves.push_back(trim(token));
          token = "";
          continue;
        }
        token += c;
      }
      moves.push_back(token);

      for (const auto& move : moves)
        varmap[board_name].make_move(uci_to_square(move.substr(0, 2)), uci_to_square(move.substr(2, 2)));
    } else if (std::regex_search(line, std::regex("^\\s*for\\s*\\(.*\\)"))) {
      std::string board_name = trim(line.substr(line.find(":") + 1, line.substr(line.find(":") + 1).find(".moves")));
      for (const std::string& m : varmap[board_name].generate_moves())
        std::cout << m << "\n";

      std::getline(program, line);
    }
  }
}

Square uci_to_square(const std::string& uci) {
  return 8 * (uci[1] - '1') + 'h' - uci[0];
}

std::string trim(const std::string& str) {
  return str.substr(str.find_first_not_of(" \n\r\t"), str.substr(str.find_first_not_of(" \n\r\t")).find_last_not_of(" \n\r\t") + 1);
}
