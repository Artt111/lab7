#include <iostream>
#include <string>
#include <sstream>

class CaesarCipher {
public:
    static std::string Encrypt(const std::string& input, int key) {
        std::string result;
        for (char c : input) {
            if (isalpha(c)) {
                char baseChar = isupper(c) ? 'A' : 'a';
                char shiftedChar = (c + key - baseChar) % 26 + baseChar;
                result += shiftedChar;
            } else {
                result += c;
            }
        }
        return result;
    }

    static std::string Decrypt(const std::string& input, int key) {
        return Encrypt(input, 26 - key);
    }
};


class RLE {
public:
    static std::string Encode(const std::string& input) {
        if (input.empty()) return "";

        std::ostringstream encoded;
        int count = 1;

        for (size_t i = 1; i < input.length(); ++i) {
            if (input[i] == input[i - 1]) {
                count++;
            } else {
                encoded << input[i - 1] << count;
                count = 1;
            }
        }

        encoded << input.back() << count;
        return encoded.str();
    }

    static std::string Decode(const std::string& encoded) {
        if (encoded.empty()) return "";

        std::ostringstream decoded;
        for (size_t i = 0; i < encoded.length(); ++i) {
            char symbol = encoded[i];
            std::string countStr;
            while (isdigit(encoded[++i]) && i < encoded.length()) {
                countStr += encoded[i];
            }
            --i; 

            int count = std::stoi(countStr);
            decoded << std::string(count, symbol);
        }

        return decoded.str();
    }
};


int main() {
    std::string text;
    int key;


    std::cout << "Input text: ";
    std::getline(std::cin, text);

    std::cout << "Input Key: ";
    std::cin >> key;

  
    std::string encryptedText = CaesarCipher::Encrypt(text, key);
    std::cout << "Encrypted Text by Caesar: " << encryptedText << std::endl;

    std::string decryptedText = CaesarCipher::Decrypt(encryptedText, key);
    std::cout << "Decrypted text by Caesar: " << decryptedText << std::endl;

    
    std::string encoded = RLE::Encode(encryptedText);
    std::cout << "RLE Encoded Text: " << encoded << std::endl;

    std::string decoded = RLE::Decode(encoded);
    std::cout << "RLE Decoded Text: " << decoded << std::endl;

    return 0;
}
