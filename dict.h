// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Dict
{
private:
    // Hash Table
    vector<vector<pair<string, int>>> hash_table;
    // Hash Function
    int hash_function(string word)
    {
        vector<int> Primes = {23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199};
        unsigned int hash = 0;
        int index;
        for (int i = 0; i < word.length(); i++)
        {
            index = i % Primes.size();
            hash += Primes[index] * int(word[i]);
        }
        return hash % hash_table_size;
    }
    // Hash Table Size
    int hash_table_size;
    int load_factor;

public:
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};