
#include <map>
#include <vector>
using namespace std;

#define frequencyMap map<string, pair<int, int> >

extern frequencyMap load_ccv_freqs_map(const string file_name);
extern vector<pair<bool, vector<string>> > load_ccv_test(const string file_name);
