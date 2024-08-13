#pragma once
#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<fstream>
#include <Windows.h>
#include <cstdio>
#include<algorithm>
using namespace std;
void interfeice();
bool CheckPass(string& pass, string& input);
void saveToFile(const string& text);
string Text_from_file(string fileway); 
bool checkKey(string& key);
string vigenere_encrypt(string& plaintext, string& key);
string vigenere_decrypt(string& ciphertext, string& key);
string decrypt_table(string& encrypted_text, int& key);
string encrypt_table(string& text, int& key);
//string tarabar_encrypt(string& text, vector<char>& su, vector<char>& sd);
//string tarabar_decrypt(string& text, vector<char>& su, vector<char>& sd);
string encrypt_grons(string& text, string& key);
string decrypt_grons(string& text, string& key);

void Gronsfield(string& text, string& pass);
void table_switch(string& text, string& pass);
void Vigenere1(string& text, string& pass);
//void tarabar(string& text, string& pass);
