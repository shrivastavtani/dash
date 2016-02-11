#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util/util.h"

char *join_strings(char **tokens, char *delim, int start, int fin)
{
  int i, len = 0;
  
  for (i = start; i < fin; i++)
  {
    len += strlen(tokens[i]);
    len += strlen(delim);
  }

  char *dest = (char *) malloc (sizeof(char) * len);

  for (i = start; i < fin; i++)
  {
    strcat(dest, tokens[i]);
    strcat(dest, delim);
  }

  return dest;
}

void remove_substring(char *s,const char *toremove)
{
  while( s=strstr(s,toremove) )
    memmove(s,s+strlen(toremove),1+strlen(s+strlen(toremove)));
}

char *extract_host(char *string)
{
  int x;
  char **strings = str_split(string, ":", &x);
  return strings[0];
}

char **str_split(char *string, const char *delim, int *num_split)
{
  int str_len = strlen(string);
  int flag = 1;
  int i;
  int num_sub_strings = 0;
  char **substrings = (char **) malloc (sizeof(char *) * str_len);
  char *start = string;
  char *end = strstr(string, delim);

  if (start == end) {
    start += strlen(delim);
    end += strlen(delim);
    end = strstr(end, delim);
  }

  if (end == NULL) {
    substrings[0] = strdup(string);
    num_sub_strings++;
  }

  while (end != NULL)
  {
    if (flag) {
      substrings[num_sub_strings] = (char *) malloc (sizeof(char) * str_len);
      i = 0;
      flag = 0;
    }

    substrings[num_sub_strings][i++] = *start;
    start++;

    if (start == end) {
      start += strlen(delim);
      end += strlen(delim);
      end = strstr(end, delim);
      flag = 1;
      substrings[num_sub_strings][i] = '\0';
      num_sub_strings++;
      if (end == NULL) {
        substrings[num_sub_strings++] = strdup(start);
        break;
      }
    }

  }
  *num_split = num_sub_strings;
  return substrings;
}