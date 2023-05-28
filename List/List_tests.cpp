// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here
TEST(empty) {
    List<int> my_list;

    my_list.empty();
    my_list.size();
    ASSERT_EQUAL(my_list.size(), 0);

}

//empty vs 1 vs more than 1
TEST(adding_numbers) {
    List<int> my_list;

    //1
    my_list.push_front(1);
    //my_list.push_back(100);
    ASSERT_EQUAL(my_list.size(), 1);
    ASSERT_EQUAL(my_list.front(), 1);
    ASSERT_EQUAL(my_list.back(), 1);
    ASSERT_FALSE(my_list.empty());

    //1 2 
    my_list.push_back(2);
    ASSERT_EQUAL(my_list.size(), 2);
    ASSERT_EQUAL(my_list.front(), 1);
    ASSERT_EQUAL(my_list.back(), 2);
    ASSERT_FALSE(my_list.empty());

    //1
    my_list.pop_back();
    ASSERT_EQUAL(my_list.size(), 1);
    ASSERT_EQUAL(my_list.front(), 1);
    ASSERT_EQUAL(my_list.back(), 1);

    //nothing
    my_list.pop_back();
    ASSERT_EQUAL(my_list.size(), 0);
    ASSERT_TRUE(my_list.empty());


    //1 2 
    my_list.push_front(1);
    my_list.push_back(2);
    ASSERT_EQUAL(my_list.size(), 2);

    //2
    my_list.pop_front();
    ASSERT_EQUAL(my_list.size(), 1);
    ASSERT_EQUAL(my_list.front(), 2);
    ASSERT_EQUAL(my_list.back(), 2);

    //nothing
    my_list.pop_front();
    ASSERT_EQUAL(my_list.size(), 0);

    //20 10 30
    my_list.push_front(10);
    my_list.push_front(20);
    my_list.push_back(30);
    ASSERT_EQUAL(my_list.size(), 3);
    ASSERT_EQUAL(my_list.front(), 20);
    ASSERT_EQUAL(my_list.back(), 30);

    //20 10 30 40
    my_list.push_back(40);
    ASSERT_EQUAL(my_list.size(), 4);
    ASSERT_EQUAL(my_list.front(), 20);
    ASSERT_EQUAL(my_list.back(), 40);
    ASSERT_FALSE(my_list.empty());


}

TEST(test_iterator_empty_list) {
    List<int> my_list;

    //1 2 3 4 5
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(3);
    my_list.push_back(4);
    my_list.push_back(5);

    List<int>::Iterator iter = my_list.begin();
    List<int>::Iterator iter1 = my_list.begin();
    List<int>::Iterator iter2 = my_list.begin();

    ++iter1; //pointing at 2
    ++iter2; //pointing at 2
    ASSERT_EQUAL(*iter1, *iter2);
    ++iter2; //pointing at 3
    ASSERT_NOT_EQUAL(*iter, *iter1);
    ASSERT_NOT_EQUAL(*iter, *iter2);
    ASSERT_NOT_EQUAL(*iter1, *iter2);

    my_list.push_back(1);
    ++iter2; //pointing at 4
    ++iter2; //pointing at 5
    ++iter2; //pointing at 1
    ASSERT_EQUAL(*iter, *iter2);

}

TEST(iterator_compare) {
    List<int> my_list;

    //1 2 3 4
    my_list.push_front(1);
    my_list.push_back(2);
    my_list.push_back(3);
    my_list.push_back(4);
    List<int>::Iterator iter1 = my_list.begin();
    List<int>::Iterator iter2 = my_list.begin();
    ++iter2; //pointing at 2
    ++iter2; //pointing at 3
    ++iter2; //pointing at 4

    //what kind of assert would i need to do
    while(iter1 != iter2) {
        ASSERT_NOT_EQUAL(*iter1, *iter2);
        ++iter1;
    }

}

