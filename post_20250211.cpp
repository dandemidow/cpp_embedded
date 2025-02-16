#include <iostream>

#include "nlohmann/json.hpp"

struct MegaJson {
  MegaJson() = default;
  MegaJson(int) { std::cout<<__PRETTY_FUNCTION__<<std::endl;}
  MegaJson(MegaJson const &o) {std::cout <<__PRETTY_FUNCTION__<<std::endl; }
  MegaJson(std::initializer_list<int>) {
    std::cout<<__PRETTY_FUNCTION__<<std::endl;
  }
  MegaJson(std::initializer_list<std::reference_wrapper<MegaJson>>) {
    std::cout<<__PRETTY_FUNCTION__<<std::endl;
  }
};


int main() {
    auto text = R"(
  {
    "pi": 3.141,
    "happy": true
  }
)";
    nlohmann::json ex1 = nlohmann::json::parse(text);
    nlohmann::json ex2 {nlohmann::json::parse(text)};
    auto const ex3 = nlohmann::json::parse(text);

    std::cout << ex1 <<std::endl;
    std::cout << ex2 <<std::endl;
    std::cout << ex3 <<std::endl;
    
    MegaJson j1 (1);
    MegaJson j2 {j1};
    MegaJson j3 (j1);

}