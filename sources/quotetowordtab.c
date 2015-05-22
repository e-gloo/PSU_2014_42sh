/*
** quotetowordtab.c for quotetowordtab in /home/boulay_b/Work/SE2/PSU/42sh/PSU_2014_42sh
**
** Made by Arnaud Boulay
** Login   <boulay_b@epitech.net>
**
** Started on  Fri May 22 00:35:07 2015 Arnaud Boulay
** Last update Fri May 22 18:11:31 2015 Sebastien BOULOC
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"

static int	count_quotes(char *str)
{
  int		quote;
  int		i;

  i = -1;
  quote = 0;
  while (str[++i] != '\0')
    if (str[i] == '"')
      ++quote;
  if (quote % 2 != 0)
    {
      printf("Unmatched \".\n");
      return (-1);
    }
  return (quote);
}

static int	count_words(char *str, char *sep)
{
  int		quote;
  int		words;
  int		i;

  i = -1;
  if (count_quotes(str) == -1)
    return (0);
  words = 0;
  quote = 0;
  while (str[++i] != '\0')
    {
      if (str[i] == '"')
	{
	  if (quote == 0)
	    quote = 1;
	  else
	    quote = 0;
	}
      if (quote == 0
	  && (is_cinside(sep, str[i]) == 0 && str[i] != '\t' &&
	      (is_cinside(sep, str[i + 1]) == 1 ||
	       str[i + 1] == '\t' || str[i + 1] == '\0')))
	++words;
    }
  return (words);
}

static int	my_wordlen(char *str, int *i, char *sep)
{
  int		quote;
  int		j;

  j = 0;
  quote = 0;
  while (str[++(*i)] != '\0')
    if (str[*i] == '"' && quote == 0)
      quote = 1;
    else if (quote == 1 || (quote == 0 && is_cinside(sep, str[*i]) == 0 &&
			    str[*i] != '\t'))
      {
	++j;
	if ((quote == 1 && str[*i + 1] == '"') ||
	    (quote == 0 && (is_cinside(sep, str[*i + 1]) == 1 ||
			    str[*i + 1] == '\t' ||
			    str[*i + 1] == '\0')))
	  {
	    if (quote == 1 && str[*i + 1] == '"')
	      ++(*i);
	    return (j);
	  }
      }
  return (-1);
}

static char	*my_wordcpy(char *tab, char *str, int *i, char *sep)
{
  int		quote;
  int		j;

  j = -1;
  quote = 0;
  while (str[++(*i)] != '\0')
    if (str[*i] == '"' && quote == 0)
      quote = 1;
    else if (quote == 1 || (quote == 0 &&
			    is_cinside(sep, str[*i]) == 0 && str[*i] != '\t'))
      {
	tab[++j] = str[*i];
	if ((quote == 1 && str[*i + 1] == '"') ||
	    (quote == 0 && (is_cinside(sep, str[*i + 1]) == 1 ||
			    str[*i + 1] == '\t' || str[*i + 1] == '\0')))
	  {
	    if (quote == 1 && str[*i + 1] == '"')
	      ++(*i);
	    tab[++j] = '\0';
	    return (tab);
	  }
      }
  return (NULL);
}

char		**my_quotetowordtab(char *str, char *sep)
{
  char		**tab;
  int		words;
  int		i;
  int		j;
  int		k;

  i = -1;
  j = -1;
  k = -1;
  if (str == NULL)
    return (NULL);
  words = count_words(str, sep);
  if ((tab = malloc(sizeof(char *) * (words + 1))) == NULL)
    return (NULL);
  while (++i < words)
    {
      if ((tab[i] = malloc(sizeof(char) * (my_wordlen(str, &j, sep) + 2)))
	  == NULL)
	return (NULL);
      tab[i] = my_wordcpy(tab[i], str, &k, sep);
    }
  tab[i] = NULL;
  return (tab);
}
