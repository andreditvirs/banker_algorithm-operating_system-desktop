#include <stdio.h>

int allocation[5][5], maxClaim[5][5], avl[5], need[5][5];
int alloc[5] = {0, 0, 0, 0, 0};
int maxRes[5], running[5], safe=0;
int count = 0, i, j, exec, resources, proses, k = 1;

int main()
{
    printf("\nMasukkan banyak jumlah proses : ");
    scanf("%d", &proses);

    for (i = 0; i < proses; i++) {
        running[i] = 1;
        count++;
    }

    printf("\nMasukkan banyaknya resources : ");
    scanf("%d", &resources);

    for (i = 0; i < resources; i++) {
        printf("\nMasukkan instant dari kelas resources %d : ", k++);
        scanf("%d", &maxRes[i]);
    }

    printf("\nMasukkan tabel Allocation :\n");
    for (i = 0; i < proses; i++) {
        for(j = 0; j < resources; j++) {
            printf("Allocation P%d dari kelas ke-%d : ",i,j+1);
            scanf("%d", &allocation[i][j]);
        }
        printf("\n");
    }

    printf("\nMasukan tabel Max :\n");
    for (i = 0; i < proses; i++) {
        for(j = 0; j < resources; j++) {
            printf("Max P%d dari kelas ke-%d : ",i,j+1);
            scanf("%d", &maxClaim[i][j]);
        }
        printf("\n");
    }

    printf("\nBanyaknya Resources : ");
    for (i = 0; i < resources; i++) {
        printf("\t%d", maxRes[i]);
    }

    printf("\nMatriks Allocation Resources :\n");
    for (i = 0; i < proses; i++) {
        for (j = 0; j < resources; j++) {
            printf("\t%d", allocation[i][j]);
        }

        printf("\n");
    }

    printf("\nMatriks Max Resources :\n");
    for (i = 0; i < proses; i++) {
        for (j = 0; j < resources; j++) {
            printf("\t%d", maxClaim[i][j]);
        }

        printf("\n");
    }

    printf("\nMatriks Need :\n");
    for (i = 0; i < proses; i++) {
        for (j = 0; j < resources; j++) {
            printf("\t%d", maxClaim[i][j] - allocation[i][j]);
        }

        printf("\n");
    }

    for (i = 0; i < proses; i++) {
        for (j = 0; j < resources; j++) {
            alloc[j] += allocation[i][j];
        }
    }

    printf("\nAllocated Resources :");
    for (i = 0; i < resources; i++) {
        printf("\t%d", alloc[i]);
    }

    for (i = 0; i < resources; i++) {
        avl[i] = maxRes[i] - alloc[i];
    }

    printf("\nAvailable resources:");
    for (i = 0; i < resources; i++) {
        printf("\t%d", avl[i]);
    }
    printf("\n");

    //prosedur pengurutan

    while (count != 0) {
        safe = 0;
        for (i = 0; i < proses; i++) {
            if (running[i]) {
                exec = 1;
                for (j = 0; j < resources; j++) {
                    if (maxClaim[i][j] - allocation[i][j] > avl[j]) {
                        exec = 0;
                        continue;
                    }
                }
                if (exec) {
                    printf("\nP%d merupakan proses yang sedang berjalan\n",i);
                    running[i] = 0;
                    count--;
                    safe = 1;

                    for (j = 0; j < resources; j++) {
                        avl[j] += allocation[i][j];
                    }
                    printf("\CHECK : Proses Aman (Tidak terjadi deadlock)");
                    printf("\nSafe Squenze-nya : ");

                    for (i = 0; i < resources; i++) {
                    printf("\t%d", avl[i]);
                    }

                    printf("\n");
                    continue;
                }
            }
        }
    }
}
