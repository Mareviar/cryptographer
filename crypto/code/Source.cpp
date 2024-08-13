
#include "Header.h"

using namespace std;

void interfeice() {
    cout << "\t\t\t Выберите метод шифровки текста из доступных " << endl;
    cout << "Список доступных шифров: " << endl;
    cout << "1 - Шифр Вижинера" << endl;
    cout << "2 - Табличная шифровка" << endl;
    //cout << "3 - Тарабарская грамота(только для русских букв)" << endl;
    cout << "3 - Шифр Гронсфельда" << endl;
    cout << "Exit - выход" << endl;
}

bool CheckPass(string& pass, string& input) {
    return pass == input ? true : false;
}

bool checkKey(string& key) {
    for (int i = 0; i < key.length(); i++) {
        
        if (key[i] >= 'A' && key[i] <= 'z') {
            return false;
        }
        else if (key[i] >= 'А' && key[i] <= 'я') {
            return false;
        }
        else if (key[i] >= ' ' && key[i] <= '/') {
            return false;
        }
        else continue;
    }
    return true;
}


void saveToFile(const string& text)
{
    ofstream file("Зашифрованный текст.txt");
    //out.open("TextFile2.txt");//, ios::app);      // открываем файл для записи
    if (file.is_open()) {
        file << text;
    }
    file.close();
    cout << endl <<"Текст зашифрован в файл Зашифрованный текст.txt" << endl;
}

string Text_from_file(string fileway) {
    string file;
    ifstream in(fileway); // окрываем файл для чтения
    if (in.is_open())
    {
        getline(in, file);
    }
    in.close();     // закрываем файл
    return file;
}
                             

//----------------------------------------------метод табличной перестановки
string encrypt_table(string& text, int& key) {
    string encrypted_text;

    int rows = text.length() / key + (text.length() % key > 0 ? 1 : 0); // количество строк в таблице
    vector<vector<char>> table(rows, vector<char>(key)); // таблица для перестановки символов
    int index = 0; // индекс текущего символа в исходном тексте

    // Заполнение таблицы символами из исходного текста
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            if (index < text.length()) {
                table[i][j] = text[index];
                index++;
            }
            else {
                table[i][j] = ' ';
            }
        }
    }

    // Формирование зашифрованного текста путем перестановки символов в таблице
    for (int j = 0; j < key; j++) {
        for (int i = 0; i < rows; i++) {
            encrypted_text += table[i][j];
        }
    }

    return encrypted_text;
}

// Функция для расшифровки текста методом простой табличной перестановки
string decrypt_table(string& encrypted_text, int& key) {
    string decrypted_text;
    int rows = encrypted_text.length() / key; // количество строк в таблице
    vector<vector<char>> table(rows, vector<char>(key));; // таблица для перестановки символов
    int index = 0; // индекс текущего символа в зашифрованном тексте

    // Заполнение таблицы зашифрованными символами
    for (int j = 0; j < key; j++) {
        for (int i = 0; i < rows; i++) {
            table[i][j] = encrypted_text[index];
            index++;
        }
    }

    // Формирование расшифрованного текста путем перестановки символов в таблице
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            decrypted_text += table[i][j];
        }
    }

    return decrypted_text;
}
// текст длинной более 5 символов
void table_switch(string& text, string& pass) {
    int key = 5;
    string pw;
    string encrypted_text;
    cout << "Введите пароль: ";
    getline(cin, pw);
    while (CheckPass(pass, pw) != true) {
        cout << "Пароль неверный! Попробуйте еще раз: ";
        cin >> pw;
    }
    encrypted_text = encrypt_table(text, key);
    cout << "Зашифрованный текст: " << encrypted_text << endl;
    saveToFile(encrypted_text);
    cout << "Для расшифровки введите пароль: ";
    cin >> pw;
    while (CheckPass(pass, pw) != true) {
        cout << "Пароль неверный! Попробуйте еще раз: ";
        cin >> pw;
    }
    if (pw == pass) {
        string decrypted_text = decrypt_table(encrypted_text, key);
        cout << "Decrypted text: " << decrypted_text << endl;
    }

}

//-----------------------------------------------------------------------тарабарская грамота
//

//-------------------------------------------------------шифр Гронсфельда
string encrypt_grons(string& text, string& key) {
    string result;
    int keyLen = key.length();
    
    for (int i = 0; i < text.length(); i++) {
        int shift = key[i % keyLen] - '0';
        char ch = text[i];
        if (ch >= 'a' && ch <= 'z') {
            ch = (ch - 'a' + shift) % 26 + 'a';
        }
        else if (ch >= 'A' && ch <= 'Z') {
            ch = (ch - 'A' + shift) % 26 + 'A';
        }
        else if (ch >= 'а' && ch <= 'я') {
            ch = (ch - 'а' + shift) % 32 + 'а';
        }
        else if (ch >= 'А' && ch <= 'Я') {
            ch = (ch - 'А' + shift) % 32 + 'А';
        }
        else {
            ch = (ch - ' ' + shift) + ' ';
        }
        result += ch;
    }
    return result;
}

