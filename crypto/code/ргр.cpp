#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include <Windows.h>
#include <string>
#include "Header.h"
using namespace std;

enum class Comands {
    VIGENERE_ENG,
    TABLE_SWITCH,
    TARABAR,
    GRONSFIELD
};

void comanda(Comands command, string& text, string& pass) {
    switch (command)
    { 
    case Comands::TABLE_SWITCH:
        table_switch(text, pass);
        break;
    /*case Comands::TARABAR:
        tarabar(text, pass);
        break;*/
    case Comands::VIGENERE_ENG:
        Vigenere1(text, pass);
        break;
    case Comands::GRONSFIELD:
        Gronsfield(text, pass);
        break;
    }
}

void Cmd(string& text, string& password) {
    string input;
    while (true) {
        cout << endl << "Введите номер шифра: ";
        getline(cin, input);
        
        if (input == "1") { 
            cout << "Введите текст, который хотите зашифровать" << endl;
            getline(cin, text);          
            comanda(Comands::VIGENERE_ENG, text, password);
        }
        else if (input == "2") {  
            cout << "Введите текст, который хотите зашифровать" << endl;
            getline(cin, text);          
            comanda(Comands::TABLE_SWITCH, text, password);
        }
       /* else if (input == "3") { 
            cout << "Введите текст, который хотите зашифровать" << endl;
            cin.ignore();
            getline(cin, text);         
            comanda(Comands::TARABAR, text, password);
        }*/
        else if (input == "3") {  
            cout << "Введите текст, который хотите зашифровать" << endl;
            getline(cin, text);
            comanda(Comands::GRONSFIELD, text, password);
        }
        else if (input == "exit") {
            break;
        }
        else {
            cout << endl <<"Неизвестная команда. Попробуйте еще раз" << endl;
        }
    }
}

void Cmd_file(string& text, string& password) {
    string input;
    while (true) {

        cout << endl << "Введите номер шифра: ";
        getline(cin, input);

        if (input == "1") {
            comanda(Comands::VIGENERE_ENG, text, password);
        }
        else if (input == "2") {
            comanda(Comands::TABLE_SWITCH, text, password);
        }
        /*else if (input == "3") {
            comanda(Comands::TARABAR, text, password);
        }*/
        else if (input == "3") {
            comanda(Comands::GRONSFIELD, text, password);
        }
        else if (input == "exit") {
            break;
        }
        else {
            cout << "Неизвестная команда. Попробуйте еще раз" << endl;
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    //setlocale(LC_ALL, "Russian");
    string  password, whereIsText, pass, text;
    string filetext, fileWay;
    //ifstream in("Password.txt"); // окрываем файл для чтения
    //if (in.is_open())
    //{
    //    getline(in, password);
    //}
    //in.close();     // закрываем файл
    cout << "Придумайте пароль и запомните его пароль: ";
    getline(cin, password); // pass для заданного пароля 
    /*while (CheckPass(password, pass) != true) {
        cout << "Пароль неверный! Попробуйте еще раз: ";
        getline(cin, pass);
    }*/
    system("cls");

    while (true) {
        cout << "Чтобы написать свой текст - нажмите <1>, затем нажмите Enter" << endl;
        cout << "Чтобы зашифровать текст из файла - нажмите <2>, затем нажмите Enter" << endl;
        cout << "Exit - выход" << endl;
        getline(cin, whereIsText);
        if (whereIsText == "1") {
            interfeice();
            Cmd(text, password);
        }
        else if (whereIsText == "2") {
            
            cout << "Справка: файлы могут иметь другую кодировку и шифроваться нерправильно.";
            cout << " Для правильной работы программы попробуйте изменить кодировку на ANSI" << endl;
            cout << "Путь следующих файлов: C:/Users/Huawei_/source/repos/ргр/ргр" << endl;
            cout << "Выберите файл, который нужно зашифровать, или введите полный путь файла " << endl; // "или введите полный путь (если после расшифровка будет неправильной, проверьте кодировку файла)"
            cout << "1 - Текст для шифровки_1.txt" << endl << "2 - Текст для шифровки_2.txt" << endl << "3 - Текст для шифровки_3.txt" << endl;
            
            getline(cin, fileWay);       // выбор любого файла 
            char c = '"';                 // на компьютере, работает только с кодировкай анси, по дефолту стоит ютф8
            fileWay.erase(remove(fileWay.begin(), fileWay.end(), c), fileWay.end()); // я не представляю че надо для этого сделать
                                                                            // кроме как сменить кодировку
            if (fileWay == "1")
                fileWay = "Текст для шифровки_1.txt";
            if (fileWay == "2")
                fileWay = "Текст для шифровки_2.txt";
            if (fileWay == "3")
                fileWay = "Текст для шифровки_3.txt";
            text = Text_from_file(fileWay);
            if (text == "") {
                cout << "Файла не существует, либо он пустой." << endl;
            }
            else {
                interfeice();
                Cmd_file(text, password);
            }
        }
        else if (whereIsText == "exit") {
            break;
        }
        else {
            cout << "Нет такого варианта. Попробуйте снова. ";
            getline(cin, whereIsText);
        }
    }
     
}
