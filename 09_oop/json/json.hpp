#ifndef JSON_HPP
#define JSON_HPP

#include <iostream>
#include <string>
#include <unordered_map>

struct IJsonToken {
  std::string value;
};

struct JsonString : public IJsonToken {
  JsonString(std::string s) { value = '"' + s + '"'; }
};

struct JsonNumber : IJsonToken {
  template <typename T> JsonNumber(T i) { value = std::to_string(i); }
};

struct JsonBool : IJsonToken {
  JsonBool(bool b) { value = b ? "true" : "false"; }
};

struct JsonArray : IJsonToken {
  JsonArray(std::initializer_list<IJsonToken> v) {
    value = "[";
    for (std::size_t i = 1; auto s : v) {
      value.append(s.value);
      // i hate it
      if (i != v.size()) {
        value.append(",");
        i++;
      }
    }
    value.append("]");
  }
};

struct Json {
  std::unordered_map<std::string, IJsonToken> tokens = {};

  Json(std::initializer_list<std::pair<std::string, IJsonToken>> il) {
    for (auto it : il)
      tokens.insert_or_assign(it.first, it.second);
  }

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

#endif
