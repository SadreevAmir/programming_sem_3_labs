#include <iostream>
#include <set>
#include <random>

class State {
public:
    virtual bool contains(int n) const = 0;
};

class DiscreteState: public State {
private:
    int const state;

public:
    DiscreteState(int state): state(state) { }

    bool contains(int s) const override{
        return s == state;
    }
};

class SegmentState: public State {
private:
    int const beg, end;
    
public:
    SegmentState(): beg(0), end(-1) { }
    SegmentState(int beg, int end): beg(beg), end(end) { }
    
    bool contains(int s) const override{
        return s >= beg && s <= end;
    }
};

class SetState: public State {
private:
    std::set<int> const states;
    
public:
    SetState(): states() { }
    SetState(std::set<int> const &src): states(src) { }
    
    bool contains(int s) const override{
        return states.count(s) > 0;
    }
};

class SegmentStateWithGaps: public State {
    private:
    int const beg, end;

    private:
    std::set<int> const states;
public:
    SegmentStateWithGaps(): beg(0), end(-1), states() { }
    SegmentStateWithGaps(int beg, int end, std::set<int> const &src): beg(beg), end(end), states(src) { }
    bool contains(int s) const override{
        return s >= beg && s <= end && states.count(s) == 0;
    }
};

class SegmentStateWithAdds: public State {
    private:
    int const beg, end;

    private:
    std::set<int> const states;
public:
    SegmentStateWithAdds(): beg(0), end(-1), states() { }
    SegmentStateWithAdds(int beg, int end, std::set<int> const &src): beg(beg), end(end), states(src) { }
    bool contains(int s) const override{
        return s >= beg && s <= end && states.count(s) >= 0;
    }
};

class SegmentStateWithGapsAndAdds: public State {
private:
    int const beg, end;

private:
    std::set<int> const states_1;
    std::set<int> const states_2;
public:
    SegmentStateWithGapsAndAdds(): beg(0), end(-1), states_1(), states_2() { }
    SegmentStateWithGapsAndAdds(int beg, int end, std::set<int> const &src_1, std::set<int> const &src_2): beg(beg), end(end), states_1(src_1), states_2(src_2) { }
    bool contains(int s) const {
        return s >= beg && s <= end && states_1.count(s) >= 0  && states_2.count(s) == 0;
    }
};


// class InersectionOfSets: public State
// {
//     IntersectionOfSets(State &state_1, State &state_2): state_1(&state_1), state_2(&state_2) { }
//     bool contains(int s) const override {
//         return state_1 -> contains(s) && state_2 -> contains(s);
//     }
// };


class ProbabilityTest {
private:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;
    
public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count): seed(seed), test_min(test_min),test_max(test_max), test_count(test_count) { }
    
    float operator()(State const &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;
        
        return static_cast<float>(good)/static_cast<float>(test_count);
    }
};

int main(int argc, const char * argv[]) {
    DiscreteState d(1);
    SegmentState s(0,10);
    SetState ss({1, 3, 5, 7});
    SegmentStateWithGaps  ssw(0, 10, {1, 2, 3, 4, 5, 8});
    SegmentStateWithAdds  ssa(0, 10, {1, 2, 3, 4, 5, 8});
    SegmentStateWithGapsAndAdds ssga(0, 10, {1, 6, 6, 1}, {8, 1, 3, 6, 3});
    ProbabilityTest pt(19, 0, 100, 10000000);
    std::cout << pt(d) << std::endl;
    std::cout << pt(s) << std::endl;
    std::cout << pt(ss) << std::endl;
    std::cout << pt(ssw) << std::endl;
    std::cout << pt(ssa) << std::endl;
    return 0;
}