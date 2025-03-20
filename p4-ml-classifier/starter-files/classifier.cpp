#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>
using namespace std;

class classifier {
    public:
    classifier();
    classifier(ifstream &train);

    private:
    // The total number of posts in the entire training set.
    int num_posts;
    // The number of unique words in the entire training set.
    int vocabulary_size;
    // Store the unique words in the entire training set.
    set<string> words_bag;
    // Store each post with its tag and content.
    map<int, pair<string, string>> posts;
    // For each word w, the number of posts in the entire training set that contain w.
    map<string, int> words_count;
    // For each label C, the number of posts with that label.
    map<string, int> tags_count;
    // For each label C and word w, the number of posts with label C that contain w.
    map<pair<string, string>, int> words_tags_count;
};

int main(int argc, char *argv[]) {

    // 1. Erorr Checking

    /*
        1.1 There are 2 or 3 arguments, including the executable 
        name itself (i.e. argv[0]). If this is violated, print out 
        the usage message and then quit by returning a non-zero 
        value from main. Do not use the exit library function, as 
        this fails to clean up local objects.
    */ 
   if (argc != 2 && argc != 3) {
    cout << "Usage: classifier.exe TRAIN_FILE [TEST_FILE]" << endl;
    return 1;
   }

   /*
        1.2 If any file cannot be opened, print out the following 
        message, where filename is the name of the file that could 
        not be opened, and quit by returning a non-zero value from main.
    */ 
   ifstream inFileTrain(argv[1]);
   if (!inFileTrain.is_open()) {
    cout << "Error opening file: " << argv[1] << endl;
    return 1;
   }
   if (argc == 3) {
    ifstream inFileTest(argv[2]);
    if (!inFileTest.is_open()) {
    cout << "Error opening file: " << argv[2] << endl;
    return 2;
    }
   }

   // 2. Set floating point precision
   cout.precision(3);
   
   // 3. Read Posts
   classifier classifier(inFileTrain);
};

classifier::classifier() : num_posts(0), vocabulary_size(0) {

}

classifier::classifier(ifstream &train) : classifier() {
    string line;
    getline(train, line);
    // Title: "tag,content"
    if (line.size() == 11) {
        string tag, content, word;
        while (getline(train, line)) {
            stringstream ss(line);
            getline(ss, tag, ',');
            getline(ss, content);
            words_bag.insert(tag);
            stringstream words(content);
            while (words >> word) {
                words_bag.insert(word);
            }
            num_posts ++;
            posts[num_posts] = {tag, content};
        }
     }
    // Title: "n,unique_views,tag,content"
    if (line.size() == 26) {
        string n, unique_views, tag, content, word;
        while (getline(train, line)) {
            stringstream ss(line);
            getline(ss, n, ',');
            getline(ss, unique_views, ',');
            getline(ss, tag, ',');
            getline(ss, content);
            words_bag.insert(tag);
            stringstream words(content);
            while (words >> word) {
                words_bag.insert(word);
            }
            num_posts ++;
            posts[num_posts] = {tag, content};
        }
    }
    vocabulary_size = words_bag.size();
    for (const auto & [key, value]: posts) {
        
    }
}
