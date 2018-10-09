#include "file_utilities.h"

#include <cstdint>
#include <list>
#include <iostream>
#include <vector>

void VBEncode(std::int32_t v, std::vector<std::uint8_t>& out) {
  std::list<std::uint8_t> bytes;
  for (;;) {
    bytes.push_front(v % 128);
    if (v < 128) {
      break;
    }
    v /= 128;
  }
  bytes.back() += 128;
  for (std::uint8_t v: bytes) {
    out.push_back(v);
  }
}

int Encode(const std::string& src_name, const std::string& dest_name) {
  std::vector<std::int32_t> postings;
  LoadFile(src_name, postings);
  std::vector<std::uint8_t> vbcode;
  for (std::int32_t v: postings) {
    VBEncode(v, vbcode);
  }
  SaveToFile(dest_name, vbcode);
  return 0;
}

int EncodeGap(const std::string& src_name, const std::string& dest_name) {
  std::vector<std::int32_t> postings;
  LoadFile(src_name, postings);
  std::vector<std::uint8_t> vbcode;
  VBEncode(postings[0], vbcode);
  for (auto i = 1; i < postings.size(); ++i) {
    VBEncode(postings[i] - postings[i - 1], vbcode);
  }
  SaveToFile(dest_name, vbcode);
  return 0;
}

int Decode(const std::string& src_name, const std::string& dest_name) {
  std::vector<std::uint8_t> data;
  LoadFile(src_name, data);
  std::vector<std::int32_t> values;
  std::int32_t v = 0;
  for (std::uint8_t b: data) {
    if (b < 128) {
      v = v * 128 + b;
    } else {
      v = 128 * v + (b -128);
      values.push_back(v);
      v = 0;
    }
  }
  SaveToFile(dest_name, values);
  return 0;
}

int DecodeGap(const std::string& src_name, const std::string& dest_name) {
  std::vector<std::uint8_t> data;
  LoadFile(src_name, data);
  std::vector<std::int32_t> values;
  std::int32_t v = 0;
  bool first = true;
  for (std::uint8_t b: data) {
    if (b < 128) {
      v = v * 128 + b;
    } else {
      v = 128 * v + (b -128);
      if (first) {
        values.push_back(v);
        first = false;
      } else {
        values.push_back(values[values.size() - 1] + v);
      }
      v = 0;
    }
  }
  SaveToFile(dest_name, values);
  return 0;
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "Usage: ./vb [enc/dec/encg/decg/cmp] src_file dest_file" << std::endl;
    return 1;
  }
  if (std::string(argv[1]) == "enc") {
    return Encode(argv[2], argv[3]);
  } else if (std::string(argv[1]) == "encg") {
    return EncodeGap(argv[2], argv[3]);
  } else if (std::string(argv[1]) == "dec") {
    return Decode(argv[2], argv[3]);
  } else if (std::string(argv[1]) == "decg") {
    return DecodeGap(argv[2], argv[3]);
  } else {
    return Compare(argv[2], argv[3]);
  }
}