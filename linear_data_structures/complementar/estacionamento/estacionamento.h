#include "./array_queue.h"

void retira_veiculo(structures::ArrayQueue<int> *f, int k) {
    for (int i = 0; i < k; i++) {
        int removed = f -> dequeue();
        f -> enqueue(removed);
    }
}


void mantenha_veiculo(structures::ArrayQueue<int> *f, int k) {
    int keep;
    for (int i = 1; i <= k; i++) {
        if (i == k) {
            keep = f -> dequeue();
        } else {
            f -> dequeue();
        }
    }
    f -> clear();
    f -> enqueue(keep);
}



/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/
