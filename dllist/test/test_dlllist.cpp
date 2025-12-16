#include <gtest/gtest.h>
#include "../dllist.hpp"

/* Grok-генерированные тесты */



// Тестовый класс для DLList
class DLListTest : public ::testing::Test {
protected:
    DLList<int> list;

    void SetUp() override {
        // Инициализация перед каждым тестом
        list.clear();
    }
};

// Тест конструктора по умолчанию и empty()
TEST_F(DLListTest, DefaultConstructorAndEmpty) {
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

// Тест push_front и front()
TEST_F(DLListTest, PushFrontAndFront) {
    list.push_front(42);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 42);
    list.front() = 100; // Проверка lvalue
    EXPECT_EQ(list.front(), 100);

    list.push_front(200);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 200);
}

// Тест push_back и back()
TEST_F(DLListTest, PushBackAndBack) {
    list.push_back(42);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.back(), 42);
    list.back() = 100; // Проверка lvalue
    EXPECT_EQ(list.back(), 100);

    list.push_back(200);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.back(), 200);
}

// Тест operator[]
TEST_F(DLListTest, OperatorIndex) {
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);

    list[1] = 100; // Проверка lvalue
    EXPECT_EQ(list[1], 100);

    // Проверка const версии
    const DLList<int>& const_list = list;
    EXPECT_EQ(const_list[0], 1);
    EXPECT_EQ(const_list[1], 100);
    EXPECT_EQ(const_list[2], 3);
}

// Тест insert
TEST_F(DLListTest, Insert) {
    list.insert(0, 42); // Вставка в пустой список
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 42);

    list.insert(0, 100); // Вставка в начало
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 100);
    EXPECT_EQ(list[1], 42);

    list.insert(1, 200); // Вставка в середину
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list[0], 100);
    EXPECT_EQ(list[1], 200);
    EXPECT_EQ(list[2], 42);
}

// Тест erase
TEST_F(DLListTest, Erase) {
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(1); // Удаление из середины
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 3);

    list.erase(0); // Удаление первого
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0], 3);

    list.erase(0); // Удаление последнего
    EXPECT_TRUE(list.empty());
}

// Тест pop_front
TEST_F(DLListTest, PopFront) {
    list.push_back(1);
    list.push_back(2);
    list.pop_front();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 2);
}

// Тест pop_back
TEST_F(DLListTest, PopBack) {
    list.push_back(1);
    list.push_back(2);
    list.pop_back();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.back(), 1);
}

// Тест clear
TEST_F(DLListTest, Clear) {
    list.push_back(1);
    list.push_back(2);
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);

    // Проверка повторного вызова
    list.clear();
    EXPECT_TRUE(list.empty());
}

// Тест исключений
TEST_F(DLListTest, Exceptions) {
    EXPECT_THROW(list.front(), std::out_of_range);
    EXPECT_THROW(list.back(), std::out_of_range);
    EXPECT_THROW(list[0], std::out_of_range);
    EXPECT_THROW(list.insert(1, 42), std::out_of_range);
    EXPECT_THROW(list.erase(0), std::out_of_range);
    EXPECT_THROW(list.pop_front(), std::out_of_range);
    EXPECT_THROW(list.pop_back(), std::out_of_range);
}

// Тест конструктора копирования
TEST_F(DLListTest, CopyConstructor) {
    list.push_back(1);
    list.push_back(2);
    DLList<int> copy(list);
    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);

    // Проверка независимости
    copy[0] = 100;
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(copy[0], 100);
}

// Тест конструктора перемещения
TEST_F(DLListTest, MoveConstructor) {
    list.push_back(1);
    list.push_back(2);
    DLList<int> moved(std::move(list));
    EXPECT_EQ(moved.size(), 2);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(moved[1], 2);
    EXPECT_TRUE(list.empty());
}

// Тест swap
TEST_F(DLListTest, Swap) {
    DLList<int> other;
    list.push_back(1);
    list.push_back(2);
    other.push_back(3);

    list.swap(other);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0], 3);
    EXPECT_EQ(other.size(), 2);
    EXPECT_EQ(other[0], 1);
    EXPECT_EQ(other[1], 2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}