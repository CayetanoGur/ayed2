#ifdef STRFUNC_H
#define STRFUNC_H

/*lenth of the string pointed by str*/
size_t string_length(const char *str);

/*filters all the characters C that are inside the string poited by str*/
char *string_filter(const char *str, char c);

#endif