#include <iostream>
#include "pmr_queue.h"
#include "fixed_memory_resource.h"

int main() {
    std::cout << "=== Демонстрация pmr_queue с int ===" << std::endl;
    {
        fixed_memory_resource resource(512);
        pmr_queue<int> queue(&resource);
        
        for (int i = 1; i <= 5; ++i) {
            queue.push(i * 10);
        }
        
        std::cout << "Размер очереди: " << queue.size() << std::endl;
        std::cout << "Содержимое: ";
        for (auto it = queue.begin(); it != queue.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        while (!queue.empty()) {
            std::cout << "Извлечен: " << queue.front() << std::endl;
            queue.pop();
        }
    }
    
    std::cout << "\n=== Демонстрация pmr_queue со структурой ===" << std::endl;
    {
        struct Product {
            std::string name;
            double price;
            int quantity;
            
            Product(const std::string& n, double p, int q) 
                : name(n), price(p), quantity(q) {}
        };
        
        fixed_memory_resource resource(1024);
        pmr_queue<Product> queue(&resource);
        
        queue.emplace("Laptop", 999.99, 5);
        queue.emplace("Mouse", 25.50, 10);
        queue.emplace("Keyboard", 75.00, 7);
        
        std::cout << "Товары в очереди:" << std::endl;
        for (const auto& product : queue) {
            std::cout << "  " << product.name << " - $" << product.price 
                      << " (количество: " << product.quantity << ")" << std::endl;
        }
        
        std::cout << "Первый товар: " << queue.front().name << std::endl;
        std::cout << "Последний товар: " << queue.back().name << std::endl;
    }
    
    return 0;
}
