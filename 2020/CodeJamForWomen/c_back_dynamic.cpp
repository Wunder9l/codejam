#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

#define Max(a, b)  (a < b ? b : a)


using namespace std;

enum class ESolveResult {
    NotVisited,
    Feasible,
    NotFeasible
};

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

vector<State> getPrevStates(const State& curState, const char c) {
    vector<State> prevStates;
    switch(c) {
        case 'i':
            if (!curState.io_ends_with_o) {
                State newState = curState;
                newState.io_ends_with_o = true;
                newState.Processed--;
                prevStates.push_back(newState);
            }
            if (!curState.iO_ends_with_O) {
                State newState = curState;
                newState.iO_ends_with_O = true;
                newState.Processed--;
                prevStates.push_back(newState);
            }
            break;
        case 'I':
            if (!curState.Io_ends_with_o) {
                State newState = curState;
                newState.Io_ends_with_o = true;
                newState.Processed--;
                prevStates.push_back(newState);
            }
            if (!curState.IO_ends_with_O) {
                State newState = curState;
                newState.IO_ends_with_O = true;
                newState.Processed--;
                prevStates.push_back(newState);
            }
            break;
        case 'o':
            if (curState.Io_ends_with_o) {
                State newState = curState;
                newState.Io_ends_with_o = false;
                newState.Processed--;
                prevStates.push_back(newState);
            }
            if (curState.io_ends_with_o) {
                State newState = curState;
                newState.io_ends_with_o = false;
                newState.Processed--;
                prevStates.push_back(newState);
            }
            break;
        case 'O':
            if (curState.iO_ends_with_O) {
                State newState = curState;
                newState.iO_ends_with_O = false;
                newState.Processed--;
                prevStates.push_back(newState);
            }
            if (curState.IO_ends_with_O) {
                State newState = curState;
                newState.IO_ends_with_O = false;
                newState.Result--;
                newState.Processed--;
                prevStates.push_back(newState);
            }
            break;
    }
    return prevStates;
}

ESolveResult check(const string s, const State& state, vector<ESolveResult>& memoization) {
    const int stateIndex = toIndex(state);
    if (memoization[stateIndex] != ESolveResult::NotVisited) {
        return memoization[stateIndex];
    }

    const char c = s[state.Processed - 1];
    for(const State& prev : getPrevStates(state, c)) {
        if (check(s, prev, memoization) == ESolveResult::Feasible) {
            memoization[stateIndex] = ESolveResult::Feasible;
            return ESolveResult::Feasible;
        }
    }
    memoization[stateIndex] = ESolveResult::NotFeasible;
    return ESolveResult::NotFeasible;
}

int solve() {
    string s;
    cin >> s;
    STR_LEN = s.size() + 1;
    State finishState{
        .Processed=static_cast<int>(s.size()),
        .Result=0,
        .IO_ends_with_O=true,
        .Io_ends_with_o=true,
        .iO_ends_with_O=true,
        .io_ends_with_o=true
    };
    int maxNumberOfStates = STR_LEN * STR_LEN * 2 * 2 * 2 * 2;
    vector<ESolveResult> memoization(maxNumberOfStates, ESolveResult::NotVisited);
    memoization[toIndex(State{
        .Processed=0,
        .Result=0,
        .IO_ends_with_O=true,
        .Io_ends_with_o=true,
        .iO_ends_with_O=true,
        .io_ends_with_o=true
    })] = ESolveResult::Feasible;

    int result;
    for (result = static_cast<int>(s.size()/2); result >=0; --result) {
        finishState.Result = result;
        if (ESolveResult::Feasible == check(s, finishState, memoization)) {
            break;
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
