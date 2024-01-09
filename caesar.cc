#include "caesar.h"

int letterToIndex(char letter) {
    // Returns the index of a letter in the alphabet
    if (letter >= 'a' && letter <= 'z') {
        return static_cast<int>(letter - 'a');
    } else if (letter >= 'A' && letter <= 'Z') {
        return static_cast<int>(letter - 'A');
    } else {
        return -1;
    }
}

// Constructors
CaesarText::CaesarText(): text{""} {}
CaesarText::CaesarText(std::string& text): text{text} {}

// Accessors
std::string CaesarText::getText() const {
    return this->text;
}
void CaesarText::setText(std::string text) {
    this->text = text;
}

// Methods
void CaesarText::print() const {
    std::cout << this->text << std::endl;
}
float CaesarText::getEntropy() const {
    // Returns the entropy of the text
    float sum = 0;
    int ignored = 0;
    for (char letter: this->text) {
        if (letterToIndex(letter) != -1) {
            sum += std::log(ENGLISH_FREQUENCIES[letterToIndex(letter)]);
        } else {
            ++ignored;
        }
    }
    return - sum / std::log(2) / (this->text.length() - ignored);
}
std::string CaesarText::shiftText(int shift) const {
    // Shifts the text by a given amount
    std::string newText = "";
    for (char letter: this->text) {
        if ('A' <= letter && letter <= 'Z') {
            newText += static_cast<char>((letter - 'A' + shift) % 26 + 'A');
        } else if ('a' <= letter && letter <= 'z') {
            newText += static_cast<char>((letter - 'a' + shift) % 26 + 'a');
        } else {
            newText += letter;
        }
    }
    return newText;
}
std::vector<int> generateKey(std::string text) {
    // Generates a key for the Vigenere cipher
    std::vector<int> key;
    for (char letter: text) {
        if ('A' <= letter && letter <= 'Z') {
            key.push_back(letter - 'A');
        } else if ('a' <= letter && letter <= 'z') {
            key.push_back(letter - 'a');
        }
    }
    return key;
}
std::string CaesarText::encryptVigenere(std::string key) const {
    // Encrypts the text using the Vigenere cipher
    std::string newText = "";
    std::vector<int> keyVector = generateKey(key);
    int i = 0;
    for (char letter: this->text) {
        if ('A' <= letter && letter <= 'Z') {
            newText += static_cast<char>((letter - 'A' + keyVector[i % key.length()]) % 26 + 'A');
            ++i;
        } else if ('a' <= letter && letter <= 'z') {
            newText += static_cast<char>((letter - 'a' + keyVector[i % key.length()]) % 26 + 'a');
            ++i;
        } else {
            newText += letter;
        }
    }
    return newText;
}
void CaesarText::fillResults(std::vector<std::tuple<int, std::string, double>>& results) const {
    // Fills the results vector with the entropy of the text shifted by 0-25
    for (int i = 0; i < 26; ++i) {
        std::string tempText = this->shiftText(i);
        results.emplace_back(i, tempText, CaesarText(tempText).getEntropy());
    }
    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        return std::get<2>(a) < std::get<2>(b);
    });
}