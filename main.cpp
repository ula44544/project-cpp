#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Шифрование 
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

// Расшифровка
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
        cout << "\n=== МЕНЮ ===\n";
        cout << "1. Зашифровать сообщение\n";
        cout << "2. Расшифровать сообщение\n";
        cout << "3. Выход\n";
        cout << "Выбор: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 3) {
            cout << "Работа завершена.\n";
            break;
        }

        if (choice == 1) {
            string message;
            cout << "Введите сообщение: ";
            getline(cin, message);

            int keyCount;
            cout << "Количество ключей: ";
            cin >> keyCount;
            cin.ignore();

            vector<string> keys(keyCount);
            for (int i = 0; i < keyCount; ++i) {
                cout << "Введите ключ " << i + 1 << ": ";
                getline(cin, keys[i]);
            }

            string encrypted = message;
            for (const auto& key : keys) {
                encrypted = vigenereEncrypt(encrypted, key);
            }

            string filePath;
            cout << "Введите путь к файлу для записи: ";
            getline(cin, filePath);

            ofstream out(filePath, ios::binary);
            out.write(encrypted.data(), encrypted.size());
            out.close();

            cout << "Сообщение успешно зашифровано и сохранено.\n";
        }

        else if (choice == 2) {
            string filePath;
            cout << "Введите путь к файлу: ";
            getline(cin, filePath);

            ifstream in(filePath, ios::binary);
            if (!in) {
                cout << "Ошибка открытия файла.\n";
                continue;
            }

            string encrypted(
                (istreambuf_iterator<char>(in)),
                istreambuf_iterator<char>()
            );
            in.close();

            int keyCount;
            cout << "Количество ключей: ";
            cin >> keyCount;
            cin.ignore();

            vector<string> keys(keyCount);
            for (int i = 0; i < keyCount; ++i) {
                cout << "Введите ключ " << i + 1 << ": ";
                getline(cin, keys[i]);
            }

            // Расшифровка в обратном порядке
            string decrypted = encrypted;
            for (int i = keyCount - 1; i >= 0; --i) {
                decrypted = vigenereDecrypt(decrypted, keys[i]);
            }

            cout << "\nИсходное сообщение:\n";
            cout << decrypted << endl;
        }

        else {
            cout << "Неверный пункт меню.\n";
        }
    }

    return 0;
}
