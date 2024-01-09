#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <tuple>
#include <compare>
#include <vector>
#include <algorithm>

const float ENGLISH_FREQUENCIES[26] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 
    0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 
    0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 
    0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 
    0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 
    0.00074
}; 

class CaesarText {
    std::string text;
  public:
    // Constructors
    CaesarText();
    CaesarText(std::string& text);

    // Accessors
    std::string getText() const;
    void setText(std::string text);

    // Methods
    void print() const;
    float getEntropy() const;
    std::string shiftText(int shift) const;
    std::string encryptVigenere(std::string key) const;
    void fillResults(std::vector<std::tuple<int, std::string, double>>& results) const;
};
