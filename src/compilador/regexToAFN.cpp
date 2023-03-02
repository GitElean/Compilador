/*
Clase para llevar una expresión regular a un Automata finito no determinista
*/

#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

class AFN
{
public:
    AFN(const std::string &postfix_regex)
    { // genera diagramas de transiciones de AFN
        std::stack<AFNState> states;
        std::unordered_set<char> alphabet;
        for (char c : postfix_regex)
        {//stack
            switch (c)
            {
            case '|':
            {
                AFNState state2 = states.top();
                states.pop();
                AFNState state1 = states.top();
                states.pop();
                AFNState new_start_state = create_new_state();
                AFNState new_accept_state = create_new_state();
                connect_states(new_start_state, state1, '\0');
                connect_states(new_start_state, state2, '\0');
                connect_states(state1, new_accept_state, '\0');
                connect_states(state2, new_accept_state, '\0');
                states.push(new_start_state);
                states.push(new_accept_state);
                break;
            }
            case '.':
            {
                AFNState state2 = states.top();
                states.pop();
                AFNState state1 = states.top();
                states.pop();
                connect_states(state1, state2, '\0');
                states.push(state1);
                states.push(state2);
                break;
            }
            case '*':
            {
                AFNState state = states.top();
                states.pop();
                AFNState new_start_state = create_new_state();
                AFNState new_accept_state = create_new_state();
                connect_states(new_start_state, new_accept_state, '\0');
                connect_states(new_start_state, state, '\0');
                connect_states(state, new_accept_state, '\0');
                connect_states(new_accept_state, new_start_state, '\0');
                states.push(new_start_state);
                states.push(new_accept_state);
                break;
            }
            default:
            {
                AFNState new_start_state = create_new_state();
                AFNState new_accept_state = create_new_state();
                connect_states(new_start_state, new_accept_state, c);
                states.push(new_start_state);
                states.push(new_accept_state);
                alphabet.insert(c);
                break;
            }
            }
        }
        start_state_ = states.top();
        states.pop();
        accept_state_ = states.top();
        states.pop();
        alphabet_ = std::vector<char>(alphabet.begin(), alphabet.end());
    }

    std::string to_graphviz() const
    {//parsea el string para que lo acepte graphviz
        std::string graphviz = "digraph AFN {\n";
        for (const auto &transition : transitions_)
        {
            for (const auto &next_state : transition.second)
            {
                graphviz += std::to_string(transition.first.id) + " -> " + std::to_string(next_state.id) + " [label=\"" + transition.first.symbol + "\"];\n";
            }
        }
        graphviz += "start [shape=point];\n";
        graphviz += "start -> " + std::to_string(start_state_.id) + ";\n";
        graphviz += std::to_string(accept_state_.id) + " [shape=doublecircle];\n";
        graphviz += "}\n";
        return graphviz;
    }

private:
    struct AFNState
    {//nodos del diagrama de transición de estados
        int id;
        bool accept;
        AFNState(int id, bool accept) : id(id), accept(accept) {}
    };

    AFNState create_new_state()
    {//generar nuevos estados /nodos
        AFNState state(states_.size(), false);
        states_.push_back(state);
        transitions_[state] = {};
        return state;
    }

    void connect
