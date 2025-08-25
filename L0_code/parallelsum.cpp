#include <cstdio>
#include <pthread.h>
#include <vector>
using namespace std;

struct index_range {
    int* init_ptr;
    int inc;
};
void* partial_sum(void* idx_r) {
    int* init = (int*) ((index_range*) idx_r)->init_ptr;
    int inc = (int) ((index_range*) idx_r)->inc;
    int par_sum = 0;
    for (int i = 0; i < inc; i++) {
        par_sum += *(init + i);
    }
    pthread_exit((void*)par_sum);
}

int mt_arraysum(int* arr, int len, int th) {
    int res = 0;
    vector<pthread_t> tp(th);
    for (int i = 0; i < th; i++) {
        index_range idx_r = {
            arr + i * (len / th),
            (len / th),
        };
        pthread_create(&tp[i], NULL, partial_sum, (void*)&idx_r);
    }
    if (len % th != 0) {
        index_range idx_r = {
            arr + ((len / th)*th),
            (len % th),
        };
        pthread_create(&tp[th-1], NULL, partial_sum, (void*)&idx_r);
    }

    for (int i = 0; i < th; i++) {
        int* sum;
        pthread_join(tp[i], (void**)&sum);
        res += *sum;
    }
    return res;
}
int main() {
    int arr[10000];
    for (int i = 0; i < 10000; i++) {
        arr[i] = i;
    }
    printf("%d", mt_arraysum(arr, 10000, 10));
    return 0;
}