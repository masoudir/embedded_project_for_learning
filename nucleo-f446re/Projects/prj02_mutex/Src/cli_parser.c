/**
  ******************************************************************************
  * @file           : cli_parser.c
  * @brief          : CLI parser functions
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "cli_parser.h"

bool is_app_ledblink_running;
bool is_app_game01_running = false;
bool is_app_acc_running = false;

bool* is_app_running[CLI_PARSER_MAX_NUMBER_OF_APPS];

cli_parser_words_t cli_parser_total_cmd;
cli_parser_words_t cli_parser_part[CLI_PARSER_MAX_NUMBER_OF_WORDS];

unsigned int cli_parser_last_word_index = 0;
unsigned int cli_parser_word_order = 0;

// APPLICATION name list
cli_parser_words_t cli_parser_app_list[CLI_PARSER_MAX_NUMBER_OF_APPS] = {0};
cli_parser_words_t cli_parser_cmd_list[CLI_PARSER_MAX_NUMBER_OF_CMDS] = {0};
cli_parser_words_t cli_parser_tag_list[CLI_PARSER_MAX_NUMBER_OF_TAGS] = {0};



static void cli_parser_reset_buf(cli_parser_words_t* input) {
    input->length = 0;
    for( unsigned int i = 0; i < CLI_PARSER_MAX_LENGTH_FOR_CMD; i++) {
        input->buf[i] = 0;
    }
}

static void cli_parser_reset() {
    cli_parser_reset_buf(&cli_parser_total_cmd);
    for(unsigned int i = 0; i < CLI_PARSER_MAX_NUMBER_OF_WORDS; i++) {
        cli_parser_reset_buf(&cli_parser_part[i]);
    }
    cli_parser_last_word_index = 0;
    cli_parser_word_order = 0;
}

static cli_parser_return_t cli_parser_add_char(cli_parser_words_t* array, char c) {
    if(array != NULL) {
        if(c != '\r' && c != '\n' ) {
            if(array->length < CLI_PARSER_MAX_LENGTH_FOR_CMD) {
                if(c != 0 ) {
                    array->buf[array->length++] = c; // buf[index++] = c    
                }
                return CLI_PARSER_CHAR_ADDED_SUCCESSFULLY;
            }
            return CLI_PARSER_MAX_LENGTH_REACHED;
        }
        return CLI_PARSER_SPECIAL_CHAR_DETECTED;
    }
    return CLI_PARSER_ERROR;
}

static cli_parser_return_t cli_parser_add_string(cli_parser_words_t* array, char *string, unsigned int size) {
    if(array != NULL ) {
        if(size < CLI_PARSER_MAX_LENGTH_FOR_CMD) {
            for(unsigned int i = 0; i < size; i++) {
                cli_parser_return_t status = cli_parser_add_char(array, string[i]);
                if(status != CLI_PARSER_CHAR_ADDED_SUCCESSFULLY) {
                    return status;
                }
            }
            return CLI_PARSER_CHAR_ADDED_SUCCESSFULLY;
        }
        return CLI_PARSER_MAX_LENGTH_REACHED;
    }
    return CLI_PARSER_ERROR;
}

void cli_parser_init() {
    cli_parser_reset();
    
    cli_parser_add_string(&cli_parser_app_list[CLI_PARSER_APP_LEDBLINK_INDEX], CLI_PARSER_APP_LEDBLINK_NAME, 8); //ledblink
    cli_parser_add_string(&cli_parser_app_list[CLI_PARSER_APP_GAME01_INDEX], CLI_PARSER_APP_GAME01_NAME, 6); //game01
    cli_parser_add_string(&cli_parser_app_list[CLI_PARSER_APP_ACC_INDEX], CLI_PARSER_APP_ACC_NAME, 13); //ACC
    
    cli_parser_add_string(&cli_parser_cmd_list[CLI_PARSER_CMD_APP_INDEX], CLI_PARSER_APP_COMMAND, 3); //app
    cli_parser_add_string(&cli_parser_cmd_list[CLI_PARSER_CMD_READ_INDEX], CLI_PARSER_READ_COMMAND, 4); //read
    cli_parser_add_string(&cli_parser_cmd_list[CLI_PARSER_CMD_WRITE_INDEX], CLI_PARSER_WRITE_COMMAND, 5); //write
    cli_parser_add_string(&cli_parser_cmd_list[CLI_PARSER_CMD_HELP_INDEX], CLI_PARSER_HELP_COMMAND, 4); //help
    
    cli_parser_add_string(&cli_parser_tag_list[CLI_PARSER_TAG_ENABLE_INDEX], CLI_PARSER_ENABLE_TAG, 6); //enable
    cli_parser_add_string(&cli_parser_tag_list[CLI_PARSER_TAG_DISABLE_INDEX], CLI_PARSER_DISABLE_TAG, 7); //disable
    cli_parser_add_string(&cli_parser_tag_list[CLI_PARSER_TAG_ON_INDEX], CLI_PARSER_ON_TAG, 2); //on
    cli_parser_add_string(&cli_parser_tag_list[CLI_PARSER_TAG_OFF_INDEX], CLI_PARSER_OFF_TAG, 3); //off
    cli_parser_add_string(&cli_parser_tag_list[CLI_PARSER_TAG_LIST_INDEX], CLI_PARSER_LIST_TAG, 4); //list
    
    is_app_running[CLI_PARSER_APP_LEDBLINK_INDEX] = &is_app_ledblink_running;
    is_app_running[CLI_PARSER_APP_GAME01_INDEX] = &is_app_game01_running;
    is_app_running[CLI_PARSER_APP_ACC_INDEX] = &is_app_acc_running;
}
/*
static int cli_parser_compare_text(char* str1, char* str2, unsigned int size) {
    return strncmp(str1, str2, size);
}*/


