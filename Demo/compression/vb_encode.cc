#include <cstdint>
#include <fstream>
#include <list>
#include <iostream>
#include <vector>

void VBEncode(std::int32_t v, std::vector<std::int8_t>& out) {
  std::list<std::int8_t> bytes;
  for (;;) {
    bytes.push_front(v % 128);
    if (v < 128) {
      break;
    }
    v /= 128;
  }
  bytes.back() += 128;
  for (std::int8_t v: bytes) {
    out.push_back(v);
  }
}

int Encode(const std::string& src_name, const std::string& dest_name) {
  std::vector<std::int32_t> postings;
  {
    std::ifstream inp{src_name, std::ios::binary | std::ios::ate};
    postings.resize(inp.tellg() / sizeof(std::int32_t));
    inp.seekg(std::ios_base::beg);
    inp.read(reinterpret_cast<char*>(postings.data()), postings.size() * sizeof(std::int32_t));
  }
  std::vector<std::int8_t> vbcode;
  for (std::int32_t v: postings) {
    VBEncode(v, vbcode);
  }
  {
    std::ofstream out{dest_name, std::ios::binary};
    out.write(reinterpret_cast<char*>(vbcode.data()), vbcode.size());
  }
  return 0;
}

int Decode(const std::string& src_name, const std::string& dest_name) {
  std::vector<std::uint8_t> data;
  {
    std::ifstream inp{src_name, std::ios::binary | std::ios::ate};
    data.resize(inp.tellg());
    inp.seekg(std::ios_base::beg);
    inp.read(reinterpret_cast<char*>(data.data()), data.size());
  }
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
  {
    std::ofstream out{dest_name, std::ios::binary};
    out.write(reinterpret_cast<char*>(values.data()), values.size() * sizeof(std::int32_t));
  }
  return 0;
}

int Compare(const std::string& file_name1, const std::string& file_name2) {
  std::vector<std::int8_t> data1;
  std::vector<std::int8_t> data2;
  auto load = [] (const std::string& file_name, std::vector<std::int8_t> data) {
    std::ifstream inp{file_name, std::ios::binary | std::ios::ate};
    data.resize(inp.tellg());
    inp.seekg(std::ios_base::beg);
    inp.read(reinterpret_cast<char*>(data.data()), data.size());
  };
  load(file_name1, data1);
  load(file_name2, data2);
  if (data1.size() != data2.size()) {
    std::cout << "Different length!" << std::endl;
    return 1;
  }
  for (auto i = 0; i < data1.size(); ++i) {
    if (data1[i] != data2[i]) {
      std::cout << "Different value at " << i << std::endl;
      return 1;
    }
  }
  std::cout << "Same values." << std::endl;
  return 0;
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "Usage: ./vb [enc/dec/cmp] src_file dest_file" << std::endl;
    return 1;
  }
  if (std::string(argv[1]) == "enc") {
    return Encode(argv[2], argv[3]);
  } else if (std::string(argv[1]) == "dec") {
    return Decode(argv[2], argv[3]);
  } else {
    return Compare(argv[2], argv[3]);
  }
}