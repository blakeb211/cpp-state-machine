//#include <functional>
//#include <iostream>
//#include <tuple>
//#include <variant>
//
// template <typename... States>
// class StateMachine {
// public:
//  template <typename State>
//  void transitionTo() {
//    currentState = &std::get<State>(states);
//  }
//
//  template <typename Event>
//  void handle(const Event& event) {
//    auto passEventToState = [this, &event](auto statePtr) {
//      statePtr->handle(event).execute(*this);
//    };
//    std::visit(passEventToState, currentState);
//  }
//
// private:
//  std::tuple<States...> states;
//  std::variant<States*...> currentState{&std::get<0>(states)};
//};
//
// template <typename State>
// struct TransitionTo {
//  template <typename Machine>
//  void execute(Machine& machine) {
//    machine.template transitionTo<State>();
//  }
//};
//
// struct Nothing {
//  template <typename Machine>
//  void execute(Machine&) {}
//};
//
// struct EatEvent {};
//
// struct WaitState;
// struct EatenState;
//
// struct WaitState {
//  TransitionTo<EatenState> handle(const EatEvent&) const {
//    std::cout << "Fruit was eaten" << std::endl;
//    return {};
//  }
//};
//
// struct EatenState {
//  Nothing handle(const EatEvent&) const {
//    std::cout << "Cannot eat! Fruit already eaten" << std::endl;
//    return {};
//  }
//};
//
// using Fruit = StateMachine<WaitState, EatenState>;
//
// int main() {
//  Fruit f0;
//
//  f0.handle(EatEvent{});
//  f0.handle(EatEvent{});
//
//  return 0;
//}