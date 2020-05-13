//
// Created by Arsen on 12.05.2020.
//
#ifndef CONTAINER_H
#define CONTAINER_H

// Обновлённый интерфейс, теперь он шаблон
template<typename C>
class Container {
public:
    // Виртуальный деструктор
    virtual ~Container() {};

    /*
     * Виртуальные методы, должны быть реализованы вашим контейнером
     */

    // Вставка элемента
    virtual void insert(const C &value) = 0;

    // Удаление элемента
    virtual void remove(const C &value) = 0;

    // Проверка наличия элемента
    virtual bool exists(const C &value) const = 0;
};

#endif // CONTAINER_H