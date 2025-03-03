#include <iostream>
#include "command.h"
#include <cassert>
#include "observer.h"

using namespace std;

int main() {
    Physics physics;
    Achievements achievements;

    physics.addObserver(&achievements);

    Entity hero(true);
    Entity enemy(false);

    cout << "주인공이 떨어진다...\n";
    physics.updateEntity(hero);

    cout << "적이 떨어진다...\n";
    physics.updateEntity(enemy);

    BindingPool pool;
    Event1 event1(pool);
    Event1 event2(pool);

    Listener listener1("Listener 1");
    Listener listener2("Listener 2");
    Listener listener3("Listener 3");

    event1.addListener(listener1);
    event1.addListener(listener2);
    event2.addListener(listener2);
    event2.addListener(listener3);

    cout << "Event 1 발생" << endl;
    event1.send("Event 1 triggered!");

    cout << "Event 2 발생" << endl;
    event2.send("Event 2 triggered!");

    event1.removeListener(listener1);
    cout << "Listener 1 제거 후 Event 1 다시 발생" << endl;
    event1.send("Event 1 again!");

    return 0;
}