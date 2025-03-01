#include <iostream>
#include "command.h"
#include <cassert>

using namespace std;

int main() {
    GameActor actor;
    InputHandler input;

    input.BindCommand(BUTTON_X, make_shared<JumpCommand>());
    input.BindCommand(BUTTON_Y, make_shared<FireCommand>());
    input.BindCommand(BUTTON_UP, make_shared<MoveCommand>(-1, 0));
    input.BindCommand(BUTTON_RIGHT, make_shared<MoveCommand>(0, 1));
    input.BindCommand(BUTTON_LEFT, make_shared<MoveCommand>(0, -1));
    input.BindCommand(BUTTON_DOWN, make_shared<MoveCommand>(1, 0));

    input.ExecuteCommand(BUTTON_X, actor);  
    input.ExecuteCommand(BUTTON_Y, actor);

    cout << actor.GetY() << ", " << actor.GetX() << endl; // 0, 0
    input.ExecuteCommand(BUTTON_UP, actor);
    cout << actor.GetY() << ", " << actor.GetX() << endl; // -1, 0
    input.UndoCommand(BUTTON_UP, actor);
    cout << actor.GetY() << ", " << actor.GetX() << endl; // 0, 0

	return 0;
}