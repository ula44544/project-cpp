#include <iostream>   // библиотека для ввода и вывода (cin, cout)
#include <fstream>    // библиотека для работы с файлами
#include <vector>     // динамический массив vector
#include <string>     // работа со строками

using namespace std;  // позволяет писать cout, string без std::

// shbifrovka 
// функция шифрования по принципу шифра Виженера
string vigenereEncrypt(const string& text, const string& key) {
    string result = text; // создаем копию текста для хранения результата

    // цикл проходит по каждому символу текста
    for (size_t i = 0; i < text.size(); ++i) {

        // складываем ASCII-код символа текста и символа ключа
        // i % key.size() делает повтор ключа если текст длиннее
        // %256 оставляет результат в диапазоне одного байта
        result[i] = static_cast<unsigned char>(
            (static_cast<unsigned char>(text[i]) +
                static_cast<unsigned char>(key[i % key.size()])) % 256
            );
    }

    return result; // возвращаем зашифрованную строку
}

// rashifrovka
// функция расшифровки (обратная операция)
string vigenereDecrypt(const string& text, const string& key) {
    string result = text; // копия текста

    // цикл по каждому символу
    for (size_t i = 0; i < text.size(); ++i) {

        // вычитаем ASCII-код символа ключа
        // +256 добавляется чтобы избежать отрицательного числа
        result[i] = static_cast<unsigned char>(
            (static_cast<unsigned char>(text[i]) -
                static_cast<unsigned char>(key[i % key.size()]) + 256) % 256
            );
    }

    return result; // возвращаем расшифрованную строку
}

int main() {
    setlocale(LC_ALL, ""); // позволяет корректно работать с русским текстом

    while (true) { // бесконечный цикл меню
        cout << "\n=== МЕНЮ ===\n";
        cout << "1. Зашифровать сообщение\n";
        cout << "2. Расшифровать сообщение\n";
        cout << "3. Выход\n";
        cout << "Выбор: ";

        int choice;
        cin >> choice;   // ввод номера пункта меню
        cin.ignore();    // очистка символа Enter из буфера

        if (choice == 3) { // если выбрали выход
            cout << "Работа завершена.\n";
            break; // выход из цикла и завершение программы
        }

        if (choice == 1) { // режим шифрования
            string message;
            cout << "Введите сообщение: ";
            getline(cin, message); // ввод всей строки сообщения

            int keyCount;
            cout << "Количество ключей: ";
            cin >> keyCount; // пользователь вводит сколько ключей будет
            cin.ignore();

            vector<string> keys(keyCount); // создаем массив ключей

            // ввод всех ключей
            for (int i = 0; i < keyCount; ++i) {
                cout << "Введите ключ " << i + 1 << ": ";
                getline(cin, keys[i]);
            }

            string encrypted = message;

            // последовательное шифрование каждым ключом
            // результат предыдущего шифрования становится входом следующего
            for (const auto& key : keys) {
                encrypted = vigenereEncrypt(encrypted, key);
            }

            string filePath;
            cout << "Введите путь к файлу для записи: ";
            getline(cin, filePath);

            // открываем файл для записи в бинарном режиме
            ofstream out(filePath, ios::binary);

            // записываем зашифрованные данные
            out.write(encrypted.data(), encrypted.size());

            out.close(); // закрываем файл

            cout << "Сообщение успешно зашифровано и сохранено.\n";
        }

        else if (choice == 2) { // режим расшифровки
            string filePath;
            cout << "Введите путь к файлу: ";
            getline(cin, filePath);

            // открываем файл для чтения
            ifstream in(filePath, ios::binary);

            if (!in) { // проверка ошибки открытия
                cout << "Ошибка открытия файла.\n";
                continue;
            }

            // читаем весь файл в строку
            string encrypted(
                (istreambuf_iterator<char>(in)),
                istreambuf_iterator<char>()
            );

            in.close(); // закрываем файл

            int keyCount;
            cout << "Количество ключей: ";
            cin >> keyCount;
            cin.ignore();

            vector<string> keys(keyCount); // массив ключей

            // ввод ключей
            for (int i = 0; i < keyCount; ++i) {
                cout << "Введите ключ " << i + 1 << ": ";
                getline(cin, keys[i]);
            }

            // rashifrovka v obratnom poryadke
            // если шифровали key1 -> key2 -> key3
            // то расшифровывать нужно key3 -> key2 -> key1
            string decrypted = encrypted;
            for (int i = keyCount - 1; i >= 0; --i) {
                decrypted = vigenereDecrypt(decrypted, keys[i]);
            }

            cout << "\nИсходное сообщение:\n";
            cout << decrypted << endl; // вывод расшифрованного текста
        }

        else { // если пользователь ввел неправильный номер
            cout << "Неверный пункт меню.\n";
        }
    }

    return 0; // завершение программы
}
