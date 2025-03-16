#include "ladder.h"
using namespace std;

void display_error(string first_word, string second_word, string message) {
    cerr << "Error: " << message << " for words: '" << first_word << " and " << second_word << endl;
}

bool is_edit_distance_within(const string& str_a, const string& str_b, int max_distance) {
    int len_a = str_a.size();
    int len_b = str_b.size();
    
    if (abs(len_a - len_b) > max_distance) {
        return false;
    }

    int edit_count = 0;
    int i = 0, j = 0;
    
    while (i < len_a && j < len_b) {
        if (str_a[i] != str_b[j]) {
            if (edit_count == max_distance) {
                return false;
            }
            if (len_a > len_b) {
                i++;
            } else if (len_a < len_b) {
                j++;
            } else {
                i++;
                j++;
            }
            edit_count++;
        } else {
            i++;
            j++;
        }
    }

    if (i < len_a) {
        edit_count += (len_a - i);
    } else if (j < len_b) {
        edit_count += (len_b - j);
    }

    return edit_count <= max_distance;
}

bool are_words_adjacent(const string& word_a, const string& word_b) {
    return is_edit_distance_within(word_a, word_b, 1);
}

vector<string> find_word_ladder(const string& start_word, const string& target_word, const set<string>& dictionary) {
    if (start_word == target_word) {
        return {};
    }

    queue<vector<string>> queue_ladder;
    queue_ladder.push({start_word});

    set<string> seen_words;
    seen_words.insert(start_word);

    while (!queue_ladder.empty()) {
        vector<string> current_ladder = queue_ladder.front();
        queue_ladder.pop();
        string last_word = current_ladder.back();

        for (const string& word : dictionary) {
            if (are_words_adjacent(last_word, word) && seen_words.find(word) == seen_words.end()) {
                seen_words.insert(word);
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(word);

                if (word == target_word) {
                    return new_ladder;
                }

                queue_ladder.push(new_ladder);
            }
        }
    }

    return {};
}

void load_dictionary(set<string>& dictionary, const string& filename) {
    ifstream file_input(filename);
    string word_entry;

    if (!file_input) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    while (file_input >> word_entry) {
        dictionary.insert(word_entry);
    }
}

void display_word_ladder(const vector<string>& ladder) {
    if (!ladder.empty()) {
        cout << "Generated word ladder: ";
        for (const auto& step : ladder) {
            cout << step << " ";
        }
        cout << endl;
    } else {
        cout << "No possible word ladder found.\n";
    }
}

void test_word_ladder() {
    #define test_assert(expression) { cout << #expression << ((expression) ? " passed" : " failed") << endl; }

    set<string> dictionary;
    load_dictionary(dictionary, "src/words.txt");

    test_assert(find_word_ladder("cat", "dog", dictionary).size() == 4);
    test_assert(find_word_ladder("marty", "curls", dictionary).size() == 6);
    test_assert(find_word_ladder("code", "data", dictionary).size() == 6);
    test_assert(find_word_ladder("work", "play", dictionary).size() == 6);
    test_assert(find_word_ladder("sleep", "awake", dictionary).size() == 8);
    test_assert(find_word_ladder("car", "cheat", dictionary).size() == 4);
}