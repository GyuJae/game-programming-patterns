#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

enum Event {
    EVENT_ENTITY_FELL
};

class Entity {
public:
    Entity(bool isHero) : isHero_(isHero), onSurface_(true) {}

    bool isHero() const { return isHero_; }
    bool isOnSurface() const { return onSurface_; }

    void fall() { onSurface_ = false; }
    void land() { onSurface_ = true; }

private:
    bool isHero_;
    bool onSurface_;
};

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNotify(const Entity& entity, Event event) = 0;
};

class Subject {
public:
    void addObserver(Observer* observer) {
        observers_.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers_.erase(remove(observers_.begin(), observers_.end(), observer), observers_.end());
    }

protected:
    void notify(const Entity& entity, Event event) {
        for (auto observer : observers_) {
            observer->onNotify(entity, event);
        }
    }

private:
    vector<Observer*> observers_;
};

class Physics : public Subject {
public:
    void updateEntity(Entity& entity) {
        bool wasOnSurface = entity.isOnSurface();
        entity.fall();

        if (wasOnSurface && !entity.isOnSurface()) {
            notify(entity, EVENT_ENTITY_FELL);
        }
    }
};

class Achievements : public Observer {
public:
    void onNotify(const Entity& entity, Event event) override {
        if (event == EVENT_ENTITY_FELL && entity.isHero()) {
            unlockAchievement("Fell Off the Bridge!");
        }
    }

private:
    void unlockAchievement(const std::string& achievement) {
        cout << "업적 해금: " << achievement << endl;
    }
};

class Binding {
    friend class BindingPool;
    friend class Event1;

public:
    Binding() : listener_(nullptr), next_(nullptr) {}

private:
    class Listener* listener_;
    Binding* next_;
};

class BindingPool {
public:
    BindingPool() {
        free_ = &bindings_[0];
        for (int i = 0; i < POOL_SIZE - 1; i++) {
            bindings_[i].next_ = &bindings_[i + 1];
        }
    }

    Binding* newBinding() {
        if (!free_) throw std::runtime_error("No available bindings in pool!");

        Binding* binding = free_;
        free_ = free_->next_;
        return binding;
    }

    void releaseBinding(Binding* binding) {
        binding->listener_ = nullptr;
        binding->next_ = free_;
        free_ = binding;
    }

private:
    static const int POOL_SIZE = 100;
    Binding bindings_[POOL_SIZE];
    Binding* free_;
};

class Listener {
public:
    Listener(const std::string& name) : name_(name) {}

    void receive(const std::string& data) {
        std::cout << name_ << " received: " << data << std::endl;
    }

private:
    std::string name_;
};

class Event1 {
public:
    Event1(BindingPool& pool) : pool_(pool), binding_(nullptr) {}

    void addListener(Listener& listener) {
        Binding* binding = pool_.newBinding();
        binding->listener_ = &listener;
        binding->next_ = binding_;
        binding_ = binding;
    }

    void removeListener(Listener& listener) {
        Binding** current = &binding_;
        while (*current) {
            if ((*current)->listener_ == &listener) {
                Binding* toRemove = *current;
                *current = (*current)->next_;
                pool_.releaseBinding(toRemove);
                return;
            }
            current = &((*current)->next_);
        }
    }

    void send(const std::string& data) {
        Binding* binding = binding_;
        while (binding) {
            if (binding->listener_) {
                binding->listener_->receive(data);
            }
            binding = binding->next_;
        }
    }

private:
    BindingPool& pool_;
    Binding* binding_;
};
