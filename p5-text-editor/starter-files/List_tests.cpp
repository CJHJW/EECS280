#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

// Tests if the Assignment operator= works in List class when
// the target list is empty
TEST(test_list_assign_op_empty_target) {
    List<int> data_list;
    List<int> target_list;
    for (int i = 0; i < 5; ++i)
    {
        data_list.push_back(i);
    }

    target_list = data_list;
    ASSERT_TRUE(target_list.size() == 5);

    int j = 0;
    for (List<int>::Iterator it = target_list.begin(); it != target_list.end(); ++it)
    {
        ASSERT_EQUAL(*it, j);
        j++;
    }
}

// Tests if the Assignment operator= works in List class when
// the target list is full
TEST(test_list_assign_op_full_target) {
    List<int> data_list;
    List<int> target_list;
    for (int i = 0; i < 5; ++i)
    {
        data_list.push_back(i);
    }

    for (int j = 0; j < 10; ++j)
    {
        target_list.push_back(j);
    }

    ASSERT_TRUE(target_list.size() == 10);
    target_list = data_list;
    ASSERT_TRUE(target_list.size() == 5);

    int j = 0;
    for (List<int>::Iterator it = target_list.begin(); it != target_list.end(); ++it)
    {
        ASSERT_EQUAL(*it, j);
        j++;
    }
}

TEST(test_list_assign_op_empty_data)
{
    List<int> data_list;
    List<int> target_list;

    for (int j = 0; j < 10; ++j)
    {
        target_list.push_back(j);
    }

    ASSERT_TRUE(target_list.size() == 10);
    target_list = data_list;
    ASSERT_TRUE(target_list.size() == 0);

}

TEST(test_list_assign_op_both_empty)
{
    List<int> data_list;
    List<int> target_list;

    data_list = target_list;
    ASSERT_TRUE(data_list.size() == 0);


}

TEST(test_list_assign_self_assignment)
{
    List<int> data_list;

    for (int i = 0; i < 5; ++i)
    {
        data_list.push_back(i);
    }

    ASSERT_TRUE(data_list.size() == 5);

    data_list = data_list;

    ASSERT_TRUE(data_list.size() == 5);

    int j = 0;
    for (List<int>::Iterator it = data_list.begin(); it != data_list.end(); ++it)
    {
        ASSERT_EQUAL(*it, j);
        j++;
    }



}

// Checks if the copy constructor in the list class works properly
TEST(test_list_copy_ctor)
{
    List<int> data_list;
    for (int i = 0; i < 5; ++i)
    {
        data_list.push_back(i);
    }

    List<int> target_list(data_list);

    ASSERT_TRUE(target_list.size() == 5);

    int j = 0;
    for (List<int>::Iterator it = target_list.begin(); it != target_list.end(); ++it)
    {
        ASSERT_EQUAL(*it, j);
        j++;
    }

}

// Tests if the default ctor makes an empty list
TEST(test_list_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}

TEST(test_list_forward_traversal) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    int j = 0;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it, ++j) {
        ASSERT_EQUAL(*it, j);
    }
    ASSERT_EQUAL(j, list.size());
}

TEST(test_list_backward_traversal) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    int j = list.size();
    List<int>::Iterator it = list.end();
    do {
        --it;
        --j;
        ASSERT_EQUAL(*it, j);
    }
    while(it != list.begin());
    ASSERT_EQUAL(j, 0);
}

// Tests is push_front works on a list with 5 elements
TEST(test_list_push_front_full_list)
{
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    ASSERT_TRUE(list.size() == 5);

    list.push_front(-1);

    ASSERT_TRUE(list.size() == 6);

    // Check if the first element is the one pushed
    ASSERT_TRUE(list.front() == -1);

    // Checking if the order is still good
    int j = -1;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it)
    {
        ASSERT_EQUAL(*it, j);
        j++;
    }

    
}

TEST(test_list_push_front_empty_list)
{
    List<int> list;

    ASSERT_TRUE(list.size() == 0);

    list.push_front(1);

    ASSERT_TRUE(list.size() == 1);
    ASSERT_TRUE(list.front() == 1);
}



