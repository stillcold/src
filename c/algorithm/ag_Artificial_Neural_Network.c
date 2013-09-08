#include "myalgorithm.h"
#include "mystatus.h"
#include "mytypes.h"
#include "mytools.h" /* get_random_number */

#include <math.h> /* cos(x) & exp(x) */

/**************************************************************************
 *
 * Copyright (c) 2013 Chao Guan (mr_kernel@163.com)
 * All rights reserved.
 *
 * This is the so called "BP" algorithm, an artificial neural network
 * algorithm with feed back network.
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
#define NUM_OF_INVISIBLE_NODE   4 /* Number of invisible nodes */
#define NUM_OF_OUTPUT_NODE  1 /* Number of output nodes */
#define SCALE_OF_SAMPLE     100
#define STEP_OF_SAMPLE      0.01

double sum_of_error_per_round;
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


/**************************************************************************
 *
 * Set weight for each level(not node).
 * Set delta for level above.
 * Set learning rate.
 * Get original sample to train_neural_network the network.
 *
 *************************************************************************/

STATUS initiate_neural_network(void){
    register u32            i;
    register u32            j;

    coefficient_of_incentive_function = 1;
    coefficient_of_modify_function = 1;
    for (i = 0; i < NUM_OF_INVISIBLE_NODE; i++){
        for (j = 0; j < NUM_OF_INPUT_NODE; j++){
            weight_level_1[j][i] = (get_random_number(100) - 50) * 0.01;
            delta_level_1_last[j][i] = 0;
            delta_level_1[j][i] = 0;
            rate_level_1[j][i] = 0.01;
        }
        for (j = 0; j < NUM_OF_OUTPUT_NODE; j++){
            weight_level_2[i][j] = (get_random_number(100) - 50) * 0.01;
            delta_level_2_last[i][j] = 0;
            delta_level_2[i][j] = 0;
            rate_level_2[i][j] = 0.01;
        }
    }
    for (i = 0; i < SCALE_OF_SAMPLE; i++){
        input_for_input_node[i][0] = i * STEP_OF_SAMPLE;
        desired_output_of_network[i][0] = cos(input_for_input_node[i][0]);
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

STATUS train_neural_network(void){
    register u32            i;
    register u32            j;
    register u32            k;

    sum_of_error_per_round = 0;
    for (i = 0; i < SCALE_OF_SAMPLE; i++){
        for (j = 0; j < NUM_OF_INVISIBLE_NODE; j++){
            input_for_invisible_node[i][j] = 0;
            for (k=0; k<NUM_OF_INPUT_NODE; k++){
                input_for_invisible_node[i][j] +=input_for_input_node[i][k]
                    * weight_level_1[k][j];
            }
            real_output_of_invisible_node[i][j] = incentive_function(
                    input_for_invisible_node[i][j]);
        }
        for (j = 0; j < NUM_OF_OUTPUT_NODE; j++){
            input_for_output_node[i][j] = 0;
            for (k = 0; k < NUM_OF_INVISIBLE_NODE; k++){
                input_for_output_node[i][j] +=
                    real_output_of_invisible_node[i][k] *
                    weight_level_2[k][j];
            }
            real_output_of_output_node[i][j] = incentive_function(
                    input_for_output_node[i][j]);
            sum_of_error_per_round = sum_of_error_per_round + (
                    real_output_of_output_node[i][j] -
                    desired_output_of_network[i][j]) * 
                (real_output_of_output_node[i][j] -
                 desired_output_of_network[i][j] ) / 2;
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
            delta_output_node[i][j] = (desired_output_of_network[i][j] - 
                    real_output_of_output_node[i][j]) *
                get_differential_coefficient(
                        real_output_of_output_node[i][j]);
        }
        for (j = 0; j < NUM_OF_INVISIBLE_NODE; j++){
            delta_invisible_node[i][j] = 0;
            for (k = 0; k < NUM_OF_OUTPUT_NODE; k++){
                delta_invisible_node[i][j] = delta_output_node[i][k] *
                    weight_level_2[j][k] + delta_invisible_node[i][j];
            }
            delta_invisible_node[i][j] = delta_invisible_node[i][j] *
                get_differential_coefficient(
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

STATUS modify_network_weight(void){
    register u32            i;
    register u32            j;
    register u32            k;
    double                  guard;

    for (i = 0; i < NUM_OF_INVISIBLE_NODE; i++){
        for (j = 0; j < NUM_OF_INPUT_NODE; j++){
            delta_level_1[j][i] = 0;
        }
        for (j = 0; j < NUM_OF_OUTPUT_NODE; j++){
            delta_level_2[i][j] = 0;
        }
    }

    /* Modify the weight of level 1 */
    for (i = 0; i < NUM_OF_INPUT_NODE; i++){
        for (j = 0; j < NUM_OF_INVISIBLE_NODE; j++){
            for (k = 0; k < SCALE_OF_SAMPLE; k++){
                delta_level_1[i][j] = delta_invisible_node[k][j] *
                    input_for_input_node[k][i] + delta_level_1[i][j];
            }
            guard = delta_level_1[i][j] * delta_level_1_last[i][j];
            rate_level_1[i][j] = new_rate(rate_level_1[i][j] , guard);
            weight_level_1[i][j] = weight_level_1[i][j] +
                rate_level_1[i][j] * (coefficient_of_modify_function *
                        delta_level_1[i][j] +
                        (1 - coefficient_of_modify_function) *
                        delta_level_1_last[i][j] );
            delta_level_1_last[i][j] = delta_level_1[i][j];
        }
    }

    /* Modify the weight of level 2 */
    for (i = 0; i < NUM_OF_INVISIBLE_NODE; i++){
        for (j = 0; j < NUM_OF_OUTPUT_NODE; j++){
            for (k = 0; k < SCALE_OF_SAMPLE; k++){
                delta_level_2[i][j] = delta_output_node[k][j] *
                    real_output_of_invisible_node[k][i] +
                    delta_level_2[i][j];
            }

            guard = delta_level_2[i][j] * delta_level_2_last[i][j];
            rate_level_2[i][j] = new_rate(rate_level_2[i][j] , guard);
            weight_level_2[i][j] = weight_level_2[i][j] +
                rate_level_2[i][j] * (coefficient_of_modify_function *
                        delta_level_2[i][j] +
                        (1 - coefficient_of_modify_function) *
                        delta_level_2_last[i][j]);
            delta_level_2_last[i][j] = delta_level_2[i][j];
        }
    }

    return STATUS_OK;
}


/**************************************************************************
 *
 *
 *************************************************************************/

double proceed(double fan_in){
    register u32            j;
    register u32            k;

    input_for_input_node[0][0] = fan_in;

    for (j = 0; j < NUM_OF_INVISIBLE_NODE; j++){
        input_for_invisible_node[0][j] = 0;
        for (k = 0; k < NUM_OF_INPUT_NODE; k++){
            input_for_invisible_node[0][j] = input_for_input_node[0][k] *
                weight_level_1[k][j] + input_for_invisible_node[0][j];
        }
        real_output_of_invisible_node[0][j] = incentive_function(
                input_for_invisible_node[0][j]);
    }

    for (j = 0; j < NUM_OF_OUTPUT_NODE; j++){
        input_for_output_node[0][j] = 0;
        for (k = 0; k < NUM_OF_INVISIBLE_NODE; k++){
            input_for_output_node[0][j] =
                real_output_of_invisible_node[0][k] * weight_level_2[k][j]
                + input_for_output_node[0][j];
        }
        real_output_of_output_node[0][j] = incentive_function(
                input_for_output_node[0][j]);
    }

    return real_output_of_output_node[0][0];
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
    if (guard > 0){
        if (original_rate < 0.04)
            original_rate = original_rate * 2;
        else original_rate = 0.08;
    }
    else if (guard < 0){
        if (original_rate >= 0.02){
            original_rate = original_rate / 2;
        }
        else original_rate = 0.01;
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

    ret = -(fan_in * coefficient_of_incentive_function);
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
    return coefficient_of_incentive_function * fan_in * (1 - fan_in);
}