static cli_parser_compare_word_output_t cli_parser_compare_words(cli_parser_words_t word1, cli_parser_words_t word2) {
    if(word1.length == word2.length) {
        if(strncmp(word1.buf, word2.buf, word1.length) == 0) {
            return CLI_PARSER_CMP_TEXT_EQUAL;
        }
    }
    return CLI_PARSER_CMP_TEXT_DIFFERENT;
}


static bool cli_parser_is_first_word_this_cmd(cli_parser_cmd_index_t cmd_index) {
    return (cli_parser_compare_words(cli_parser_part[0], cli_parser_cmd_list[cmd_index]) == CLI_PARSER_CMP_TEXT_EQUAL);
}

static bool cli_parser_is_second_word_related_to_this_app(cli_parser_app_index_t app_index) {
    return (cli_parser_compare_words(cli_parser_part[1], cli_parser_app_list[app_index]) == CLI_PARSER_CMP_TEXT_EQUAL);
}

static bool cli_parser_is_second_word_related_to_this_tag(cli_parser_tag_index_t tag_index) {
    return (cli_parser_compare_words(cli_parser_part[1], cli_parser_tag_list[tag_index]) == CLI_PARSER_CMP_TEXT_EQUAL);
}

static bool cli_parser_is_third_word_related_to_this_tag(cli_parser_tag_index_t tag_index) {
    return (cli_parser_compare_words(cli_parser_part[2], cli_parser_tag_list[tag_index]) == CLI_PARSER_CMP_TEXT_EQUAL);
}

void cli_parser(char c) {
    cli_parser_return_t status = cli_parser_add_char(&cli_parser_total_cmd, c);
    
    switch(status) {
        case CLI_PARSER_MAX_LENGTH_REACHED:
            printf("ERROR: MAX LENGTH FOR CMD REACHED! \r\n");
        break;
        case CLI_PARSER_SPECIAL_CHAR_DETECTED:
            printf(">>> Command \"%s\" is going to be executed.\r\n", cli_parser_total_cmd.buf);
            
             cli_parser_add_string(&cli_parser_part[cli_parser_word_order],
                                      &cli_parser_total_cmd.buf[cli_parser_last_word_index],
                                      cli_parser_total_cmd.length - cli_parser_last_word_index);
                                      
                cli_parser_last_word_index = cli_parser_total_cmd.length;
    
                ++cli_parser_word_order;
            
            //int cmp1 = cli_parser_compare_text(cli_parser_part[0].buf, CLI_PARSER_APP_COMMAND, cli_parser_part[cli_parser_word_order].length);
            //if(cmp1 == 0) {printf("New Word is app");}

            if(cli_parser_is_first_word_this_cmd(CLI_PARSER_CMD_APP_INDEX)) {
                if(cli_parser_is_second_word_related_to_this_app(CLI_PARSER_APP_LEDBLINK_INDEX)) {
                    if(cli_parser_is_third_word_related_to_this_tag(CLI_PARSER_TAG_ENABLE_INDEX)) {
                         printf("your ledblink application is going to be executed\r\n");
                         is_app_ledblink_running = true;
                        
                    } else if (cli_parser_is_third_word_related_to_this_tag(CLI_PARSER_TAG_DISABLE_INDEX)) {
                        printf("your ledblink application is now stopped\r\n");
                        is_app_ledblink_running = false;
                    }
                }

                if(cli_parser_is_second_word_related_to_this_app(CLI_PARSER_APP_ACC_INDEX)) {
                    if(cli_parser_is_third_word_related_to_this_tag(CLI_PARSER_TAG_ENABLE_INDEX)) {
                         printf("your ledblink application is going to be executed\r\n");
                         is_app_acc_running = true;
                        
                    } else if (cli_parser_is_third_word_related_to_this_tag(CLI_PARSER_TAG_DISABLE_INDEX)) {
                        printf("your ledblink application is now stopped\r\n");
                        is_app_acc_running = false;
                    }
                }

                else if(cli_parser_is_second_word_related_to_this_app(CLI_PARSER_APP_GAME01_INDEX)) {
                    
                }
                else if(cli_parser_is_second_word_related_to_this_tag(CLI_PARSER_TAG_LIST_INDEX)) {
                    for(unsigned int j = 0; j < CLI_PARSER_APP_GAME01_INDEX + 1; j++) {
                        printf("app%d=%s\tis_running=%d\r\n", j, cli_parser_app_list[j].buf, *is_app_running[j]);
                    }
                    
                }
            } else if(cli_parser_is_first_word_this_cmd(CLI_PARSER_CMD_HELP_INDEX)) {
                    printf("\r\n");
                     printf("app list 	  --> to get the list of applications\r\napp <APP> enable  --> to enable <APP> \r\n app <APP> disable --> to disable <APP>\r\n");
                        
            }
            
            cli_parser_reset();
        break;
        case CLI_PARSER_CHAR_ADDED_SUCCESSFULLY:
            if(c == ' ') {
                cli_parser_add_string(&cli_parser_part[cli_parser_word_order],
                                      &cli_parser_total_cmd.buf[cli_parser_last_word_index],
                                      cli_parser_total_cmd.length - cli_parser_last_word_index - 1);
                                      
                cli_parser_last_word_index = cli_parser_total_cmd.length;
    
                ++cli_parser_word_order;
            }
        break;
        default:
        break;
    }

    
}
