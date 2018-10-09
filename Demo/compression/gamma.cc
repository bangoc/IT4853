#include "file_utilities.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class BitVector {
 public:
  // all bits default to 1
  void AddBit(bool value) {
    if (!value) {
      data_[current_byte_] &= (~b_[current_bit_]);
    }
    Advance();
    if (Eof()) {
      data_.push_back(255);
    }
  }
  void Advance() {
    ++current_bit_;
    if (current_bit_ >= 8) {
      current_bit_ = 0;
      ++current_byte_;
    }
  }
  bool ReadBit() {
    bool value = (data_[current_byte_] & b_[current_bit_]) > 0;
    Advance();
    return value;
  }
  bool Eof() {
    return current_byte_ >= data_.size();
  }
  void Seek() {
    current_byte_ = 0;
    current_bit_ = 0;
  }
  std::vector<std::uint8_t>& data() {
    return data_;
  }
 private:
  std::int32_t current_byte_ = 0;
  std::uint8_t current_bit_ = 0;
  std::vector<std::uint8_t> data_{255};
  std::vector<std::uint8_t> b_
    {1 << 7, 1 << 6, 1 << 5, 1 << 4, 1 << 3, 1 << 2, 1 << 1, 1};
};

std::ostream& operator<<(std::ostream& stream, BitVector& data) {
  data.Seek();
  std::int32_t cc = 0;
  while (!data.Eof()) {
    if (data.ReadBit()) {
      ++cc;
    } else {
      for (std::int32_t i = 0; i < cc; ++i) {
        stream << 1;
      }
      stream << 0;
      for (std::int32_t i = 0; i < cc; ++i) {
        stream << data.ReadBit();
      }
      cc = 0;
    }
  }
  return stream;
}

int Encode(std::int32_t n, BitVector& out) {
  std::vector<bool> code;
  while (n > 1) {
    code.push_back((n % 2) > 0);
    n /= 2;
  }
  auto len = code.size();
  code.push_back(0);
  for (auto i = 0; i < len; ++i) {
    code.push_back(1);
  }
  for (std::int32_t i = code.size() - 1; i >= 0; --i) {
    out.AddBit(code[i]);
  }
  return 0;
}

int Encode(const std::string& src_file, const std::string& dst_file) {
  std::vector<std::int32_t> postings;
  LoadFile(src_file, postings);
  // std::cout << "Postings size: " << postings.size() << std::endl;
  BitVector out;
  Encode(postings[0], out);
  for (std::int32_t i = 1; i < postings.size(); ++i) {
    Encode(postings[i] - postings[i - 1], out);
  }
  // std::cout << "Encode size: " << out.data().size() << std::endl;
  SaveToFile(dst_file, out.data());
  return 0;
}

int Decode(const std::string& src_file, const std::string& dst_file) {
  BitVector data;
  LoadFile(src_file, data.data());
  data.Seek();
  std::vector<std::int32_t> postings;
  bool first = true;
  std::int32_t cc = 0;
  while (!data.Eof()) {
    if (data.ReadBit()) {
      ++cc;
    } else {
      std::int32_t v = 1;
      for (int i = 0; i < cc; ++i) {
        v = v << 1;
        if (data.ReadBit()) {
          ++v;
        }
      }
      cc = 0;
      if (first) {
        postings.push_back(v);
        first = false;
      } else {
        postings.push_back(postings[postings.size() - 1] + v);
      }
    }
  }
  SaveToFile(dst_file, postings);
}

int TestEnc(const std::string& data) {
  std::stringstream ss{data};
  std::int32_t v1, v2;
  bool first = true;
  BitVector out;
  while (ss >> v2) {
    if (first) {
      Encode(v2, out);
      first = false;
    } else {
      Encode(v2 - v1, out);
    }
    v1 = v2;
  }
  std::cout << "gamma(" << data << ") = " << out << std::endl;
  return 1;
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "Usage: ./gamma [enc/dec/cmp] src_file dst_file" << std::endl;
    std::cout << "or ./gamma test enc 123" << std::endl;
    return 1;
  }
  if (std::string(argv[1]) == "enc") {
    return Encode(argv[2], argv[3]);
  } else if (std::string(argv[1]) == "dec") {
    return Decode(argv[2], argv[3]);
  } else if (std::string(argv[1]) == "test" && std::string(argv[2]) == "enc") {
    return TestEnc(argv[3]);
  } else {
    return Compare(argv[2], argv[3]);
  }
  return 0;
}