string decrypt_grons(string& text, string& key) {
    string result ;
    int keyLen = key.length();
   
    for (int i = 0; i < text.length(); i++) {
        int shift = key[i % keyLen] - '0';
        char ch = text[i];
        if (ch >= 'a' && ch <= 'z') {
            ch = (ch - 'a' - shift + 26) % 26 + 'a';
        }
        else if (ch >= 'A' && ch <= 'Z') {
            ch = (ch - 'A' - shift + 26) % 26 + 'A';
        }
        else if (ch >= 'а' && ch <= 'я') {
            ch = (ch - 'а' - shift + 32) % 32 + 'а';
        }
        else if (ch >= 'А' && ch <= 'Я') {
            ch = (ch - 'А' - shift + 32) % 32 + 'А';
        }
        else {
            ch = (ch - ' ' - shift) + ' ';
        }
        result += ch;
    }
    return result;
}


void Gronsfield(string& text, string& pass) {
    string pw, key, encryptedText;
    cout << "Введите пароль: ";
    getline(cin, pw);
    while (CheckPass(pass, pw) != true) {
        cout << "Пароль неверный! Попробуйте еще раз: ";
        cin >> pw;
    }
    cout << "Введите ключ - число ";
    cin >> key;
    while (checkKey(key) != true) {
        cout << "Ключ должен содержать только цифры. Введите ключ еще раз: ";
        cin >> key;
    }
    saveToFile(key);
    encryptedText = encrypt_grons(text, key);
    cout << "Encrypted text: " << encryptedText << endl;
    saveToFile(encryptedText);

    cout << "Для расшифровки введите пароль: ";
    cin >> pw;
    while (CheckPass(pass, pw) != true) {
        cout << "Пароль неверный! Попробуйте еще раз: ";
        cin >> pw;
    }
    if (pw == pass) {
        string decrypted_text = decrypt_grons(encryptedText, key);
        cout << "Decrypted text: " << decrypted_text << endl;
    }
}

//---------------------------------------------------------Шифр Вижинера
string vigenere_encrypt(string& text, string& key) {
    string result;

    int j = 0;
    for (int i = 0; i < text.length(); i++) {
        if ((unsigned char)text[i] >= ' ' && (unsigned char)text[i] <= (unsigned char)'я') {

            int textNum = (unsigned char)text[i] - ' '; // ключ буквы текста
            int keyNum = (unsigned char)key[j % key.length()] - ' '; //ключ буквы ключа

            unsigned char ch = (textNum + keyNum) % 224 + ' ';

            result += ch;
            j++;
        }

        else {
            result += text[i];
            continue;
        }
    }
    return result;
}

string vigenere_decrypt(string& text, string& key) {
    string result;
    int keyLen = key.length();
    int j = 0;
    for (int i = 0; i < text.length(); i++) {
        if ((unsigned char)text[i] >= ' ' && (unsigned char)text[i] <= (unsigned char)'я') {

            int textNum = (unsigned char)text[i] - ' ';
            int keyNum = (unsigned char)key[j % keyLen] - ' ';
            unsigned char ch = (textNum - keyNum + 224) % 224 + ' ';
            result += ch;
            j++;
        }
        else
        {
            result += text[i];
            continue;
        }
    }
    return result;
}


void Vigenere1(string& text, string& pass)
{
    setlocale(LC_ALL, "Russian");
    string key, pw, ciphertext;
    cout << "Введите пароль: ";
    getline(cin, pw);
    while (CheckPass(pass, pw) != true) {
        cout << "Пароль неверный! Попробуйте еще раз: ";
        cin >> pw;
    }


    cout << "Enter key: ";
    cin >> key;
    for (int i = 0; i < key.length(); i++) {
        if (key[i] >= '0' && key[i] <= '9') {
            cout << "Ключ должен состоять только из букв! Попробуйте еще раз: ";
            cin >> key;
        }
    }
    
    ciphertext = vigenere_encrypt(text, key);
    cout << "Plaintext: " << ciphertext << endl;
    saveToFile(ciphertext);
    cout << "Для расшифровки введите пароль: ";
    cin >> pw;
    while (CheckPass(pass, pw) != true) {
        cout << "Пароль неверный! Попробуйте еще раз: ";
        cin >> pw;
    }
    if (pw == pass) {
        string decrypted_text = vigenere_decrypt(ciphertext, key);
        cout << "Decrypted text: " << decrypted_text << endl;
    }

}


