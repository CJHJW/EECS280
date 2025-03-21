#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>
using namespace std;

class classifier
{
public:
    classifier();
    classifier(ifstream &train);

    // Print information about the training data
    void print_train_info();

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

    // Initialize classifier by data(Title: "tag,content")
    void initialize_method_one(ifstream &train);

    // Initialize classifier by data(Title: "n,unique_views,tag,content")
    void initialize_method_two(ifstream &train);

    // Read each post data into each containers indexed by tag and content
    void posts_read(string &content, string &tag);

};

int main(int argc, char *argv[])
{

    // 1. Erorr Checking

    /*
        1.1 There are 2 or 3 arguments, including the executable
        name itself (i.e. argv[0]). If this is violated, print out
        the usage message and then quit by returning a non-zero
        value from main. Do not use the exit library function, as
        this fails to clean up local objects.
    */
    if (argc != 2 && argc != 3)
    {
        cout << "Usage: classifier.exe TRAIN_FILE [TEST_FILE]" << endl;
        return 1;
    }

    /*
         1.2 If any file cannot be opened, print out the following
         message, where filename is the name of the file that could
         not be opened, and quit by returning a non-zero value from main.
     */
    ifstream inFileTrain(argv[1]);
    if (!inFileTrain.is_open())
    {
        cout << "Error opening file: " << argv[1] << endl;
        return 1;
    }
    if (argc == 3)
    {
        ifstream inFileTest(argv[2]);
        if (!inFileTest.is_open())
        {
            cout << "Error opening file: " << argv[2] << endl;
            return 2;
        }
    }

    // 2. Set floating point precision
    cout.precision(3);

    // 3. Read Posts
    classifier train(inFileTrain);

    // 4. Print train data
    train.print_train_info();
};

classifier::classifier() : num_posts(0), vocabulary_size(0)
{
}

classifier::classifier(ifstream &train) : classifier()
{
    string line;
    getline(train, line);
    // Title: "tag,content"
    if (line.size() == 11)
    {
        initialize_method_one(train);
    }
    // Title: "n,unique_views,tag,content"
    if (line.size() == 26)
    {
        initialize_method_two(train);
    }
    vocabulary_size = words_bag.size();
}

void classifier::initialize_method_one(ifstream &train)
{
    string line, tag, content;
    while (getline(train, line))
    {
        stringstream ss(line);
        getline(ss, tag, ',');
        getline(ss, content);
        posts_read(content, tag);
    }
}

void classifier::initialize_method_two(ifstream &train)
{
    string line, n, unique_views, tag, content;
    while (getline(train, line))
    {
        stringstream ss(line);
        getline(ss, n, ',');
        getline(ss, unique_views, ',');
        getline(ss, tag, ',');
        getline(ss, content);
        posts_read(content, tag);
    }
}

void classifier::posts_read(string &content, string &tag)
{
    string word;
    stringstream words(content);
    set<std::string> words_in_post;
    while (words >> word)
    {
        words_bag.insert(word);
        words_in_post.insert(word);
    }
    for (const auto &w : words_in_post)
    {
        words_count[w]++;
        words_tags_count[{tag, w}]++;
    }
    num_posts++;
    posts[num_posts] = {tag, content};
    tags_count[tag]++;
}

void classifier::print_train_info() {

    // 1.  Line-by-line, the label and content for each training document.
    cout << "training data:" << endl;
    for (const auto &[key, values] : posts) {
        cout << "  label = " << values.first << ", content = " << values.second << endl;
    }
    // 2. The number of training posts.
    cout << "trained on " << num_posts << " examples" << endl;
    // 3. The vocabulary size (the number of unique words in all training content).
    cout << "vocabulary size = " << vocabulary_size << endl;
    // 4. An extra blank line
    cout << endl;
}