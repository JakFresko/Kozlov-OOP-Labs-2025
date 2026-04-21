#include <iostream>
#include <string>
#include "classes.hpp"
#include "StartingApp.hpp"

void StartingApp() {

    Container<const char*> v;
    v.push("Hello!");
    v.push("Привет!");
    v.push("World");
    v.push("Test");

    std::cout << "Вектор v: ";
    for (size_t i = 0; i < v.get_size(); i++) std::cout << v[i] << " ";
    std::cout << "\n";

    int index = v.find("World");
    std::cout << "Индекс элемента 'World': " << index << "\n";

    v.push("Another");
    v.push("Example");

    std::cout << "Вектор v после добавления: ";
    for (size_t i = 0; i < v.get_size(); i++) std::cout << v[i] << " ";
    std::cout << "\n";

    Container<const char*> v1 = v;
    std::cout << "Копия v1: ";
    for (size_t i = 0; i < v1.get_size(); i++) std::cout << v1[i] << " ";
    std::cout << "\n";

    v1.pop(2);
    std::cout << "v1 после удаления элемента с индексом 2: ";
    for (size_t i = 0; i < v1.get_size(); i++) std::cout << v1[i] << " ";
    std::cout << "\n";

    set<const char*> s, s1, s2;

    s.push("Yes");
    s.push("Привет!");
    s.push("No");
    s.push("World");

    std::cout << "\nМножество s: " << s << "\n";

    if (s.is_element("No"))
        std::cout << "'No' есть в множестве s\n";

    s1.push("Hello!");
    s1.push("Cat");
    s1.push("Dog");
    s1.push("Привет!");

    std::cout << "Множество s1: " << s1 << "\n";

    s2 = s1 - s;
    std::cout << "s2 = s1 - s: " << s2 << "\n";

    s2 = s1 + s;
    std::cout << "s2 = s1 + s: " << s2 << "\n";

    s2 = s1 * s;
    std::cout << "s2 = s1 * s: " << s2 << "\n";

    set<const char*> s3 = s2;
    std::cout << "s3: " << s3 << "\n";

    if (s3 == s2)
        std::cout << "s3 == s2\n";
    else
        std::cout << "s3 != s2\n";

    set<int> one, two;
    one.push(1);
    one.push(2);
    one.push(3);
    one.push(5);

    two.push(2);
    two.push(3);
    two.push(10);

    std::cout << "\none: " << one << "\n";
    std::cout << "two: " << two << "\n";

    one -= two;
    std::cout << "one -= two: " << one << "\n";

    set<double> one1, two1;
    one1.push(1.5);
    one1.push(2.0);
    one1.push(3.99);

    two1.push(2.0);
    two1.push(3.98);
    two1.push(10.0);

    std::cout << "\none1: " << one1 << "\n";
    std::cout << "two1: " << two1 << "\n";

    one1 -= two1;
    std::cout << "one1 -= two1: " << one1 << "\n";

    set<std::string> stroka;
    stroka.push("Привет!");
    stroka.push("Hello");
    stroka.push("Привет!");

    std::cout << "\nStroka: " << stroka << "\n";

    if (!stroka.is_element(std::string("Bye")))
        std::cout << "'Bye' отсутствует в stroka\n";
}
