#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "json.hpp"

#include <doctest.h>

TEST_CASE("All JSON types can be serialized") {
  CHECK_EQ(Json{}.serialize(), "{}");

  CHECK_EQ(Json{{"str_token", JsonString("val")}}.serialize(),
           "{\"str_token\":\"val\"}");

  CHECK_EQ(Json{{"int_token", JsonNumber(999999)}}.serialize(),
           "{\"int_token\":999999}");

  CHECK_EQ(Json{{"bool_token", JsonBool(true)}}.serialize(),
           "{\"bool_token\":true}");

  CHECK_EQ(Json{{"array_token", JsonArray({JsonNumber(1), JsonString("ok")})}}
               .serialize(),
           "{\"array_token\":[1,\"ok\"]}");
}

TEST_CASE("Duplicates update values") {
  CHECK_EQ(Json{{"a", JsonNumber(999999)}, {"a", JsonNumber(0)}}.serialize(),
           "{\"a\":0}");
}