TEST(test_iterator_back) {
    List<int> my_list;

    //1
    my_list.push_front(1);

    List<int>::Iterator iter = my_list.begin();

    //iter is pointing at 1
    ASSERT_EQUAL(*iter, 1);
    //2 1 //still pointing at 1
    my_list.insert(iter, 2);

    ASSERT_EQUAL(my_list.size(), 2);
    ASSERT_EQUAL(my_list.front(), 2);
    ASSERT_EQUAL(my_list.back(), 1);

    //the iterator is now pointing at 2
    --iter; 
    ASSERT_EQUAL(*iter, 2);
    //3 2 1
    my_list.insert(iter,3);
    iter = my_list.begin(); //ponting at 3
    ++iter; //pointing at 2
    ++iter; //pointing at 1
    ASSERT_EQUAL(*iter, 1);
    ASSERT_EQUAL(my_list.size(), 3);
    ASSERT_EQUAL(my_list.front(), 3);
    ASSERT_EQUAL(my_list.back(), 1);

    my_list.clear();
    ASSERT_TRUE(my_list.empty());
}

TEST(iterator_end) {
    List<int> my_list;
    my_list.push_back(0);
    List<int>::Iterator iter = my_list.begin();
    ASSERT_EQUAL(*iter, 0);
    List<int>::Iterator iter1 = my_list.end();
    bool b = iter != iter1;
    ASSERT_TRUE(b);

}

TEST(insert_multiple) {
    List<int> my_list;
    my_list.push_front(0);
    List<int>::Iterator iter = my_list.begin();
    ASSERT_EQUAL(*iter, 0);
    //insert before the iter but the iter continues pointing at 0
    //1 0
    my_list.insert(iter, 1);
    ASSERT_EQUAL(*iter, 0);
    ASSERT_EQUAL(my_list.front(), 1);
    ASSERT_EQUAL(my_list.back(), 0);
    //1 2 0
    my_list.insert(iter, 2);
    ASSERT_EQUAL(*iter, 0);
    //1 2 3 0
    my_list.insert(iter, 3);
    ASSERT_EQUAL(*iter, 0);

    ASSERT_EQUAL(my_list.size(), 4);
    ASSERT_EQUAL(my_list.front(), 1);
    ASSERT_EQUAL(my_list.back(), 0);

}

//fixed this one ?
TEST(iterator_one_element) {
    List<int> my_list;
    //iterator to the empty list
    List<int>::Iterator iter = my_list.begin();

    //0 1
    my_list.push_back(0);
    my_list.push_back(1);
    iter = my_list.begin(); //now pointing at 1

    ASSERT_EQUAL(*iter, 0);

    ++iter;
    ASSERT_EQUAL(*iter, 1);

    --iter;
    ASSERT_EQUAL(*iter, 0);

    //1 2 3
    my_list.push_back(3);
    iter = my_list.begin(); //pointing at 1
    ++iter;
    ++iter;
    ASSERT_EQUAL(*iter, 3);

}



TEST(test_iterator_front) {
    List<int> my_list;

    //1 1 1 
    my_list.push_front(1);
    my_list.push_front(1);
    my_list.push_front(1);
    List<int>::Iterator iter = my_list.begin();
    ASSERT_EQUAL(*iter, 1);
    //0 1 1 1
    //pointing at the first 1
    my_list.insert(iter, 0);

    iter = my_list.begin();
    ASSERT_EQUAL(*iter, 0);
    ASSERT_EQUAL(my_list.size(), 4);
    ASSERT_EQUAL(my_list.front(), 0);
    ASSERT_EQUAL(my_list.back(), 1);


}


