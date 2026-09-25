#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define SIG_LEN 1000

typedef struct Complex{
    float real;
    float img;

} Complex;

float magnitude(Complex num) {
    return sqrtf(num.real * num.real + num.img * num.img);
}

float phase(Complex num) {
    return atan2f(num.img, num.real);
}

Complex* dft(int N, int* signal){
    Complex* sig_freq = malloc(sizeof *sig_freq * N);
    if (!sig_freq) return NULL;
    for(int k = 0; k < N; k++){
        sig_freq[k] = (Complex){0, 0};
        for(int n = 0; n < N; n++){
            float angle = 2.0f * M_PI * n * k / N;
            sig_freq[k].real += signal[n] * cosf(angle);
            sig_freq[k].img += signal[n] * -sinf(angle);
        }
    }

    return sig_freq;
}

int* gen_signal(int N){
    int* signal = malloc(sizeof(int) * N);
    if (!signal) return NULL;
    srand(time(0));
    for(int i = 0; i < N; i++){
        signal[i]= (random() % 256) - 127;
    }
    return signal;

}

void print_signal(int N, int* signal){
    for(int i = 0; i < N; i++){
        printf("%d\n", signal[i]);
    }
}

void print_dft_coord(int N, Complex* signal){
    for(int i = 0; i < N; i++){
        printf("%.2f + %.2fj\n", signal[i].real, signal[i].img);
    }
}

void print_dft_mag_phase(int N, Complex* signal){
    for(int i = 0; i < N; i++){
        printf("mag:%.2f pha:%.2f\n", magnitude(signal[i]), phase(signal[i]));
    }
}

int main(void){
    int* signal = gen_signal(SIG_LEN);
    Complex* dft_vec = dft(SIG_LEN, signal);
    print_dft_coord(SIG_LEN, dft_vec);
    free(signal);
    free(dft_vec);
    return 0;
}