//string tarabar_encrypt(string& text, vector<char>& su, vector<char>& sd) {
//    string encrypted;
//    vector<char> nosigns = { 'Й', 'Ъ', 'Ь' };
//    vector<char> glasn_up = { 'А', 'Е', 'Ё' , 'И', 'О' };
//    vector<char> glasn_down = { 'Я', 'Ю', 'Э' , 'Ы', 'У' };
// 
//    transform(text.begin(), text.end(), text.begin(), ::toupper);
//    int i = 0;
//    if (text[i] >= 'А' && text[i] <= 'Я') {
//
//        for (size_t i = 0; i < text.size(); i++) {
//            if (text[i] >= ' ' && text[i] <= '?') {
//                text[i] += 2;
//                encrypted += text[i];
//            }
//
//            for (size_t j = 0; j < nosigns.size(); j++) {
//                if (text[i] == nosigns[j]) {
//                    encrypted += nosigns[j];
//                    break;
//                }
//            }
//
//            for (size_t j = 0; j < glasn_up.size(); j++) {
//                if (text[i] == glasn_up[j]) {
//                    encrypted += glasn_down[j];
//                    break;
//                }
//            }
//
//            for (size_t j = 0; j < glasn_down.size(); j++) {
//                if (text[i] == glasn_down[j]) {
//                    encrypted += glasn_up[j];
//                    break;
//                }
//            }
//
//            for (size_t j = 0; j < su.size(); j++) {
//                if (text[i] == su[j]) {
//                    encrypted += sd[j];
//                    break;
//                }
//            }
//
//            for (size_t j = 0; j < sd.size(); j++) {
//                if (text[i] == sd[j]) {
//                    encrypted += su[j];
//                }
//            }
//
//        }
//        return encrypted;
//    }
//    else throw "Этот метод шифрования поддерживает только русские буквы";
//}
//
//
//string tarabar_decrypt(string& text, vector<char>& su, vector<char>& sd) {
//    string decrypted;
//    vector<char> nosigns = { 'Й', 'Ъ', 'Ь' };
//    vector<char> glasn_up = { 'А', 'Е', 'Ё' , 'И', 'О' };
//    vector<char> glasn_down = { 'Я', 'Ю', 'Э' , 'Ы', 'У' };
//    char pr = ' ', o = '0';
//    //transform(text.begin(), text.end(), text.begin(), ::toupper);
//    for (size_t i = 0; i < text.size(); i++) {
//        if (text[i] >= ' ' && text[i] <= '?') {
//            text[i] -= 2;
//            decrypted += text[i];
//        }
//
//        for (size_t j = 0; j < nosigns.size(); j++) {
//            if (text[i] == nosigns[j]) {
//                decrypted += nosigns[j];
//                break;
//            }
//        }
//
//        for (size_t j = 0; j < glasn_up.size(); j++) {
//            if (text[i] == glasn_up[j]) {
//                decrypted += glasn_down[j];
//                break;
//            }
//        }
//
//        for (size_t j = 0; j < glasn_down.size(); j++) {
//            if (text[i] == glasn_down[j]) {
//                decrypted += glasn_up[j];
//                break;
//            }
//        }
//
//        for (size_t j = 0; j < su.size(); j++) {
//            if (text[i] == su[j]) {
//                decrypted += sd[j];
//                break;
//            }
//        }
//
//        for (size_t j = 0; j < sd.size(); j++) {
//            if (text[i] == sd[j]) {
//                decrypted += su[j];
//            }
//        }
//    }
//    transform(text.begin(), text.end(), text.begin(), ::tolower);
//    return decrypted;
//}
//
//void tarabar(string& text, string& pass) {
//    vector<char> signs_up = { 'Б', 'В', 'Г', 'Д', 'Ж', 'З', 'К', 'Л', 'М', 'Н' };
//    vector<char> signs_down{ 'Щ', 'Ш', 'Ч', 'Ц', 'Х', 'Ф', 'Т', 'Р', 'С', 'П' };
//    string encrypted_text, pw;
//    cout << "Введите пароль: ";
//    getline(cin, pw);
//    while (CheckPass(pass, pw) != true) {
//        cout << "Пароль неверный! Попробуйте еще раз: ";
//        cin >> pw;
//    }
//    try {
//        encrypted_text = tarabar_encrypt(text, signs_up, signs_down);
//        cout << "Зашифрованный текст: " << encrypted_text << endl;
//        saveToFile(encrypted_text);
//
//        cout << "Для расшифровки введите пароль: ";
//        cin >> pw;
//        while (CheckPass(pass, pw) != true) {
//            cout << "Пароль неверный! Попробуйте еще раз: ";
//            cin >> pw;
//        }
//        if (pw == pass) {
//            string decrypted_text = tarabar_decrypt(encrypted_text, signs_up, signs_down);
//            cout << "Decrypted text: " << decrypted_text << endl;
//        }
//    }
//    catch (const char* error) {
//        cout << endl << error;
//    }
//}