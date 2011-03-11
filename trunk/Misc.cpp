#include "Misc.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


// find the sequence, the sum of which equals n, between 1 ~ n.
//
void find_sum_equals_n(int sum)
{
    // sum = n * (a1 + an) / 2 = n * a1 + n * (n - 1) / 2
    //     --> k = sum �C n * (n - 1) / 2
    //     --> a1 = k / n
    // a1 >= 1
    //     --> k > n

    int n = 1;                      // n �� 1 ��ʼ����
	int k = sum - n * (n - 1) / 2;  // k Ϊ sum �Cn * (n - 1)/2
    while (k > n) {
        // ��� k ���Ա� n ��������������� n �������������ܺ�Ϊ sum��
        if (k % n == 0) {
            int a1 = k / n;

            for (int i = 0; i < n; ++i) {
                printf("%d ", a1 + i);
            }

            printf("\n");
        }

        ++n;
		k = sum - n * (n - 1) / 2;
    }
}

// ����ˮ�ɻ���
//
void find_daffodils_number()
{
    const int cube[10] = {0, 1, 8, 27, 64, 125, 216, 343, 512, 729};

    printf("\nFind the daffodils number: ");

    int sum = 0;
    int t = 0;
    for (int i = 100; i < 1000; i++) {
        sum = 0;
        t = i;
        while (t) {
            sum += cube[t % 10];

            t /= 10;
        }

        if (sum == i) {
            printf("%d ", i);
        }
    }

    printf("\n");
}