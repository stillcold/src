#include "mystatus.h"
#include "mytypes.h"
#include "mytools.h" /* get_random_number */

#include <math.h> /* cos(x) & exp(x) */

/**************************************************************************
 *
 * Copyright (c) 2013 Chao Guan (mr_kernel@163.com)
 * All rights reserved.
 *
 * This is the so called "BP" algorithm, an artificial network algorithm
 * with feed back network.
 *
 * In this code, y = cos(x) is the target functon to be simualted.
 *
 *************************************************************************/

/**************************************************************************
 *
 * I will put all define variables here instead of head files, this file
 * will NOT be used by other files or programs.
 *
 *************************************************************************/
#define NUM_OF_INPUT_NODE   1 /* Number of input nodes */
#define NUM_OF_INVISIBLE_NODE   9 /* Number of invisible nodes */
#define NUM_OF_OUTPUT_NODE  1 /* Number of output nodes */
#define SCALE_OF_SAMPLE     100
#define STEP_OF_SAMPLE      0.01

/* Program will be terminated when difference smaller than this value*/
#define TARGET_ERROR_VALUE  0.02
#define MAX_LOOP_TIMES      10000
#define e                   2.718

double sum_of_erroe_per_round;
double coefficient_of_incentive_function;
double coefficient_of_modify_function;
double weight_level_1[NUM_OF_INPUT_NODE][NUM_OF_INVISIBLE_NODE];
double weight_level_2[NUM_OF_INVISIBLE_NODE][NUM_OF_OUTPUT_NODE];

/* To modify weight_level_1 and weight_level_2 */
double delta_level_1[NUM_OF_INPUT_NODE][NUM_OF_INVISIBLE_NODE];
double delta_level_2[NUM_OF_INVISIBLE_NODE][NUM_OF_OUTPUT_NODE];

/* The delta value of last round */
double delta_level_1_last[NUM_OF_INVISIBLE_NODE][NUM_OF_OUTPUT_NODE];
/* Notice here */
double delta_level_2_last[NUM_OF_INPUT_NODE][NUM_OF_OUTPUT_NODE];
double rate_level_1[NUM_OF_INPUT_NODE][NUM_OF_INVISIBLE_NODE];
double rate_level_2[NUM_OF_INVISIBLE_NODE][NUM_OF_OUTPUT_NODE];

/* Input value for each node */
double input_for_input_node[SCALE_OF_SAMPLE][NUM_OF_INPUT_NODE];
double input_for_invisible_node[SCALE_OF_SAMPLE][NUM_OF_INVISIBLE_NODE];
double input_for_output_node[SCALE_OF_SAMPLE][NUM_OF_OUTPUT_NODE];

/* Desired output value of the network */
double desired_output_of_network[SCALE_OF_SAMPLE][NUM_OF_OUTPUT_NODE];

/* Real output of some node */
double real_output_of_invisible_node[SCALE_OF_SAMPLE][NUM_OF_INVISIBLE_NODE];
double real_output_of_output_node[SCALE_OF_SAMPLE][NUM_OF_OUTPUT_NODE];

/* Diff of node, the delta above is for weight */
double delta_invisible_node[SCALE_OF_SAMPLE][NUM_OF_INVISIBLE_NODE];
double delta_output_node[SCALE_OF_SAMPLE][NUM_OF_OUTPUT_NODE];

STATUS initiate(void);
STATUS train(void);
STATUS get_delta(void);
STATUS modify(void);
STATUS proceed(void);
double new_rate(double original_rate, double guard);
double incentive_function(double fan_in);
double get_differential_coefficient(double fan_in);

/**************************************************************************
 *
 * Set weight for each level(not node).
 * Set delta for level above.
 * Set learning rate.
 * Get original sample to train the network.
 *
 *************************************************************************/

