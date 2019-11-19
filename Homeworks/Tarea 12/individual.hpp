#include <vector>

using namespace std;

class Individual {
    private:
        vector<bool> genome;
    public:
        Individual(unsigned int size, bool ramdonize=true);
        Individual(vector<bool> gnome);
        Individual(unsigned int size, bool ramdonize=true);
        ~Individual();

        vector<bool> get_genome();
        unsigned int get_size();

};
