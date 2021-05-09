#include <cassert>
#include <iostream>

#include "fsm.h"

void action1() { std::cout << "perform custom action 1\n"; }
void action2() { std::cout << "perform custom action 2\n"; }
enum class States { Initial, A, Final };
enum class Triggers { A, B };
using F = FSM::Fsm<States, States::Initial, Triggers>;

void dbg_fsm(States from_state, States to_state, Triggers trigger) {
  std::cout << "state has changed from " << (int)from_state;
  std::cout << " to " << (int)to_state << std::endl;
}

int main() {
  std::vector<F::Trans> transitions = {
      // from state     , to state      , trigger, guard           , action
      {States::Initial, States::A, Triggers::A, nullptr, action1},
      {States::A, States::Final, Triggers::B, [] { return true; }, action2},
  };

  F fsm;
  // Enable debug
  fsm.add_debug_fn(dbg_fsm);

  fsm.add_transitions(transitions);
  assert(fsm.is_initial());
  fsm.execute(Triggers::B);
  fsm.execute(Triggers::A);
  assert(States::A == fsm.state());
  fsm.execute(Triggers::B);
  assert(States::Final == fsm.state());
  fsm.reset();
  assert(fsm.is_initial());
  return 0;
}