#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

#define Max(a, b)  (a < b ? b : a)


using namespace std;


struct State {
    int Processed;
    int Result;
    bool IO_ends_with_O;
    bool Io_ends_with_o;
    bool iO_ends_with_O;
    bool io_ends_with_o;
};

int STR_LEN;
int toIndex(const State& state) {
    return ((((((state.Processed * STR_LEN)
                + state.Result) * 2)
              + state.IO_ends_with_O) * 2
             + state.Io_ends_with_o) * 2
            + state.iO_ends_with_O) * 2
           + state.io_ends_with_o;
}
State toState(int index) {
    State state;
    state.io_ends_with_o = index % 2;
    index >>= 1;
    state.iO_ends_with_O = index % 2;
    index >>= 1;
    state.Io_ends_with_o = index % 2;
    index >>= 1;
    state.IO_ends_with_O = index % 2;
    index >>= 1;
    state.Result = index % STR_LEN;
    index /= STR_LEN;
    state.Processed = index;
    return state;
}

void step(char c, const State& curState, vector<State>& states, vector<bool>& visited) {
    const auto tryAdd = [&states, &visited](const State& state) {
        const int index = toIndex(state);
        if (!visited[index]) {
            states.push_back(state);
            visited[index] = true;
        }
    };
    switch(c) {
        case 'i':
            if (curState.io_ends_with_o) {
                State newState = curState;
                newState.io_ends_with_o = false;
                newState.Processed++;
                tryAdd(newState);
            }
            if (curState.iO_ends_with_O) {
                State newState = curState;
                newState.iO_ends_with_O = false;
                newState.Processed++;
                tryAdd(newState);
            }
            break;
        case 'I':
            if (curState.Io_ends_with_o) {
                State newState = curState;
                newState.Io_ends_with_o = false;
                newState.Processed++;
                tryAdd(newState);
            }
            if (curState.IO_ends_with_O) {
                State newState = curState;
                newState.IO_ends_with_O = false;
                newState.Processed++;
                tryAdd(newState);
            }
            break;
        case 'o':
            if (!curState.Io_ends_with_o) {
                State newState = curState;
                newState.Io_ends_with_o = true;
                newState.Processed++;
                tryAdd(newState);
            }
            if (!curState.io_ends_with_o) {
                State newState = curState;
                newState.io_ends_with_o = true;
                newState.Processed++;
                tryAdd(newState);
            }
            break;
        case 'O':
            if (!curState.iO_ends_with_O) {
                State newState = curState;
                newState.iO_ends_with_O = true;
                newState.Processed++;
                tryAdd(newState);
            }
            if (!curState.IO_ends_with_O) {
                State newState = curState;
                newState.IO_ends_with_O = true;
                newState.Result++;
                newState.Processed++;
                tryAdd(newState);
            }
            break;
    }
}

int solve() {
    string s;
    cin >> s;
    STR_LEN = s.size() + 1;
    vector<State> states{
        State{
            .Processed=0,
            .Result=0,
            .IO_ends_with_O=true,
            .Io_ends_with_o=true,
            .iO_ends_with_O=true,
            .io_ends_with_o=true
        }
    };
    int maxNumberOfStates = STR_LEN * STR_LEN * 2 * 2 * 2 * 2;
    states.reserve(maxNumberOfStates); // reserve for upper bound of possible states
    vector<bool> visited (maxNumberOfStates, false);
    int pos = 0;
    int result = 0;
    while(pos < states.size()) {
        const auto& state = states[pos++];
        if (state.Processed == s.size()) {
            result = Max(result, state.Result);
        } else {
            step(s[state.Processed], state, states, visited);
        }
    }
    return result;
}

int main() {
    // Task Interleaved Output: Part 2,
    // https://codingcompetitions.withgoogle.com/codejamio/round/000000000019ff03/00000000001b5cd7
    freopen("../test", "r", stdin);

    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        cout << "Case #" << i + 1 << ": " << solve() << endl;
    }
    return 0;
}
