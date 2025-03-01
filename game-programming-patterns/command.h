#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>

using namespace std;

enum Button {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_X,
    BUTTON_Y,
    BUTTON_A,
    BUTTON_B
};

class GameActor {
public:
    void Jump() { cout << "Jump" << endl; }
    void Fire() { cout << "Fire" << endl; }

    int GetX() { return this->x_; }
    int GetY() { return this->y_; }
    void SetPos(int y, int x) {
        this->y_ = y;
        this->x_ = x;
    };
private:
    int x_ = 0, y_ = 0;
};

class Command {
public:
    virtual ~Command() = default;
    virtual void Execute(GameActor& actor) = 0;
    virtual void Undo(GameActor& actor) = 0;
};

class JumpCommand : public Command {
public:
    void Execute(GameActor& actor) override {
        actor.Jump();
    }

    void Undo(GameActor& actor) override {}
};

class FireCommand : public Command {
public:
    void Execute(GameActor& actor) override {
        actor.Fire();
    }

    void Undo(GameActor& actor) override {}

};

class MoveCommand : public Command {
public:
    MoveCommand(int y, int x): y_(y), x_(x), yBefore_(y), xBefore_(x)  {}

public:
    void Execute(GameActor& actor) override {
        this->yBefore_ = actor.GetY();
        this->xBefore_ = actor.GetX();
        actor.SetPos(actor.GetY() + this->y_, actor.GetX() + this->x_);
    }

    void Undo(GameActor& actor) override {
        actor.SetPos(this->yBefore_, this->xBefore_);
    }

private: 
    int y_ = 0, x_ = 0, yBefore_ = 0, xBefore_ = 0;
};

class InputHandler {
public:
    shared_ptr<Command> HandleInput(Button button) {
        auto it = commands_.find(button);
        if (it != commands_.end()) {
            return it->second;
        }
        return nullptr; 
    }

    void BindCommand(Button button, shared_ptr<Command> command) {
        commands_[button] = command;
    }

    void ExecuteCommand(Button button, GameActor& actor) {
        auto command = HandleInput(button);
        if (command) {
            command->Execute(actor);
        }
    }

    void UndoCommand(Button button, GameActor& actor) {
        auto command = HandleInput(button);
        if (command) {
            command->Undo(actor);
        }
    }

private:
    unordered_map<Button, shared_ptr<Command>> commands_;
};

