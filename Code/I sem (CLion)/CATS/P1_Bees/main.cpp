#include <fstream>
using namespace std;

int main()
{
    ifstream fin ("input.txt");
    ofstream fout ("output.txt");

    int N; fin >> N;

    int massPoles[N];
    for (int i = 0; i < N; i++)
    {
        fin >> massPoles[i];
    }

    int max_sum = 0, Lindex, Mindex, Rindex;

    for (int i = 0; i < N - 1; i++)
    {
        int rbuf = i, mbuf = i, M_sum = massPoles[i], R_sum = 0;

        while (rbuf < N)
        {

            if (M_sum < R_sum)
            {
                mbuf++;
                M_sum += massPoles[mbuf];
                R_sum -= massPoles[mbuf];
            }

            else
            {
                rbuf++;
                R_sum += massPoles[rbuf];
            }

            if ((M_sum == R_sum) and (M_sum > max_sum))
            {
                max_sum = M_sum;

                Lindex = i + 1;
                Mindex = mbuf + 1;
                Rindex = rbuf + 1;
                // cout(max_sum); cout(" "); cout(Lindex); cout(" "); cout(Mindex); cout(" "); cout(Rindex);
            }
        }
    }

    if (max_sum)
    {
        fout << Lindex << " " << Mindex << " " << Rindex;
    }
    else
    {
        fout << -1;
    }
}
