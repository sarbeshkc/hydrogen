// #include "tokenizer.h"
// #include <cctype>
// #include <cstdlib>
// #include <vector>

// std::optional<char> Tokenizer::peek(int ahead = 1) {
//   if (m_index + ahead < m_src.length()) {
//     return m_src.at(m_index + ahead);
//   } else {
//     return {};
//   }
// }

// char Tokenizer::consume() { return m_src.at(m_index++); }

// std::vector<TOKEN> Tokenizer::tokenizer() {
//   std::vector<TOKEN> tokens;
//   std::string buf;
//   while (peek().has_value()) {
//     if (std::isalpha(peek().value())) {
//       buf.push_back(consume());
//       while (peek().has_value() && std::isalnum(peek().value())) {
//         buf.push_back(consume());
//       }
//       if (buf == "exit") {
//         tokens.push_back({.type = TOKEN_TYPE::_exit});
//         buf.clear();
//         break;
//       } else {
//         std::cerr << "You messed up " << std::endl;
//         exit(EXIT_FAILURE);
//       }
//     } else if (std::isdigit(peek().value())) {
//       buf.push_back(consume());
//       while (peek().has_value() && std::isdigit(peek().value())) {
//         buf.push_back(consume());
//       }
//       tokens.push_back({.type = TOKEN_TYPE::int_lint, .value = buf});
//       buf.clear();
//     } else if (peek().value() == ';') {
//       consume();
//       tokens.push_back({.type = TOKEN_TYPE::semi});
//     } else if (std::isspace(peek().value())) {
//       consume();
//     } else {
//       std::cerr << "Error occurred" << std::endl;
//       exit(EXIT_FAILURE);
//     }
//   }
//   return tokens;
// }
