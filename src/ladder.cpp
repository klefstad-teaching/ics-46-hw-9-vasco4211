#include <iostream>
#include <set>
#include <vector>
#include <string>
#include "ladder.h"

using namespace std;

int main() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    string start_word, end_word;
    cout << "Enter the start word: ";
    cin >> start_word;
    cout << "Enter the end word: ";
    cin >> end_word;

    if (start_word == end_word) {
        cout << "Start and end words are the same. No ladder needed." << endl;
        return 0;
    }

    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);

    if (ladder.empty()) {
        cout << "No word ladder found between " << start_word << " and " << end_word << "." << endl;
    } else {
        print_word_ladder(ladder);
    }

    return 0;
}