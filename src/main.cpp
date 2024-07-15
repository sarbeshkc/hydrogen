#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

// Token type

enum TOKEN_TYPE { _return, int_lint, semi };

// Token structure

struct TOKEN {
  TOKEN_TYPE type;
  std::optional<std::string> value;
};

// Manual Tokenization of the program

std::vector<TOKEN> tokenize(std::string &str) {

  // The tokens
  std::vector<TOKEN> tokens;
  // The buffer
  std::string buf;
  for (int i = 0; i < str.length(); i++) {
    char c = str.at(i);
    if (std::isalpha(c)) {
      buf.push_back(c);
      i++;
      while (std::isalnum(str.at(i))) {
        buf.push_back(str.at(i));
        i++;
      }
      i--;
      if (buf == "mugi") {
        tokens.push_back({.type = TOKEN_TYPE::_return});
        buf.clear();
        continue;
      } else {
        std::cout << "You messed up no, reutrn " << std::endl;
      }
    } else if (std::isdigit(c)) {
      buf.push_back(c);
      i++;
      while (std::isdigit(str.at(i))) {
        buf.push_back(str.at(i));
        i++;
      }
      i--;
      tokens.push_back({.type = TOKEN_TYPE::int_lint, .value = buf});
      buf.clear();
    } else if (c == ';') {
      tokens.push_back({.type = TOKEN_TYPE::semi});
    } else if (std::isspace(c)) {
      continue;
    } else {
      std::cerr << "Messed up" << std::endl;
    }
  }
  std::cout << buf << std::endl;
  return tokens;
}

std::string token_to_asm(std::vector<TOKEN> &assembly) {
  std::stringstream output;
  output << "_global_start\nstart:\n";
  for (int i = 0; i < assembly.size(); i++) {
    const TOKEN &token = assembly.at(i);
    if (token.type == TOKEN_TYPE::_return) {
      if (i + 1 < assembly.size() &&
          assembly.at(i + 1).type == TOKEN_TYPE::int_lint) {
        if (i + 2 < assembly.size() &&
            assembly.at(i + 2).type == TOKEN_TYPE::semi) {
          output << "   mov rax, 60\n";
          output << "   mov rdi, " << assembly.at(i + 1).value.value() << "\n";
          output << "   syscall";
        }
      }
    }
  }
  return output.str();
}

int main(int argc, char *argv[]) {
  std::string contents;
  std::stringstream content_stream;
  if (argc != 2) {
    std::cout << "Pass two argument " << std::endl;
  } else {
    {
      std::fstream Input(argv[1], std::ios::in);
      content_stream << Input.rdbuf();
    }
  }
  contents = content_stream.str();
  std::vector<TOKEN> thing = tokenize(contents);

  {
    std::fstream file("../out.asm", std::ios::out);
    file << token_to_asm(thing);
  }
  int nasm_result = system("nasm -f elf64 ../out.asm -o out.o");
  if (nasm_result != 0) {
    std::cerr << "NASM failed to assemble the file." << std::endl;
    return EXIT_FAILURE;
  }

  int ld_result = system("ld -o out out.o");
  if (ld_result != 0) {
    std::cerr << "Linker failed to link the object file." << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_FAILURE;
}