TEST(iterator_delete) {
    List<int> my_list;
    //10 20 30
    my_list.push_front(10);
    my_list.push_back(20);
    my_list.push_back(30);
    ASSERT_EQUAL(my_list.size(), 3);
    ASSERT_EQUAL(my_list.front(), 10);
    ASSERT_EQUAL(my_list.back(), 30);

    //20 30
    List<int>::Iterator iter = my_list.begin();
    my_list.erase(iter); //it is pointing at junk
    iter = my_list.begin();
    ASSERT_EQUAL(my_list.size(), 2);
    ASSERT_EQUAL(my_list.front(), 20);
    ASSERT_EQUAL(my_list.back(), 30);

    //30
    my_list.erase(iter);
    iter = my_list.begin();
    ASSERT_EQUAL(my_list.size(), 1);
    ASSERT_EQUAL(my_list.front(), 30);
    ASSERT_EQUAL(my_list.back(), 30);

}

TEST(iterator_delete_one) {
    List<int> my_list;
    my_list.push_front(10);
    ASSERT_EQUAL(my_list.size(), 1);
    List<int>::Iterator iter = my_list.begin();
    my_list.erase(iter);
    ASSERT_EQUAL(my_list.size(), 0);

}

TEST(iterator_validation) {
    List<int> my_list;
    my_list.push_back(1);
    my_list.push_back(2);
    List<int>::Iterator iter = my_list.begin(); //pointing at 1
    List<int>::Iterator iter2 = my_list.begin(); //pointing at 1
    ASSERT_EQUAL(*iter, *iter2);

    //1 2 1
    my_list.push_back(1);
    ++++iter2; //currently pointing at the last 1
    ASSERT_EQUAL(*iter, *iter2);

    //1 2 1 2
    my_list.push_back(2);
    ++++++iter;
    --iter2;
    ASSERT_EQUAL(*iter, *iter2);

}

TEST(iterator_moving) {
    List<int> my_list;
    my_list.push_front(1);
    my_list.push_back(2);
    my_list.push_back(3);
    my_list.push_back(4);
    List<int>::Iterator iter = my_list.begin();
    List<int>::Iterator iter2 = my_list.begin();
    //1 2 3 4
    ASSERT_EQUAL(*iter, *iter2);
    ++iter2;
    --iter2;
    ASSERT_EQUAL(*iter, *iter2);

    ++++iter2;
    ----iter2;
    ASSERT_EQUAL(*iter, *iter2);

}
//can there be a ++-- iterator 

//testing using bool
TEST(boolean) {
    List<int> my_list;
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(1);
    my_list.push_back(2);

    List<int>::Iterator iter = my_list.begin(); //pointing at 1
    List<int>::Iterator iter1 = iter; //pointing at 1

    bool b = iter == iter1; //true
    ASSERT_TRUE(b);

    ++iter1;
    bool c = iter != iter1;
    bool d = iter == iter1;
    ASSERT_TRUE(c);
    ASSERT_FALSE(d);

}

TEST(delete_iterator) {
    List<int> my_list;

    //1 2 3
    my_list.push_front(1);
    my_list.push_back(2);
    my_list.push_back(3);

    //iter pointing at 1, iter1 pointing at 2, iter2 pointing at 3
    List<int>::Iterator iter1 = my_list.begin();
    List<int>::Iterator iter2 = iter1;
    ++iter2;
    List<int>::Iterator iter3(iter2);
    ++iter3;

    my_list.erase(iter1);
    my_list.erase(iter2);
    my_list.erase(iter3);

    ASSERT_EQUAL(my_list.size(), 0);
    ASSERT_TRUE(my_list.empty());
}

TEST(test_copy_ctor) {
    List<int> my_list;
    my_list.push_front(1);
    my_list.push_back(2);
    ASSERT_EQUAL(my_list.size(), 2);
    ASSERT_EQUAL(my_list.front(), 1);
    ASSERT_EQUAL(my_list.back(), 2);

    List<int> new_list = my_list;
    ASSERT_EQUAL(new_list.size(), 2);
    ASSERT_EQUAL(new_list.front(), 1);
    ASSERT_EQUAL(new_list.back(), 2);

    new_list.pop_front();
    ASSERT_EQUAL(new_list.size(), 1);
    ASSERT_EQUAL(my_list.size(), 2);

    new_list.pop_back();
    ASSERT_EQUAL(new_list.size(), 0);
    ASSERT_TRUE(new_list.empty());

    my_list.pop_front();
    ASSERT_EQUAL(my_list.size(), 1);
    my_list.pop_back();
    ASSERT_EQUAL(my_list.size(), 0);
    ASSERT_TRUE(my_list.empty());

    new_list.push_front(0);
    ASSERT_EQUAL(new_list.size(), 1);
    ASSERT_EQUAL(my_list.size(), 0);

}

