#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <filesystem>
#include "caesar.h"

extern const float ENGLISH_FREQUENCIES[26];

enum class ConversionType { Caesar, Vigenere, Decrypt };

void printHelp() {
    std::cout << "Caesar Cipher (C++)\n";
    std::cout << "Usage:\n";
    std::cout << "    caesar\n";
    std::cout << "    caesar <-h/-help/h/help>"
    std::cout << "    caesar -f <filename> <conversion> <key/all>\n";
    std::cout << "\n";
    std::cout << "    If no argument is given, the program will prompt the user for text.\n";
    std::cout << "    If the flag -f and a file name is given, the program will read the text from the file.\n";
    std::cout << "\n";
    std::cout << "    To output the help message, provide either '-h', '-help', 'h', 'help' as a flag.\n";
    std::cout << "\n";
    std::cout << "    The conversion argument can be:\n";
    std::cout << "        for Caesar encryption: '-c' '-caesar' 'c' 'caesar'\n";
    std::cout << "        for Vigenere encryption: '-v' '-vigenere' 'v' 'vigenere'\n";
    std::cout << "        for Caesar decryption: '-d' '-decrypt' 'd' 'decrypt'\n";
    std::cout << "\n";
    std::cout << "    For Caesar encryption, the key must be an integer.\n";
    std::cout << "    For Vigenere encryption, the key must be a string of alphabetic characters.\n";
    std::cout << "\n";
    std::cout << "    For Caesar decryption, to show all results provide either '-a', '-all', 'a' or 'all' as a flag. \n";
    std::cout << "    Otherwise, to not show all results, do not provide any flags.\n";
    std::cout << "\n";
    std::cout << "    The program will then carry out the conversion and output the result." << std::endl;
}    

void displayResults(const std::vector<std::tuple<int, std::string, double>>& results, bool all) {
    std::cout << std::setw(10) << "Key" << std::setw(15) << "Decrypted Text" << std::setw(15) << "Entropy" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    size_t limit = all ? results.size() : std::min(results.size(), static_cast<size_t>(3));
    for (size_t i = 0; i < limit; ++i) {
        std::cout << std::setw(10) << std::get<0>(results[i]) << std::setw(15) << std::get<1>(results[i]) << std::setw(15) << std::get<2>(results[i]) << std::endl;
    }
}

bool isConvertibleToInt(const std::string& str) {
    std::istringstream iss(str);
    int value;
    iss >> value;
    return !iss.fail() && iss.eof();
}

bool isAlphabet(const std::string& str) {
    return std::all_of(str.begin(), str.end(), [](char c) { return std::isalpha(c); });
}

ConversionType getConversionType(const std::string& conversion) {
    if (conversion == "-c" || conversion == "-caesar" || conversion == "c" || conversion == "caesar") {
        return ConversionType::Caesar;
    } else if (conversion == "-v" || conversion == "-vigenere" || conversion == "v" || conversion == "vigenere") {
        return ConversionType::Vigenere;
    } else if (conversion == "-d" || conversion == "-decrypt" || conversion == "d" || conversion == "decrypt") {
        return ConversionType::Decrypt;
    } else {
        throw std::invalid_argument("Invalid conversion type:" + conversion);
    }
}