STATUS initiate(void){
    register u32            i;
    register u32            j;

    for (j = 0; j < NUM_OF_INVISIBLE_NODE; j++){
        for (i = 0; i < NUM_OF_INPUT_NODE; i++){
            /* (-50, 50) / 100 -> (-0.5, 0.5)*/
            weight_level_1[i][j] = (get_random_number(100) - 50) * 0.01;
            delta_level_1[i][j] = delta_level_1_last[i][j] = 0;
            rate_level_1[i][j] = 0.01;
        }
        for (i = 0; i < NUM_OF_OUTPUT_NODE; i++){
            /* (-50, 50) / 100 -> (-0.5, 0.5)*/
            weight_level_2[i][j] = (get_random_number(100) - 50) * 0.01;
            delta_level_2[i][j] = delta_level_2_last[i][j] = 0;
            rate_level_2[i][j] = 0.01;
        }
    }
    for (i = 0; i < SCALE_OF_SAMPLE; i++){
        j = 0;
        /* for (j = 0; j < NUM_OF_INPUT_NODE; j++) , j has only one value - 0 */
        input_for_input_node[i][j] = i * STEP_OF_SAMPLE;
        /* for (j = 0; j < NUM_OF_OUTPUT_NODE; j++) , j has only one value - 0 */
        desired_output_of_network[i][j] = cos (input_for_input_node[i][j]);
    }

    return STATUS_OK;
}


/**************************************************************************
 *
 * Step 1: preparation stage.
 *      get the output of invisible level node and output node.
 * Step 2: the last and most impossible stage.
 *      get the sum of error per round.
 *
 *************************************************************************/

STATUS train(void){
    register u32            i;
    register u32            j;
    register u32            k;

    sum_of_erroe_per_round = 0;

    for (i = 0; i < SCALE_OF_SAMPLE; i++){
        for (j = 0; j < NUM_OF_INVISIBLE_NODE; j++){
            for (k = 0; k < NUM_OF_INPUT_NODE; k++){
                input_for_invisible_node[i][j] =
                    input_for_input_node[i][k] * weight_level_1[k][j];
            }
            real_output_of_invisible_node[i][j] =
                incentive_function(input_for_invisible_node[i][j]);
        }
        for (j = 0; j < NUM_OF_OUTPUT_NODE; j++){
            for (k = 0; k < NUM_OF_INVISIBLE_NODE; k++){
                input_for_output_node[i][j] =
                    real_output_of_invisible_node[i][k] *
                    weight_level_2[k][j];
            }
            real_output_of_output_node[i][j] =
                incentive_function(input_for_output_node[i][j]);
            sum_of_erroe_per_round +=
                (real_output_of_output_node[i][j] -
                 desired_output_of_network[i][j])
                *
                (real_output_of_output_node[i][j] -
                 desired_output_of_network[i][j])
                * 0.5;
        }
    }

    return STATUS_OK;
}


/**************************************************************************
 *
 * Get delta of invisible node and output node.
 *
 * This is the key step of BP: get the diff of each node( not just its 
 * output, but the output and then multiply by a differencial coefficient)
 *
 *************************************************************************/

STATUS get_delta(void){
    register u32            i;
    register u32            j;
    register u32            k;

    for (i = 0; i < SCALE_OF_SAMPLE; i++){
        for (j = 0; j < NUM_OF_OUTPUT_NODE; j++){

            /* Target 1, the code is a little complex. ^_^ */
            delta_output_node[i][j] = (desired_output_of_network[i][j] -
                    real_output_of_output_node[i][j])
                * get_differential_coefficient(
                        real_output_of_output_node[i][j]);
        }
        for (j = 0; j < NUM_OF_INVISIBLE_NODE; j++){
            for (k = 0; k < NUM_OF_OUTPUT_NODE; k++){
                delta_invisible_node[i][j] = delta_output_node[i][k] *
                    weight_level_2[k][j];
            }
            /* Target 2 */
            delta_invisible_node[i][j] = get_differential_coefficient(
                    real_output_of_invisible_node[i][j]);
        }
    }

    return STATUS_OK;
}


/**************************************************************************
 *
 * Modify the weight.
 *
 * Well, I can't understand why somebody init the variables every time
 * before use them. And he does this without using memset. I can't repeat
 * that operation if I can't agree with it, but if there are any bugs, this
 * may be the reason.
 *
 *************************************************************************/