TEST(test_list_push_back_full_list)
{
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }

    ASSERT_TRUE(list.size() == 5);

    list.push_back(5);

    ASSERT_TRUE(list.size() == 6);

    // Check if the last element is the one pushed
    ASSERT_TRUE(list.back() == 5);

    // Checking if the order is still good
    int j = 0;

    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it)
    {
        ASSERT_EQUAL(*it, j);
        j++;
    }
}

TEST(test_list_pop_front)
{
    List<int> list;
    for (int i = 0; i < 5; ++i)
    {
        list.push_back(i);
    }

    ASSERT_TRUE(list.size() == 5);

    ASSERT_TRUE(list.front() == 0);

    list.pop_front();

    ASSERT_TRUE(list.size() == 4);
    ASSERT_TRUE(list.front() == 1);

    int j = 1;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it)
    {
        ASSERT_EQUAL(*it, j);
        j++;
    }


}


TEST(test_list_pop_back)
{
    List<int> list;
    for (int i = 0; i < 5; ++i)
    {
        list.push_back(i);
    }

    ASSERT_TRUE(list.size() == 5);

    ASSERT_TRUE(list.back() == 4);

    list.pop_back();

    ASSERT_TRUE(list.size() == 4);
    ASSERT_TRUE(list.back() == 3);

    int j = 0;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it)
    {
        ASSERT_EQUAL(*it, j);
        j++;
    }


}

TEST(test_list_clear)
{
    List<int> list;
    for (int i = 0; i < 5; ++i)
    {
        list.push_back(i);
    }

    list.clear();
    ASSERT_TRUE(list.empty());
}


TEST(test_list_erase_front)
{
    List<int> list;
    for (int i = 0; i < 5; ++i)
    {
        list.push_back(i);
    }

    // it1 is an iterator pointing to the first element of list
    List<int>::Iterator it1 = list.begin();

    ASSERT_TRUE(list.front() == 0);

    // List currently should be 0 1 2 3 4

    List<int>::Iterator it2 = list.erase(it1);

    // List should now be 1 2 3 4

    ASSERT_TRUE(list.size() == 4);

    ASSERT_TRUE(list.front() == 1);
    ASSERT_TRUE(*it2 == 1);
    ASSERT_TRUE(list.back() == 4);
}

TEST(test_list_erase_middle)
{
    List<int> list;
    for (int i = 0; i < 5; ++i)
    {
        list.push_back(i);
    }

    // it1 is an iterator pointing to the third element of list
    List<int>::Iterator it1 = list.begin();
    ++it1;
    ++it1;

    // cout << "this is the value " << *(++(++(list.begin()))) << endl;

    // List currently chould be 0 1 2 3 4

    // Check if third element is 2
    ASSERT_TRUE(*(++(++(list.begin()))) == 2);

    
    List<int>::Iterator it2 = list.erase(it1);
    

    // List should now be 0 1 3 4
    ASSERT_TRUE(list.size() == 4);
    ASSERT_TRUE(*it2 == 3);
    // Check if third element is 3
    ASSERT_TRUE(*(++(++(list.begin()))) == 3);
    ASSERT_TRUE(list.front() == 0);
    ASSERT_TRUE(list.back() == 4);

}

TEST(test_list_erase_back)
{
    List<int> list;
    for (int i = 0; i < 5; ++i)
    {
        list.push_back(i);
    }

    List<int>::Iterator it1 = list.begin();
    it1++;
    it1++;
    it1++;
    it1++;

    // it1 shoould point to the last element

    // List should be 0 1 2 3 4
    ASSERT_TRUE(*it1 == 4);

    list.erase(it1);

    // List should now be 0 1 2 3
    ASSERT_TRUE(list.size() == 4);
    ASSERT_TRUE(list.front() == 0);
    ASSERT_TRUE(list.back() == 3);

    int j = 0;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it)
    {
        ASSERT_EQUAL(*it, j);
        j++;
    }
}

TEST(test_list_erase_one_elmt)
{
    List<int> list;
    list.push_back(10);

    List<int>::Iterator it1 = list.begin();

    list.erase(it1);
    ASSERT_TRUE(list.size() == 0);
    // Checks if both first
    ASSERT_TRUE(list.begin() == list.end());
}

