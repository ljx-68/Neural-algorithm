#include "type.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
ErrorCode tfe_extract(TextFeatureExtractor *self, Sample *sample){
    if (sample == NULL || self == NULL) {
        return TFE_ERR_NULL_POINTER; 
    }
    if (self->X == NULL || sample->text == NULL) {
        return TFE_ERR_INVALID_TEXT;
    }
    double *T = self->X;
    for (int i = 0; i < self->vocab_size; i++){
        const char *word = self->vocab[i];
        int hit = (word && word[0] && strstr(sample->text, word) != NULL);
        *T = hit ? 1.0 : 0.0;
        T++;
    }
    return TFE_SUCCESS;
}
ErrorCode tfe_forward(TextFeatureExtractor *ext, NeuralNetwork *net){
    if (ext == NULL || net == NULL)
        return TFE_ERR_NULL_POINTER;
    if (ext->vocab_size <= 0 || ext->X == NULL)
        return TFE_ERR_INVALID_TEXT;
    if (net->W == NULL)
        return TFE_ERR_OUT_OF_MEMORY;
    double *a = net->Y;
    const double *c = net->W; 
    const double *x = ext->X;
    const double *b = net->B;
    
    for (int i = 0; i < 3; i++){
        a[i] = b[i];
    }
    for (int in = 0; in < ext->vocab_size; in++){
        for (int i = 0; i < 3; i++){
            a[i] += x[in] * c[in * 3 + i];
        }
    }
    return TFE_SUCCESS;
}
ErrorCode tfe_network_reset(TextFeatureExtractor *ext, NeuralNetwork *net, double number){
    if (ext == NULL || ext->vocab_size <= 0 || net == NULL) return TFE_ERR_NULL_POINTER;
    double *a = net->Y;
    double *b = net->B;
    double *c = net->W;
    const int w_size = net->in_dim * net->out_dim;
    for (int i = 0; i < 3; i++){
        a[i] = number;
        b[i] = number;
    }
    for (int i = 0; i < w_size; i++) {
        c[i] = ((double)rand() / RAND_MAX - 0.5) * 0.02; 
    }
    return TFE_SUCCESS;
}

ErrorCode tfe_backward(TextFeatureExtractor *ext, NeuralNetwork *net, double *Y_true, double lr){
    if (ext == NULL || net == NULL || Y_true == NULL) return TFE_ERR_NULL_POINTER;
    if (ext->X == NULL || net->W == NULL) return TFE_ERR_NULL_POINTER; 
    const double *y = net->Y;
    double *w = net->W;
    const double *x = ext->X;
    const int out_dim = net->out_dim;
    for (int i = 0; i < out_dim; i++) {
        double err = Y_true[i] - y[i]; 
        for (int in = 0; in < net->in_dim; in++) {
            w[in * out_dim + i] += lr * err * x[in];
        }
        net->B[i] += lr * err;
    }
    return TFE_SUCCESS;
}

