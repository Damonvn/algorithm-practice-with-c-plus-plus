/* =============
Exercise - Find the smallest substring:

Given two strings S1 and S2. Your task is to find the smallest substring of
S1 that contains all the characters of S2. If there is no substring satisfying
the problem's requirements, please output -1

T, S1, S2 satisfy the constraints: 1 ≤ T ≤ 100; 1 ≤ Length(S1), Length(S2) ≤ 100

Example:

Input:
timetopractice
toc
Output:
toprac

Input:
timetopractice
ttoc
Output:
topract

Input:
timetopracticeoct
toc
Output:
oct

============= */

#include <iostream>
#include <string>

using namespace std;

int main()
{
    int t;
    cin >> t;
    cin.ignore();
    while (t--)
    {
        string s1, s2;
        cout << "Input: " << endl;
        getline(cin, s1);
        getline(cin, s2);
        int c1[256] = {0}, c2[256] = {0};
        for (char x : s2)
        {
            c2[x]++;
        }
        int cnt = 0, left = 0, ans = INT_MAX, index = -1;
        for (int i = 0; i < s1.length(); i++)
        {
            c1[s1[i]]++;
            if (c1[s1[i]] <= c2[s1[i]])
            {
                cnt++;
            }
            if (cnt == s2.length())
            {
                while (c1[s1[left]] > c2[s1[left]])
                {
                    c1[s1[left]]--;
                    ++left;
                }
                if (ans > i - left + 1)
                {
                    ans = i - left + 1;
                    index = left;
                }
                --cnt;
                c1[s1[left]]--;
                ++left;
            }
        }
        cout << "Output: " << endl;
        if (ans == INT_MAX)
        {
            cout << "-1" << endl;
        }
        else
        {
            for (int i = index; i < index + ans; i++)
            {
                cout << s1[i];
            }
            cout << endl;
        }
        cout << "===============" << endl;
    }

    return 0;
}
