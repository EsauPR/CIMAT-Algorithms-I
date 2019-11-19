#include <vector.h>

using namespace std;

class Selection {
    private:
        template <typename Ind>
        double _h1_function_cost(Ind ind, double from=0.5, double to=10);
        template <typename Ind>
        double _h1_function_cost(Ind ind, double from=0.5, double to=10);

    protected:
        template <typename Ind>
        void select_best(vector<Ind> population, int f_cost_t);

    public:
        Selection();
        ~Selection();
        enum {
            _H1,
            _H2
        };

};