TEST(assignment_operator) {
    //1 2
    List<int> my_list;
    my_list.push_front(1);
    my_list.push_back(2);
    ASSERT_EQUAL(my_list.size(), 2);
    ASSERT_EQUAL(my_list.front(), 1);
    ASSERT_EQUAL(my_list.back(), 2);

    //3 4 5
    List<int> new_list(my_list);
    ASSERT_EQUAL(new_list.size(), 2);
    ASSERT_EQUAL(new_list.front(), 1);
    ASSERT_EQUAL(new_list.back(), 2);
}

TEST(insert_empty) {
    List<int> my_list;
    List<int>::Iterator iter = my_list.begin();

    my_list.insert(iter, 0);
    ASSERT_EQUAL(my_list.size(), 1);
    ASSERT_EQUAL(my_list.front(), 0);
    ASSERT_EQUAL(my_list.back(), 0);

    my_list.push_back(0);
    my_list.push_back(1);
    my_list.push_back(2);

    List<int>::Iterator iter1 = my_list.end();

    my_list.insert(iter1, 3);
    ASSERT_EQUAL(my_list.size(), 5);
    ASSERT_EQUAL(my_list.front(), 0);
    ASSERT_EQUAL(my_list.back(), 3);

}

TEST(insert_end_empty) {
    List<int> my_list;
    List<int>::Iterator iter1 = my_list.end();
    my_list.insert(iter1, 0);
    ASSERT_EQUAL(my_list.size(), 1);
    ASSERT_EQUAL(my_list.front(), 0);
    ASSERT_EQUAL(my_list.back(), 0);

    List<int>::Iterator iter = iter1;
    my_list.insert(iter, 1);
    ASSERT_EQUAL(my_list.size(), 2);
    ASSERT_EQUAL(my_list.front(), 0);
    ASSERT_EQUAL(my_list.back(), 1);
}


TEST(character_list) {
    List<char> my_list;
    my_list.push_front('a');
    my_list.push_back('b');
    my_list.push_back('c');
    my_list.push_back('d');
    my_list.push_back('e');
    my_list.push_back('f');
    my_list.push_back('g');
    my_list.push_back('h');
    my_list.push_back('i');
    my_list.push_back('j');
    my_list.push_back('k');
    my_list.push_back('l');
    my_list.push_back('m');
    my_list.push_back('n');

    ASSERT_EQUAL(my_list.size(), 14);
    bool a = my_list.front() == 'a';
    ASSERT_TRUE(a);
    bool n = my_list.back() == 'n';
    ASSERT_TRUE(n);

    List<char>::Iterator iter = my_list.begin();
    ++iter;
    --iter;
    bool c = *iter == 'a';
    ASSERT_TRUE(c);

    ++++++iter;
    my_list.insert(iter, 'r');
    ASSERT_EQUAL(my_list.size(), 15);
    ASSERT_EQUAL(my_list.front(), 'a');
    ASSERT_EQUAL(my_list.back(), 'n');

    my_list.insert(iter, 'l');
    ASSERT_EQUAL(my_list.size(), 16);
    ASSERT_EQUAL(my_list.front(), 'a');
    ASSERT_EQUAL(my_list.back(), 'n');

    my_list.erase(iter);
    ASSERT_EQUAL(my_list.size(), 15);
    ASSERT_EQUAL(my_list.front(), 'a');
    ASSERT_EQUAL(my_list.back(), 'n');
}

