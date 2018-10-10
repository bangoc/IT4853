#include <cstring>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  {
    std::cout << "Option 1" << std::endl;
    char s1[] = "automata";
    char s2[] = "automate";
    char s3[] = "automatic";
    char s4[] = "automation";
    std::cout << s1 << std::endl
              << s2 << std::endl
              << s3 << std::endl
              << s4 << std::endl;
  }
  {
    char s[] = "\x08" "automata" "\x08" "automate" "\x09" "automatic" "\x0A" "automation";
    std::cout << "Option 2" << std::endl;
    int p = 1;
    for (int i = 0; i < 4; ++i) {
      std::string::size_type len = static_cast<std::string::size_type>(s[p - 1]);
      std::cout << std::string{s + p, len} << std::endl;
      p += len + 1;
    }
  }
  {
    std::cout << "Option 3" << std::endl;
    char s[] = "\x08\x07" "automata" "\x01" "e" "\x02" "ic" "\x03" "ion";
    int p = 2 + s[0] + 1;
    std::string front{s + 2, static_cast<std::string::size_type>(s[1])};
    std::cout << std::string{s + 2, static_cast<std::string::size_type>(s[0])} << std::endl;
    for (int i = 0; i < 3; ++i) {
      std::string::size_type len = static_cast<std::string::size_type>(s[p - 1]);
      std::cout << front << std::string{s + p, len} << std::endl;
      p += len + 1;
    }
  }
}