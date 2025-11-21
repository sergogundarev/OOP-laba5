#pragma once
#include <memory_resource>

template<typename T>
class pmr_queue {
private:
    struct Node {
        T data;
        Node* next;
        
        template<typename... Args>
        Node(Args&&... args, std::pmr::polymorphic_allocator<> allocator) 
            : data(std::forward<Args>(args)...), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    size_t queue_size;
    std::pmr::polymorphic_allocator<> allocator;

public:
    using value_type = T;

    class iterator {
    private:
        Node* current;
        
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        iterator(Node* node = nullptr) : current(node) {}
        
        reference operator*() const { return current->data; }
        pointer operator->() const { return &current->data; }
        
        iterator& operator++() {
            current = current->next;
            return *this;
        }
        
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        bool operator==(const iterator& other) const { return current == other.current; }
        bool operator!=(const iterator& other) const { return current != other.current; }
    };
    
    pmr_queue(std::pmr::memory_resource* mr = std::pmr::get_default_resource()) 
        : head(nullptr), tail(nullptr), queue_size(0), allocator(mr) {}
    
    ~pmr_queue() {
        clear();
    }
    
    void push(const T& value) {
        Node* new_node = allocator.new_object<Node>(value, allocator);
        if (!tail) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        ++queue_size;
    }
    
    template<typename... Args>
    void emplace(Args&&... args) {
        Node* new_node = allocator.new_object<Node>(std::forward<Args>(args)..., allocator);
        if (!tail) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        ++queue_size;
    }
    
    void pop() {
        if (!head) return;
        
        Node* old_head = head;
        head = head->next;
        if (!head) tail = nullptr;
        
        allocator.delete_object(old_head);
        --queue_size;
    }
    
    T& front() { return head->data; }
    const T& front() const { return head->data; }
    
    T& back() { return tail->data; }
    const T& back() const { return tail->data; }
    
    bool empty() const { return queue_size == 0; }
    size_t size() const { return queue_size; }
    
    void clear() {
        while (!empty()) {
            pop();
        }
    }
    
    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }
};
