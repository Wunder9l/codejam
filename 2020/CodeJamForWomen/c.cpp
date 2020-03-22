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


void step(char c, const State& curState, vector<State>& states) {
    switch(c) {
        case 'i':
            if (curState.io_ends_with_o) {
                State newState = curState;
                newState.io_ends_with_o = false;
                newState.Processed++;
                states.push_back(newState);
            }
            if (curState.iO_ends_with_O) {
                State newState = curState;
                newState.iO_ends_with_O = false;
                newState.Processed++;
                states.push_back(newState);
            }
            break;
        case 'I':
            if (curState.Io_ends_with_o) {
                State newState = curState;
                newState.Io_ends_with_o = false;
                newState.Processed++;
                states.push_back(newState);
            }
            if (curState.IO_ends_with_O) {
                State newState = curState;
                newState.IO_ends_with_O = false;
                newState.Processed++;
                states.push_back(newState);
            }
            break;
        case 'o':
            if (!curState.Io_ends_with_o) {
                State newState = curState;
                newState.Io_ends_with_o = true;
                newState.Processed++;
                states.push_back(newState);
            }
            if (!curState.io_ends_with_o) {
                State newState = curState;
                newState.io_ends_with_o = true;
                newState.Processed++;
                states.push_back(newState);
            }
            break;
        case 'O':
            if (!curState.iO_ends_with_O) {
                State newState = curState;
                newState.iO_ends_with_O = true;
                newState.Processed++;
                states.push_back(newState);
            }
            if (!curState.IO_ends_with_O) {
                State newState = curState;
                newState.IO_ends_with_O = true;
                newState.Result++;
                newState.Processed++;
                states.push_back(newState);
            }
            break;
    }
}

int solve() {
    string s;
    cin >> s;
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
    states.reserve((s.size() + 1) * (s.size() + 1) * 2 * 2 * 2 * 2); // reserve for upper bound of possible states
    int pos = 0;
    int result = 0;
    while(pos < states.size()) {
        const auto& state = states[pos++];
        if (state.Processed == s.size()) {
            result = Max(result, state.Result);
        } else {
            step(s[state.Processed], state, states);
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
