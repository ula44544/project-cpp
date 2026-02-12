#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Øèôðîâàíèå 
string vigenereEncrypt(const string& text, const string& key) {
    string result = text;
    for (size_t i = 0; i < text.size(); ++i) {
        result[i] = static_cast<unsigned char>(
            (static_cast<unsigned char>(text[i]) +
                static_cast<unsigned char>(key[i % key.size()])) % 256
            );
    }
    return result;
}

// Ðàñøèôðîâêà
string vigenereDecrypt(const string& text, const string& key) {
    string result = text;
    for (size_t i = 0; i < text.size(); ++i) {
        result[i] = static_cast<unsigned char>(
            (static_cast<unsigned char>(text[i]) -
                static_cast<unsigned char>(key[i % key.size()]) + 256) % 256
            );
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "");

    while (true) {
        cout << "\n=== ÌÅÍÞ ===\n";
        cout << "1. Çàøèôðîâàòü ñîîáùåíèå\n";
        cout << "2. Ðàñøèôðîâàòü ñîîáùåíèå\n";
        cout << "3. Âûõîä\n";
        cout << "Âûáîð: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 3) {
            cout << "Ðàáîòà çàâåðøåíà.\n";
            break;
        }

        if (choice == 1) {
            string message;
            cout << "Ââåäèòå ñîîáùåíèå: ";
            getline(cin, message);

            int keyCount;
            cout << "Êîëè÷åñòâî êëþ÷åé: ";
            cin >> keyCount;
            cin.ignore();

            vector<string> keys(keyCount);
            for (int i = 0; i < keyCount; ++i) {
                cout << "Ââåäèòå êëþ÷ " << i + 1 << ": ";
                getline(cin, keys[i]);
            }

            string encrypted = message;
            for (const auto& key : keys) {
                encrypted = vigenereEncrypt(encrypted, key);
            }

            string filePath;
            cout << "Ââåäèòå ïóòü ê ôàéëó äëÿ çàïèñè: ";
            getline(cin, filePath);

            ofstream out(filePath, ios::binary);
            out.write(encrypted.data(), encrypted.size());
            out.close();

            cout << "Ñîîáùåíèå óñïåøíî çàøèôðîâàíî è ñîõðàíåíî.\n";
        }

        else if (choice == 2) {
            string filePath;
            cout << "Ââåäèòå ïóòü ê ôàéëó: ";
            getline(cin, filePath);

            ifstream in(filePath, ios::binary);
            if (!in) {
                cout << "Îøèáêà îòêðûòèÿ ôàéëà.\n";
                continue;
            }

            string encrypted(
                (istreambuf_iterator<char>(in)),
                istreambuf_iterator<char>()
            );
            in.close();

            int keyCount;
            cout << "Êîëè÷åñòâî êëþ÷åé: ";
            cin >> keyCount;
            cin.ignore();

            vector<string> keys(keyCount);
            for (int i = 0; i < keyCount; ++i) {
                cout << "Ââåäèòå êëþ÷ " << i + 1 << ": ";
                getline(cin, keys[i]);
            }

            // Ðàñøèôðîâêà â îáðàòíîì ïîðÿäêå
            string decrypted = encrypted;
            for (int i = keyCount - 1; i >= 0; --i) {
                decrypted = vigenereDecrypt(decrypted, keys[i]);
            }

            cout << "\nÈñõîäíîå ñîîáùåíèå:\n";
            cout << decrypted << endl;
        }

        else {
            cout << "Íåâåðíûé ïóíêò ìåíþ.\n";
        }
    }

    return 0;
}
