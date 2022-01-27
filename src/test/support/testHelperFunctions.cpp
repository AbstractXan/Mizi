using namespace std;
string printVector(vector<string> vec)
{
    string ret = "{";
    for (auto item : vec)
    {
        ret += "\"" + item + "\", ";
    }
    if (!vec.empty())
    {
        //remove extra `\", `
        ret.pop_back();
        ret.pop_back();
    }
    ret += "}";
    return ret;
}