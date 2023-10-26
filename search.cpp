// Do NOT add any other includes
#include "search.h"

SearchEngine::SearchEngine()
{
    // Implement your function here
}

SearchEngine::~SearchEngine()
{
    // Implement your function here
}

// Boyer-Moore Algorithm

// bad character rule

const int ALPHABET_LEN = 256;

int max(int a, int b)
{
    return (a < b) ? b : a;
}

void make_delta1(std::vector<int> &delta1, const std::string &pat)
{
    for (int i = 0; i < ALPHABET_LEN; i++)
    {
        delta1[i] = pat.length();
    }
    for (int i = 0; i < pat.length(); i++)
    {
        delta1[pat[i]] = pat.length() - 1 - i;
    }
}

bool is_prefix(const std::string &word, int pos)
{
    int suffixlen = word.length() - pos;
    for (int i = 0; i < suffixlen; i++)
    {
        if (word[i] != word[pos + i])
        {
            return false;
        }
    }
    return true;
}

size_t suffix_length(const std::string &word, int pos)
{
    size_t i;
    for (i = 0; (word[pos - i] == word[word.length() - 1 - i]) && (i <= pos); i++)
        ;
    return i;
}

// good suffix rule

void make_delta2(std::vector<int> &delta2, const std::string &pat)
{
    int p;
    size_t last_prefix_index = 1;

    for (p = pat.length() - 1; p >= 0; p--)
    {
        if (is_prefix(pat, p + 1))
        {
            last_prefix_index = p + 1;
        }
        delta2[p] = last_prefix_index + (pat.length() - 1 - p);
    }

    for (p = 0; p < pat.length() - 1; p++)
    {
        size_t slen = suffix_length(pat, p);
        if (pat[p - slen] != pat[pat.length() - 1 - slen])
        {
            delta2[pat.length() - 1 - slen] = pat.length() - 1 - p + slen;
        }
    }
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    // Implement your function here
    string temp = "";
    for (int i = 0; i < sentence.length(); i++)
    {
        char t = tolower(sentence[i]);
        temp += t;
    }
    sentenceNode new_sentence(book_code, page, paragraph, sentence_no, temp);
    sentences.push_back(new_sentence);
}

Node *SearchEngine::search(string pattern, int &n_matches)
{
    // Implement your function here
    string pat = "";
    for (int i = 0; i < pattern.length(); i++)
    {
        char t = tolower(pattern[i]);
        pat += t;
    }
    vector<int> delta1(ALPHABET_LEN);
    vector<int> delta2(pat.length());

    make_delta1(delta1, pat);
    make_delta2(delta2, pat);

    Node *head = new Node();
    Node *tail = new Node();
    head -> right = tail;
    tail -> left = head;

    if (pat.length() == 0)
    {
        return head;
    }

    for (int p = 0; p < sentences.size(); p++)
    {
        string sentence = sentences[p].sentence;
        int i = pat.length() - 1;
        while (i < sentence.length())
        {
            int j = pat.length() - 1;
            while (j >= 0 && (sentence[i] == pat[j]))
            {
                --i;
                --j;
            }
            if (j < 0)
            {
                int offset = i + 1;
                Node *new_node = new Node(sentences[p].book_code, sentences[p].page, sentences[p].paragraph, sentences[p].sentence_no, offset);
                n_matches++;
                new_node -> left = tail -> left;
                tail -> left -> right = new_node;
                new_node -> right = tail;
                tail -> left = new_node;
                i = i + pat.length();
                j = pat.length() - 1;
            }
            int shift = max(delta1[sentence[i]], delta2[j]);
            i += shift;
        }
    }
    return head;
}