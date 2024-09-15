#include "BMlow.h"


void BMlow::Init(){
    for (int i = 0; i < MWSPT_NSEC; ++i) {
            for (int j = 0; j < 2; ++j) {
                input_buffer[i][j] = 0.0;
                output_buffer[i][j] = 0.0;
            }
        }
}

float BMlow::Process(float in){
    float output = in;

        for (int i = 0; i < MWSPT_NSEC; ++i) {
            // Shift the old values in buffers
            for (int j = 1; j > 0; --j) {
                input_buffer[i][j] = input_buffer[i][j - 1];
                output_buffer[i][j] = output_buffer[i][j - 1];
            }

            // Store the new input
            input_buffer[i][0] = output;

            // Compute the new output for the current section
            float temp_output = 0.0;
            for (int j = 0; j < 2; ++j) {
                temp_output += NUM[i][j] * input_buffer[i][j];
                if (j > 0) {
                    temp_output -= DEN[i][j] * output_buffer[i][j];
                }
            }

            // Store the new output
            output_buffer[i][0] = temp_output;
            output = temp_output;
        }

        return output;
}