STATUS modify(void){
    register u32            i;
    register u32            j;
    register u32            k;
    double                  guard;

    /* Modify the weight of level 1 */
    for (i = 0; i < NUM_OF_INPUT_NODE; i++){
        for (j = 0; j < NUM_OF_INVISIBLE_NODE; j++){
            for (k = 0; k < SCALE_OF_SAMPLE; k++){
                delta_level_1[i][j] = input_for_input_node[k][i] *
                    delta_invisible_node[k][j];
            }
            guard = delta_level_1[i][j] * delta_level_1_last[i][j];
            rate_level_1[i][j] = new_rate(rate_level_1[i][j], guard);
            
            /* This is what we talking about */
            weight_level_1[i][j] = weight_level_1[i][j] +
                rate_level_1[i][j] * (coefficient * delta_level_1[i][j] +
                        (1 - coefficient) * delta_level_1_last[i][j]);
            delta_level_1_last[i][j] = delta_level_1[i][j];
        }
    }

    /* Modify level 2 */
    for (i = 0; i < NUM_OF_INVISIBLE_NODE; i++){
        for (j = 0; j < NUM_OF_OUTPUT_NODE; j++){
            for (k = 0; k < SCALE_OF_SAMPLE; k++){
                delta_level_2[i][j] = real_output_of_invisible_node[k][i] *
                    delta_output_node[k][j];
            }
            guard = delta_level_2[i][j] * delta_level_2_last[i][j];
            rate_level_2[i][j] = new_rate(rate_level_2[i][j], guard);
            
            /* This is what we talking about */
            weight_level_2[i][j] = weight_level_2[i][j] +
                rate_level_2[i][j] * (coefficient * delta_level_2[i][j] +
                        (1 - coefficient) * delta_level_2_last[i][j]);
            delta_level_2_last[i][j] = delta_level_2[i][j];
        }
    }
}


/**************************************************************************
 *
 * Step 1: preparation stage.
 *      get the output of invisible level node and output node.
 * Step 2: the last and most impossible stage.
 *      get the sum of error per round.
 *
 *************************************************************************/

double proceed(double fan_in){
    register u32            j;
    register u32            k;

    for (j = 0; j < NUM_OF_INVISIBLE_NODE; j++){
        for (k = 0; k < NUM_OF_INPUT_NODE; k++){
            input_for_invisible_node[0][j] = fan_in * weight_level_1[k][j];
        }
        real_output_of_invisible_node[0][j] =
            incentive_function(input_for_invisible_node[0][j]);
    }
    for (j = 0; j < NUM_OF_OUTPUT_NODE; j++){
        for (k = 0; k < NUM_OF_INVISIBLE_NODE; k++){
            input_for_output_node[0][j] =
                real_output_of_invisible_node[0][k] *
                weight_level_2[k][j];
        }
    }

    return incentive_function(input_for_output_node[0][0]);
}

/**************************************************************************
 *
 * Get the new rate. i.e, the modify range for the weight.
 * guard: to check if the output of the network of this time and last time
 * both larger or smaller than the desired output. i.e, if this time and
 * last time have the same direction. If it is, it means we should have
 * a larger modify range. 
 *
 *************************************************************************/

double new_rate(double original_rate, double guard){
    if (guard == 0)
        return original_rate;

    if (guard > 0)
    {
        if (original_rate < 0.04)
            original_rate *= 2;
        else
            original_rate = 0.08;
    } else {
        if (original_rate > 0.02)
            original_rate /= 2;
        else
            original_rate = 0.01;
    }
    return original_rate;
}


/**************************************************************************
 *
 * Use the Fan In to get the Fan Out.
 * f(d) = 1 / 1+exp(-u*d).  Note: (u > 0)
 *
 *************************************************************************/

double incentive_function(double fan_in){
    double                  ret;

    ret = -(fan_in * coefficient);
    ret = exp (ret);
    ret = 1 / (ret + 1);
    return ret;
}


/**************************************************************************
 *
 * Get the differencial coefficient of incentive_function.
 *
 *************************************************************************/

double get_differential_coefficient(double fan_in){
    return coefficient * fan_in * (1 - fan_in);
}