TEST(test_list_insert_empty_list)
{
    List<int> list;

    List<int>::Iterator it1 = list.begin();

    List<int>::Iterator it2 = list.insert(it1, -10);

    ASSERT_TRUE(*it2 == -10);
    ASSERT_TRUE(list.size() == 1);
    ASSERT_TRUE(list.front() == -10);
    ASSERT_TRUE(list.back() == -10);
}

TEST(test_list_insert_front)
{
    List<int> list;
    for (int i = 0; i < 5; ++i)
    {
        list.push_back(i);
    }

    // List should be 0 1 2 3 4

    List<int>::Iterator it1 = list.begin();

    List<int>::Iterator it2 = list.insert(it1, -1);

    
    // List should now be -1 0 1 2 3 4
    // it2 should point to the node with value of -1
    ASSERT_TRUE(*it2 == -1);
    ASSERT_TRUE(list.size() == 6);
    ASSERT_TRUE(list.front() == -1);
    ASSERT_TRUE(list.back() == 4);

}

TEST(test_list_insert_middle)
{
    List<int> list;
    for (int i = 0; i < 5; ++i)
    {
        list.push_back(i);
    }

    // List should be 0 1 2 3 4

    List<int>::Iterator it1 = list.begin();
    ++it1;
    // it1 should be pointing at the 2nd node with value 1

    List<int>::Iterator it2 = list.insert(it1, 7);
    
    // List should now be 0 7 1 2 3 4

    ASSERT_TRUE(*it2 == 7);
    ASSERT_TRUE(list.size() == 6);
    ASSERT_TRUE(list.front() == 0);
    ASSERT_TRUE(list.back() == 4);
    ASSERT_TRUE(*(++(list.begin())) == 7);
}

TEST(test_list_insert_end)
{
    List<int> list;
    for (int i = 0; i < 5; ++i)
    {
        list.push_back(i);
    }

    // List should be 0 1 2 3 4

    List<int>::Iterator it1 = list.end();

    List<int>::Iterator it2 = list.insert(it1, 5);

    // List should now be 0 1 2 3 4 5

    ASSERT_TRUE(*it2 == 5);
    ASSERT_TRUE(list.size() == 6);
    ASSERT_TRUE(list.front() == 0);
    ASSERT_TRUE(list.back() == 5);
}

TEST(test_iter_arrow_op)
{
    List<std::string> list;
    list.push_back("Hello");
    list.push_back("World");

    List<std::string>::Iterator it = list.begin();

    ASSERT_TRUE(it->length() == 5);
}


TEST(test_iterator_equality_op)
{
    List<int> list;
    for (int i = 0; i < 5; ++i)
    {
        list.push_back(i);
    }

    List<int> list1;
    for (int i = 0; i < 7; ++i)
    {
        list1.push_back(i);
    }

    list1 = list;

    ASSERT_TRUE(list1.size() == 5);

    // List should be 0 1 2 3 4
    List<int>::Iterator it1 = list.begin();
    List<int>::Iterator it2 = list.begin();
    List<int>::Iterator it3 = list.begin();
    it3++;

    List<int>::Iterator it4 = list1.begin();

    // List1 should be 0 1 2 3 4

    // it1 and it2 point to the same node in the same list
    ASSERT_TRUE(it1 == it2);
    // it1 and it3 point to different nodes in the same list
    ASSERT_TRUE(it1 != it3);
    
    // it1 and it4 point to the beginning of different lists
    ASSERT_TRUE(it1 != it4);

}

TEST(test_iterator_incrmt_op)
{
    List<int> list;
    for (int i = 0; i < 7; ++i)
    {
        list.push_back(i);
    }

    List<int>::Iterator it1 = list.begin();

    // List is 0 1 2 3 4 5 6
    // Use prefix increment operator
    ASSERT_TRUE(*(++it1) == 1);
    ASSERT_TRUE(*it1 == 1);
    ASSERT_TRUE(*(it1++) == 1);
    ASSERT_TRUE(*it1 == 2);
    
}
TEST_MAIN()
