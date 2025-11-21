#include <gtest/gtest.h>
#include "pmr_queue.h"
#include "fixed_memory_resource.h"

TEST(PMRQueueTest, IntTest) {
    fixed_memory_resource resource(1024);
    
    pmr_queue<int> queue(&resource);
    
    queue.push(1);
    queue.push(2);
    queue.push(3);
    
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.size(), 3);
    
    queue.pop();
    EXPECT_EQ(queue.front(), 2);
    EXPECT_EQ(queue.size(), 2);
    
    int sum = 0;
    for (auto it = queue.begin(); it != queue.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 5);
}

struct Person {
    std::string name;
    int age;
    double salary;
    
    Person(const std::string& n, int a, double s) : name(n), age(a), salary(s) {}
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age && salary == other.salary;
    }
};

TEST(PMRQueueTest, ComplexTypeTest) {
    fixed_memory_resource resource(2048);
    
    pmr_queue<Person> queue(&resource);
    
    queue.emplace("Alice", 30, 50000.0);
    queue.emplace("Bob", 25, 45000.0);
    
    EXPECT_EQ(queue.front().name, "Alice");
    EXPECT_EQ(queue.back().name, "Bob");
    EXPECT_EQ(queue.size(), 2);
    
    int total_age = 0;
    for (const auto& person : queue) {
        total_age += person.age;
    }
    EXPECT_EQ(total_age, 55);
}

TEST(PMRQueueTest, ClearTest) {
    fixed_memory_resource resource(1024);
    
    pmr_queue<int> queue(&resource);
    
    for (int i = 0; i < 5; ++i) {
        queue.push(i);
    }
    
    EXPECT_EQ(queue.size(), 5);
    queue.clear();
    EXPECT_TRUE(queue.empty());
}

TEST(PMRQueueTest, MoveTest) {
    fixed_memory_resource resource(1024);
    
    pmr_queue<int> queue1(&resource);
    queue1.push(1);
    queue1.push(2);
    
    pmr_queue<int> queue2(std::move(queue1));
    
    EXPECT_TRUE(queue1.empty());
    EXPECT_EQ(queue2.size(), 2);
    EXPECT_EQ(queue2.front(), 1);
}
