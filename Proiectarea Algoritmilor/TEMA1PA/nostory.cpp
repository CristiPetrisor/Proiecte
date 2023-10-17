#include <cstdint>
#include <iostream>
#include <algorithm>

using namespace std;

int a[100001], b[100001], max[100001], min[100001];

int getpos(int64_t max[], int64_t x, int n)
{

    for (int i = 0; i < n; i++)
    {
        if (max[i] > x)
            return i;
    }
    return -1;
}

int64_t SolveTask(int a[], int b[], int n, int moves)
{

    sort(a + 0, a + n);
    sort(b + 0, b + n);

    int64_t s = 0;
    int k = 0;
    int j = n - 1;
    for (int i = n - 1; i >= k; i--)
    {
        while (moves != 0 && b[j] > a[i])
        {
            s += b[j];
            j--;
            moves--;
            k++;
        }
        if (k > i)
            break;
        s += a[i];
    }

    return s;
}

int main()
{

    int n, moves;

    cin >> n >> moves;

    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];

    int res = SolveTask(a, b, n, moves);
    cout << res << "\n";
    return 0;
}
