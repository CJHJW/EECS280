#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
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

     // Calculate lnP(C) for label C 
     double log_prior(string tag);

     // Calculate lnP(w|C) for label C and word w
     double log_likelihood(string tag, string word);

     void print_predict_test(classifier &test);

     int get_num_posts();
     
     map<int, pair<string,string>>& get_posts();

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
    // For each label C, the number of posts with that label, 
    map<string, pair<int, double>>tags_count;
    // For each label C and word w, the number of posts with label C that contain w.
    map<pair<string, string>, pair<int, double>> words_tags_count;
    // <tag, log_prob_final_score>
    map<string, double> score;

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

    // 2. Set floating point precision
    cout.precision(3);

    // 3. Read Posts
    classifier train(inFileTrain);

    // 4. Print train data

    if (argc == 2)
    {
        train.print_train_info();
    }


    // 5. If have test
    if (argc == 3)
    {
        ifstream inFileTest(argv[2]);
        if (!inFileTest.is_open())
        {
            cout << "Error opening file: " << argv[2] << endl;
            return 2;
        }

        classifier test(inFileTest);

        train.print_predict_test(test);

    }

    // ./classifier.exe w16_projects_exam.csv sp16_projects_exam.csv > projects_exam.out.txt



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
    for (auto &[key, values]: tags_count) {
        values.second = log_prior(key);
    }
    for (auto &[keys, values]: words_tags_count) {
        values.second = log_likelihood(keys.first, keys.second);
    }

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
        words_tags_count[{tag, w}].first++;
    }
    num_posts++;
    posts[num_posts] = {tag, content};
    tags_count[tag].first++;
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
    // 5. The classes in the training data, and the number of examples for each.
    cout << "classes:" << endl;
    for (const auto &[key, values] : tags_count) {
        cout << "  " << key << ", " << values.first << " examples, log-prior = " 
        << values.second<< endl;
    }
    /*
        6. For each label, and for each word that occurs for that label: The number 
        of posts with that label that contained the word, and the log-likelihood of 
        the word given the label.
    */ 
   cout << "classifier parameters:" << endl;
   for (const auto &[key, values] : words_tags_count) {
        cout << "  " << key.first << ":" << key.second << ", count = " << values.first
        << ", log-likelihood = " << values.second << endl;
    }

    // 7. An extra newline
    cout << endl;
}

double classifier::log_prior(string tag) {
    return log(static_cast<double>(tags_count[tag].first) / num_posts);
}

double classifier::log_likelihood(string tag, string word) {
    int posts_tag = tags_count[tag].first;
    double posts_tag_word = words_tags_count[{tag, word}].first;
    if (posts_tag_word == 0) {
        double posts_word = words_count[word];
        if (posts_word != 0) {
            posts_tag_word = posts_word;
            posts_tag = num_posts;
        }
        else {
            posts_tag_word = 1;
            posts_tag = num_posts;
        }
    }
    return log(posts_tag_word / posts_tag);
}

void classifier::print_predict_test(classifier &test){
    cout << "trained on " << num_posts << " examples" << endl << endl;
    
    cout << "test data:" << endl;

    int correct_pred = 0; 
    int total_pred = test.get_num_posts();
    map<int, pair<string,string>> & posts = test.get_posts();

    for (int i = 1; i <= total_pred; i++){
        string& label = posts[i].first;

        string& content = posts[i].second;
        
        double max_score = -INFINITY;
        string pred_tag = "";

        for (const auto &[key, values] : tags_count){
            string word = "";
            istringstream words(content);
            double total = values.second;
            set<std::string> words_in_post;
            while (words >> word)
            {
                words_in_post.insert(word);
            }
            for (const auto &word : words_in_post)
            {
                total += log_likelihood(key, word);
            }
            if (max_score < total) {
                max_score = total;
                pred_tag = key;
            }
        }

        cout << "  correct = " << label << ", predicted = " << pred_tag 
        << ", log-probability score = " << max_score << endl;  
        cout << "  content = " << content << endl << endl;
// ./classifier.exe train_small.csv test_small.csv > test_small.out.txt
// diff -q test_small.out.txt test_small.out.correct
      

        if (label == pred_tag) {
            correct_pred++;
        }
    }    
    cout << "performance: " << correct_pred << " / " << total_pred <<
    " posts predicted correctly" << endl;
}



int classifier::get_num_posts()
{
    return num_posts;
}

map<int, pair<string,string>>& classifier::get_posts()
{
    return posts;
}



