#include<vector>
#include<set>
#include<iostream>

using namespace std;
/**
* 中值算法来自https://blog.51cto.com/u_15302258/3086800
vector<unsigned char> medianSlidingWindow(vector<unsigned char>& nums, int k) {
    vector<unsigned char> res;
    multiset<double> st;
    for (int i = 0; i < nums.size(); ++i) {
        if (st.size() >= k) st.erase(st.find(nums[i - k]));
        st.insert(nums[i]);
        if (i >= k - 1) {
            auto mid = st.begin();
            std::advance(mid, k / 2);
            res.push_back((*mid + *prev(mid, (1 - k % 2))) / 2);
            cout << "wow:" << (int)(*mid + *prev(mid, (1 - k % 2))) / 2 << endl;
        }
    }
    return res;
}
int main()
{
    cout << "hello?" << endl;
    vector<unsigned char> test{ 1,1,4,5,1,4,1,9,1,9,8,1,0 };
    vector<unsigned char> res = medianSlidingWindow(test, 3);
    cout << "test:" << test.size();
    cout << "res:" << res.size();
    for (vector<unsigned char>::iterator iter = test.begin(); iter != test.end(); iter++)
    {
        cout << (int)*iter << " ";
    }
    for (vector<unsigned char>::iterator iter = res.begin(); iter != res.end(); iter++)
    {
        cout << (int)*iter << " ";
    }
    getchar();
    return 0;
}
*/