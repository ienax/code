int is_whitespace(char c) { return c == ' ' || c == '\t' || c == '\n'; }
int string_count(char* str) {
    register int i = 0;
    while(str[i]!='\0'){
        i++;
    }
    return i;
}
int string_words(char* str)  {
    int i, len_str, words_number;
    char flag=-1;
    words_number = 0;
    len_str = string_count(str);
    for(i = 0; i < len_str; i++){
        if (is_whitespace(str[i]))
            flag = -1;
        else if (flag == -1) {
            flag = 1;
            words_number++;
        }
    }
    return words_number;
}
