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
        return TFE_ERR_NULL_POINTER;
    const int out_dim = net->out_dim;
    for (int i = 0; i < out_dim; i++){
        net->Y[i] = net->B[i];
    }
    for (int in = 0; in < ext->vocab_size; in++){
        for (int i = 0; i < out_dim; i++){
            net->Y[i] += ext->X[in] * net->W[in * out_dim + i];
        }
    }
    return TFE_SUCCESS;
}
ErrorCode tfe_backward(TextFeatureExtractor *ext, NeuralNetwork *net, const double *Y_true, double lr){
    if (ext == NULL || net == NULL || Y_true == NULL) return TFE_ERR_NULL_POINTER;
    if (ext->X == NULL || net->W == NULL) return TFE_ERR_NULL_POINTER; 
    const double *y = net->Y;
    const int out_dim = net->out_dim;
    for (int i = 0; i < out_dim; i++) {
        double err = Y_true[i] - net->Y[i];
        for (int in = 0; in < net->in_dim; in++) {
            net->W[in * out_dim + i] += lr * err * ext->X[in];
        }
        net->B[i] += lr * err;
    }
    return TFE_SUCCESS;
}

