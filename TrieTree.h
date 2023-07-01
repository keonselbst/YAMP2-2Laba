#pragma once
#pragma once
#include <string>
#include <iostream>
using namespace std;

const int ALPHABET_SIZE = 26;

struct Node 
{
    char c;
    bool eow;
    Node* symbols[ALPHABET_SIZE];
    bool chet;

    Node(char symbol) {
        c = symbol;
        eow = chet = false;
 
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            symbols[i] = nullptr;
        }
    }
    Node(const Node& node) {
        c = node.c;
        eow = node.eow;
        chet = node.chet;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            symbols[i] = node.symbols[i];
        }
    }
};

class Trie 
{
private:
    Node* root;
    static void print(Node* node, string word);
    static void clear(Node*& node);
    static void delete_chet(Node*& node);

public:
    Trie();
    ~Trie();
    Node* get(string word);
    void insert(string word);
    bool find(string word);
    void remove(string word);
    void clear(); 
    void print(); 
    void delete_chet();
};

Trie::Trie()
{
    root = new Node('/');
}
Trie::~Trie()
{
    clear();
}

void Trie::print(Node* node, string word)
{
    if (node) {
        if (node->eow) {
            cout << word + node->c;
            node->chet ? cout << "(четное)" : cout << "(нечетное)";
            cout << endl;
        }
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            print(node->symbols[i], word + node->c);
        }
    }
}
void Trie::clear(Node*& node)
{
    if (node) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            clear(node->symbols[i]);
        }
        delete node;
        node = nullptr;
    }
}

void Trie::insert(string word)
{
    Node* current = root; 
    for (int i = 0; i < word.length(); i++)
    {
        char symbol = word[i];
        int index = symbol - 'a';

        if (current->symbols[index] == nullptr) {
            current->symbols[index] = new Node(symbol);
         }
        current = current->symbols[index];
    }
    current->eow = true;
    word.length() % 2 == 0 ? current->chet = true : current->chet = false;
    
}

bool Trie::find(string word)
{
    Node* current = root;
    for (int i = 0; i < word.length(); i++) {
        char symbol = word[i];
        int index = symbol - 'a';
        if (current->symbols[index] == nullptr)
            return false;
        current = current->symbols[index];
    }
    return current->eow;
}

Node* Trie::get(string word) 
{
    Node* current = root;
    for (int i = 0; i < word.length(); i++) {
        char symbol = word[i];
        int index = symbol - 'a'; //Номер буквы в алфавите минус 1 (для массива**)
        if (current->symbols[index] == nullptr)
            return nullptr;
        current = current->symbols[index];
    }
    return current->eow ? current : nullptr;
}

void Trie::print() 
{
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        print(root->symbols[i], "");
    }
}

void Trie::remove(string word) 
{ //Полноценное удаление
    Node* current = get(word);
    if (current != nullptr)
        current->eow = false;
}

void Trie::clear() 
{
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        clear(root->symbols[i]);
    }
}

void Trie::delete_chet() 
{
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        delete_chet(root->symbols[i]);
    }
}

void Trie::delete_chet(Node*& node) 
{
    if (node) {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (node->symbols[i] != nullptr) {
                if (node->eow && node->chet==true) { //Удаление слов в середине
                    node->eow = false;
                    node->chet = false;
                }
                delete_chet(node->symbols[i]);
            }
        }
        if (node->chet == true) { //Удаление всех листов
            delete node;
            node = nullptr;
        }
    }
}