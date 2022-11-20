#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

struct BasicToken {
  std::string value;
};

struct StringToken : public BasicToken {
  StringToken(std::string s) { value = '"' + s + '"'; }
};
struct NumToken : BasicToken {
  template <typename T> NumToken(T i) { value = std::to_string(i); }
};
struct BoolToken : BasicToken {
  BoolToken(bool b) { value = b ? "true" : "false"; }
};
struct ArrayToken : BasicToken {
  ArrayToken(std::initializer_list<BasicToken> v) {
    value = "[";
    for (std::size_t i = 1; auto s : v) {
      value.append(s.value);
      if (i != v.size()) {
        value.append(",");
        i++;
      }
    }
    value.append("]");
  }
};

struct Json {
  std::unordered_map<std::string, BasicToken> tokens;

  Json(std::unordered_map<std::string, BasicToken> j) { tokens = j; }
  std::string serialize() {
    std::string out = "{";
    for (std::size_t i = 1; const auto &elem : tokens) {
      out.append("\"" + elem.first + "\":" + elem.second.value);
      if (i != tokens.size()) {
        out.append(",");
        i++;
      }
    }
    out.append("}");
    return out;
  }
};

// int main() {
//   // std::unordered_map<std::string, BasicToken> a = {
//   //     {"int_token", NumToken(9090)},
//   //     {"str_token", StringToken("hi")},
//   //     {"bool_token", BoolToken(true)},
//   //     {"array_token", ArrayToken({NumToken(1), StringToken("ok")})}};
//   //
//   // Json json{
//   // std::unordered_map<std::string, BasicToken>{
//   //     {"int_token", NumToken(9090)},
//   //     {"str_token", StringToken("hi")},
//   //     {"bool_token", BoolToken(true)},
//   //     {"array_token", ArrayToken({NumToken(1), StringToken("ok")})}}
//   //   };
//   //
//   // std::cout << json.serialize() << std::endl;
//   std::cout << Json{std::unordered_map<std::string, BasicToken>{
//                         {"int_token", NumToken(9090)},
//                         {"str_token", StringToken("hi")},
//                         {"bool_token", BoolToken(true)},
//                         {"array_token",
//                          ArrayToken({NumToken(1), StringToken("ok")})}}}
//                    .serialize()
//             << std::endl;
// }
