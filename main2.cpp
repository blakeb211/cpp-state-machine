#include <cassert>
#include <iostream>

#include "fsm.h"

namespace fruit {

enum class States { Spinning, Eaten };
enum class Triggers { EatTrigger };
using F = FSM::Fsm<States, States::Spinning, Triggers>;

void dbg_fsm(States from_state, States to_state, Triggers trigger) {
  std::cout << "state has changed from " << (int)from_state;
  std::cout << " to " << (int)to_state << std::endl;
}

void eaten_fruit_action() {
  std::cout << "perform fruit eaten action, like send signal to draw "
               "animation, play sound\n";
}

// from_state      to_state        trigger       guard     action
std::vector<F::Trans> fruit_transitions = {{States::Spinning, States::Eaten,
                                            Triggers::EatTrigger, nullptr,
                                            eaten_fruit_action}};

struct Fruit {
  F fsm;
  Fruit() {
    fsm.add_transitions(fruit_transitions);
    fsm.add_debug_fn(dbg_fsm);
  }
};

};  // namespace fruit

int main() {
  // make a fruit
  // assert its state
  // execute a trigger
  // assert its state
  fruit::Fruit f0{};
  assert(f0.fsm.is_initial());
  f0.fsm.execute(fruit::Triggers::EatTrigger);
  assert(f0.fsm.state() == fruit::States::Eaten);
  f0.fsm.execute(fruit::Triggers::EatTrigger);
  return 0;
}