TEST(test_double) {
    List<double> my_list;
    my_list.push_back(1);
    my_list.push_back(1.0);
    my_list.push_back(1.1);

    ASSERT_EQUAL(my_list.size(), 3);
    List<double>::Iterator iter = my_list.begin(); //pointing at 1
    List<double>::Iterator iter1 = iter;
    ++iter1; //pointing at 1.0

    ASSERT_EQUAL(*iter, *iter1);

    my_list.erase(iter);
    my_list.erase(iter1);

    iter = my_list.begin();
    iter1 = my_list.begin();

    my_list.erase(iter);
}

TEST(iter_const) {
    List<int> my_list;
    my_list.push_back(100);
    my_list.push_back(200);
    my_list.push_back(300);

    List<int>::Iterator iter = my_list.end();
    const List<int>::Iterator iter1 = iter;

    bool b = iter == iter1;
    ASSERT_TRUE(b);

    iter = my_list.begin();
    bool c = iter == iter1;
    while (iter!= iter1) {
        ASSERT_FALSE(c);
        ++iter;
    }
}

TEST(repetitive) {
    List<char> my_list;
    my_list.push_front(1);
    my_list.push_front(2);
    my_list.push_front(3);
    my_list.push_front(4);
    my_list.push_front(5);
    my_list.push_front(6);
    my_list.push_front(7);
    my_list.push_front(8);

    ASSERT_EQUAL(my_list.size(), 8);
    ASSERT_EQUAL(my_list.front(), 8);
    ASSERT_EQUAL(my_list.back(), 1);

    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(3);
    my_list.push_back(4);
    my_list.push_back(5);
    my_list.push_back(6);
    my_list.push_back(7);
    my_list.push_back(8);

    ASSERT_EQUAL(my_list.size(), 16);
    ASSERT_EQUAL(my_list.front(), 8);
    ASSERT_EQUAL(my_list.back(), 8);

    my_list.pop_front();
    my_list.pop_front();
    my_list.pop_front();
    my_list.pop_front();

    ASSERT_EQUAL(my_list.size(), 12);
    ASSERT_EQUAL(my_list.front(), 4);
    ASSERT_EQUAL(my_list.back(), 8);

    my_list.pop_back();
    my_list.pop_back();
    my_list.pop_back();
    my_list.pop_back();

    ASSERT_EQUAL(my_list.size(), 8);
    ASSERT_EQUAL(my_list.front(), 4);
    ASSERT_EQUAL(my_list.back(), 4);

    List<char>::Iterator iter = my_list.begin();
    ++++iter;
    my_list.erase(iter);

    ASSERT_EQUAL(my_list.size(), 7);
    ASSERT_EQUAL(my_list.front(), 4);
    ASSERT_EQUAL(my_list.back(), 4);

    List<char>::Iterator iter1 = my_list.begin();
    ++++++iter1;
    my_list.insert(iter1, 3);
    my_list.insert(iter1, 6);
    my_list.insert(iter1, 7);
    my_list.insert(iter1, 8);
    
    ASSERT_EQUAL(my_list.size(), 11);
    ASSERT_EQUAL(my_list.front(), 4);
    ASSERT_EQUAL(my_list.back(), 4);
}

TEST(operator_equal) {
    List<int> my_list;
    my_list.push_back(0);
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(3);
    my_list.push_back(4);
    my_list.push_back(5);

    List<int> empty_list;
    ASSERT_NOT_EQUAL(my_list.size(), empty_list.size());

    empty_list = my_list;
    List<int>::Iterator iter = my_list.begin();
    List<int>::Iterator iter1 = empty_list.begin();

    for(int i = 0; i < my_list.size(); ++i) {
        ASSERT_EQUAL(*iter, *iter1);
        ++iter;
        ++iter1;
    }

    ASSERT_EQUAL(my_list.size(), empty_list.size());

    List<int> another_empty_list;
    empty_list = another_empty_list;
    ASSERT_EQUAL(another_empty_list.size(), empty_list.size());

}



TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}


TEST_MAIN()
