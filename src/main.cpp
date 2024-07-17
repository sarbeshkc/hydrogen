#include "tokenizer.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

// Manual Tokenization of the program

std::string token_to_asm(std::vector<TOKEN> &assembly) {
  std::stringstream output;
  output << "_global_start\nstart:\n";
  for (int i = 0; i < assembly.size(); i++) {
    const TOKEN &token = assembly.at(i);
    if (token.type == TOKEN_TYPE::_exit) {
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
  std::vector<TOKEN> tokens;
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

  Tokenizer gettingtokens(contents);
  std::vector<TOKEN> token = gettingtokens.tokenizer();
  std::string assembly_code = token_to_asm(token);
  //
  //
  // The linking and other phase
  //
  //
  {
    std::fstream file("../out.asm", std::ios::out);
    file << assembly_code;
  }
  // { std::fstream file("../out.asm", std::ios::out); }
  // int nasm_result = system("nasm -f elf64 ../out.asm -o out.o");
  // if (nasm_result != 0) {
  //   std::cerr << "NASM failed to assemble the file." << std::endl;
  //   return EXIT_FAILURE;
  // }

  // int ld_result = system("ld -o out out.o");
  // if (ld_result != 0) {
  //   std::cerr << "Linker failed to link the object file." << std::endl;
  //   return EXIT_FAILURE;
  // }
  return EXIT_FAILURE;
}
