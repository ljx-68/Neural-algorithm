#include "type.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
ErrorCode tfe_network_init(NeuralNetwork *net, int in_dim, int out_dim)
{
    srand((unsigned)time(NULL));
    if (net == NULL) return TFE_ERR_NULL_POINTER;
    if (in_dim <= 0 || in_dim <= 0) return TFE_ERR_INVALID_ARG;
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

ErrorCode tfe_network_Sample(Sample *s, int Length, char *text_address, const double *vad){
    if (s == NULL || text_address == NULL) return TFE_ERR_NULL_POINTER;
    char *copy = (char*)malloc(strlen(text_address) + 1);
    if (copy == NULL) 
        return TFE_ERR_OUT_OF_MEMORY;
    strcpy(copy, text_address);
    s->Length = Length;
    double *G = s->VAD;
    if (vad == NULL) return TFE_ERR_INVALID_ARG;
    memcpy(s->VAD, vad, sizeof(s->VAD));
    return TFE_SUCCESS;
}

void tfe_network_free(Sample *net){
    if (net == NULL) return TFE_ERR_NULL_POINTER;
    free(net->text);
    net->text = NULL;
    net->Length = 0;
    const int len = sizeof(net->VAD) / sizeof(int);
    for (int i = 0; i < len; i++){
        net->VAD[i] = 0.0;
    } 
}