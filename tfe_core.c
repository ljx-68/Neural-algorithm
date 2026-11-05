#include "type.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
ErrorCode tfe_network_init(NeuralNetwork *net, int in_dim, int out_dim)
{
    srand((unsigned)time(NULL));
    if (net == NULL) return TFE_ERR_NULL_POINTER;
    if (in_dim <= 0 || out_dim <= 0) return TFE_ERR_INVALID_ARG;
    if (out_dim != 3) return TFE_ERR_INVALID_ARG;

    double *W = (double*)calloc((size_t)in_dim * out_dim, sizeof(double));
    if (W == NULL) return TFE_ERR_OUT_OF_MEMORY;

    for (int i = 0; i < in_dim * out_dim; i++){
        W[i] = ((double)rand() / RAND_MAX - 0.5) * 0.02;
    }
    net->W = W;
    net->in_dim = in_dim;
    net->out_dim = out_dim;
    memset(net->B, 0, sizeof(net->B));
    memset(net->Y, 0, sizeof(net->Y));
    return TFE_SUCCESS;
}

void tfe_network_free(NeuralNetwork *net)
{
    if (net == NULL) return;
    free(net->W);
    net->W = NULL;
    net->in_dim  = 0;
    net->out_dim = 0;
}

ErrorCode tfe_sample_init(Sample *s, const char *text_address, const double *vad){
    if (s == NULL || text_address == NULL || vad == NULL) return TFE_ERR_NULL_POINTER;
    char *copy = (char*)malloc(strlen(text_address) + 1);
    if (copy == NULL) 
        return TFE_ERR_OUT_OF_MEMORY;
    strcpy(copy, text_address);

    s->text = copy;
    memcpy(s->VAD, vad, sizeof(s->VAD));
    return TFE_SUCCESS;
}

void tfe_sample_free(Sample *s){
    if (s == NULL) return;
    free((void *)s->text);
    s->text = NULL;
    memset(s->VAD, 0, sizeof(s->VAD));
}

ErrorCode tfe_TextFeatureExtractor_init(TextFeatureExtractor *T, const char **vocad, int vocad_size, double *X){
    if (T == NULL || vocad == NULL || X == NULL) return TFE_ERR_NULL_POINTER;
    if (vocad_size <= 0) return TFE_ERR_INVALID_ARG;
    
    for (int i = 0; i < vocad_size; i++){
        T->vocab[i] = vocad[i];
        T->X[i] = X[i];
    }

}