int main(int argc, char** argv) {
    std::string flag, filename, conversion, key, text;
    CaesarText ct;
    try {
        if (argc == 5) {
            flag = argv[1];
            filename = argv[2];
            conversion = argv[3];
            key = argv[4];
            if (!(flag == "-f" || flag == "-file" || flag == "f" || flag == "file")) {
                throw std::invalid_argument("Invalid flag:" + flag);
            }
            if (!std::filesystem::exists(filename)) {
                throw std::invalid_argument("Invalid file:" + filename);
            }
            std::ifstream file_stream(filename);
            std::string file_contents((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
            ct.setText(file_contents);
            std::cout << "Original text: " << file_contents << std::endl;
            ConversionType type = getConversionType(conversion);
            switch (type) {
                case ConversionType::Caesar: 
                    if (!isConvertibleToInt(key)) {
                        throw std::invalid_argument("Invalid key:" + key);
                    }
                    std::cout << "Key: " << key << std::endl;
                    std::cout << "Encrypted text: " << ct.shiftText(std::stoi(key)) << std::endl;
                    break;
                case ConversionType::Vigenere:
                    if (!isAlphabet(key)) {
                        throw std::invalid_argument("Invalid key:" + key);
                    }
                    std::cout << "Key: " << key << std::endl;
                    std::cout << "Encrypted text: " << ct.encryptVigenere(key) << std::endl;
                    break;
                case ConversionType::Decrypt:
                    if (key != "-a" || key != "-all" || key != "a" || key != "all") {
                        throw std::invalid_argument("Invalid flag: " + key);
                    }
                    std::vector<std::tuple<int, std::string, double>> results;
                    ct.fillResults(results);
                    displayResults(results, true);
                    break;
            }
        } else if (argc == 4) {
            flag = argv[1];
            filename = argv[2];
            conversion = argv[3];
            if (!(flag == "-f" || flag == "-file" || flag == "f" || flag == "file")) {
                throw std::invalid_argument("Invalid flag:" + flag);
            }
            if (!std::filesystem::exists(filename)) {
                throw std::invalid_argument("Invalid file:" + filename);
            }
            std::ifstream file_stream(filename);
            std::string file_contents((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
            ct.setText(file_contents);
            std::cout << "Original text: " << file_contents << std::endl;
            ConversionType type = getConversionType(conversion);
            if (type != ConversionType::Decrypt) {
                throw std::invalid_argument("Invalid arguments count.");
            }
            std::vector<std::tuple<int, std::string, double>> results;
            ct.fillResults(results);
            displayResults(results, false);
        } else if (argc == 2) {
            flag = argv[1];
            if (!(flag == "-h" || flag == "-help" || flag == "h" || flag == "help")) {
                throw std::invalid_argument("Invalid flag:" + flag);
            } else {
                printHelp();
            }
        } else if (argc == 1) {
            while (true) {
                std::cout << "Enter text: " << std::endl;
                std::getline(std::cin, text);
                ct.setText(text);
                std::cout << "Original text: " << text << std::endl;
                std::cout << "Select conversion type (Caesar encryption, Vigenere encryption, Caesar decryption): " << std::endl;
                std::cin >> conversion;
                ConversionType type = getConversionType(conversion);
                switch (type) {
                    case ConversionType::Caesar:
                        std::cout << "Enter key: " << std::endl;
                        std::cin >> key;
                        if (!isConvertibleToInt(key)) {
                            throw std::invalid_argument("Invalid key:" + key);
                        }
                        std::cout << "Key: " << key << std::endl;
                        std::cout << "Encrypted text: " << ct.shiftText(std::stoi(key)) << std::endl;
                        break;
                    case ConversionType::Vigenere:
                        std::cout << "Enter key: " << std::endl;
                        std::cin >> key;
                        if (!isAlphabet(key)) {
                            throw std::invalid_argument("Invalid key:" + key);
                        }
                        std::cout << "Key: " << key << std::endl;
                        std::cout << "Encrypted text: " << ct.encryptVigenere(key) << std::endl;
                        break;
                    case ConversionType::Decrypt:
                        std::cout << "Show all results? (y/n)" << std::endl;
                        std::string flag;
                        std::cin >> flag;
                        if (flag == "y" || flag == "yes") {
                            std::vector<std::tuple<int, std::string, double>> results;
                            ct.fillResults(results);
                            displayResults(results, true);
                        } else if (flag == "n" || flag == "no") {
                            std::vector<std::tuple<int, std::string, double>> results;
                            ct.fillResults(results);
                            displayResults(results, false);
                        } else {
                            throw std::invalid_argument("Invalid flag: " + flag);
                        }
                        break;
                }
            }
        } else {
            throw std::invalid_argument("Invalid arguments count.");
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
